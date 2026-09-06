#include "rs485relaycontroller.h"

#include <QDebug>
#include <QSerialPort>
#include <QMutexLocker>

#include "controller/controllermanager.h"

RS485RelayController::RS485RelayController(ControllerManager *manager, QString id, RELAY_MODEL model, int relayCount, QObject *parent) : RelayControllerBase(manager, id, relayCount, parent), m_model(model)
{
    connect(&m_statusTimer, &QTimer::timeout, this, &RS485RelayController::retrieveStatus);
}

RS485RelayController::~RS485RelayController() {
    m_modbusClient.disconnectDevice();
}

void RS485RelayController::init() {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 20000));
    m_slaveId = m_config->getInt(this, "slaveId", 1);

    m_modbusClient.setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_config->getString(this, "serial.port", "COM1"));
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbusClient.setNumberOfRetries(1);

    iInfo() << "Relay count:" << m_relayCount;

    connect(&m_modbusClient, &QModbusDevice::stateChanged, this, &RS485RelayController::onStateChanged);
    connect(&m_modbusClient, &QModbusDevice::errorOccurred, this, &RS485RelayController::onErrorOccurred);
}

void RS485RelayController::start() {
    iDebug() << Q_FUNC_INFO;
    iInfo() << "Connecting on" << m_modbusClient.connectionParameter(QModbusDevice::SerialPortNameParameter).toString();

    m_modbusClient.connectDevice();
    m_statusTimer.start();
}

void RS485RelayController::printRawMessage(quint8 slaveId, const QModbusRequest &req) {
    QByteArray rawFrame;
    rawFrame.append(static_cast<char>(slaveId));
    rawFrame.append(static_cast<char>(req.functionCode()));
    rawFrame.append(req.data());

    quint16 crc = 0xFFFF;
    for (int pos = 0; pos < rawFrame.size(); pos++) {
        crc ^= static_cast<quint8>(rawFrame.at(pos));
        for (int i = 8; i != 0; i--) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    rawFrame.append(static_cast<char>(crc & 0xFF));
    rawFrame.append(static_cast<char>((crc >> 8) & 0xFF));

    QString hexString;
    for (int i = 0; i < rawFrame.size(); ++i) {
        hexString.append(QString("%1 ").arg(static_cast<quint8>(rawFrame.at(i)), 2, 16, QChar('0')).toUpper());
    }
    iDebug() << "Raw Modbus Request Sent:" << hexString.trimmed();
}

void RS485RelayController::printRawResponse(quint8 slaveId, const QModbusResponse &response) {
    QByteArray rawFrame;
    rawFrame.append(static_cast<char>(slaveId));
    rawFrame.append(static_cast<char>(response.functionCode()));
    rawFrame.append(response.data());

    quint16 crc = 0xFFFF;
    for (int pos = 0; pos < rawFrame.size(); pos++) {
        crc ^= static_cast<quint8>(rawFrame.at(pos));
        for (int i = 8; i != 0; i--) {
            if ((crc & 0x0001) != 0) {
                crc >>= 1;
                crc ^= 0xA001;
            } else {
                crc >>= 1;
            }
        }
    }
    rawFrame.append(static_cast<char>(crc & 0xFF));
    rawFrame.append(static_cast<char>((crc >> 8) & 0xFF));

    QString hexString;
    for (int i = 0; i < rawFrame.size(); ++i) {
        hexString.append(QString("%1 ").arg(static_cast<quint8>(rawFrame.at(i)), 2, 16, QChar('0')).toUpper());
    }
    iDebug() << "Raw Modbus Response Received:" << hexString.trimmed();
}

void RS485RelayController::switchStatus(quint8 relayIndex, bool status) {
    iDebug() << Q_FUNC_INFO << relayIndex << status;
    QMutexLocker locker(&m_Mutex);

    quint16 targetRegister = quint16(relayIndex + 1);
    quint16 controlValue = 0x0000;

    if (m_model == RS485_SERIAL_8PORT) {
        controlValue = status ? quint16(0x0100) : quint16(0x0200);
    } else {
        controlValue = status ? quint16(0x0001) : quint16(0x0000);
    }

    ModbusCommand cmd = { targetRegister, controlValue, relayIndex };
    m_commandQueue.enqueue(cmd);

    if (!m_isSending) {
        m_isSending = true;
        QTimer::singleShot(10, this, &RS485RelayController::processNextCommand);
    }
}

void RS485RelayController::processNextCommand() {
    if (m_commandQueue.isEmpty()) {
        m_isSending = false;
        return;
    }

    if (m_modbusClient.state() != QModbusClient::ConnectedState) {
        m_commandQueue.clear();
        m_isSending = false;
        m_warnManager->raiseWarning("Serial not connected", QtCriticalMsg);
        return;
    }

    ModbusCommand cmd = m_commandQueue.dequeue();

    QModbusRequest req(QModbusRequest::WriteSingleRegister);
    req.encodeData(cmd.reg, cmd.val);

    printRawMessage(m_slaveId, req);

    QModbusReply* reply = m_modbusClient.sendRawRequest(req, m_slaveId);

    if (!reply) {
        iWarning() << "Failed to enqueue raw write request.";
        QTimer::singleShot(80, this, &RS485RelayController::processNextCommand);
        return;
    }

    quint8 rIdx = cmd.idx;
    bool expectedStatus = (m_model == RS485_SERIAL_8PORT) ? (cmd.val == 0x0200) : (cmd.val == 0x0001);

    connect(reply, &QModbusReply::finished, this, [this, rIdx, reply, expectedStatus]() {
        if (reply->error() == QModbusDevice::NoError) {
            printRawResponse(m_slaveId, reply->rawResult());
            setStatus(rIdx, expectedStatus);
            m_valueManager->publishValue(actor(rIdx));
            iDebug() << "Relay" << rIdx << "successfully switched";
        } else {
            iWarning() << "Write failed for relay" << rIdx << "Error:" << reply->errorString();
        }
        reply->deleteLater();

        QTimer::singleShot(80, this, &RS485RelayController::processNextCommand);
    });
}

quint8 RS485RelayController::getRelayCount(RELAY_MODEL model) {
    switch (model) {
    case RS485_SERIAL_32PORT:
        return 32;
    case RS485_SERIAL_8PORT:
        return 8;
    default:
        qWarning() << "Unknown relay model" << model;
        return 0;
    }
}

void RS485RelayController::onStateChanged() {
    iDebug() << Q_FUNC_INFO << m_modbusClient.state();

    switch(m_modbusClient.state()) {
    case QModbusClient::ConnectedState:
        Q_EMIT(controllerConnected());
        break;
    case QModbusClient::UnconnectedState:
        onErrorOccurred();
        break;
    default:
        iDebug() << m_modbusClient.state();
        break;
    }
}

void RS485RelayController::onErrorOccurred() {
    iDebug() << Q_FUNC_INFO << m_modbusClient.errorString();

    m_warnManager->raiseWarning("Relay connection disconnected", QtCriticalMsg);
    Q_EMIT(controllerDisconnected());
}

void RS485RelayController::onDataReceived() {
    iDebug() << Q_FUNC_INFO;

    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        QModbusResponse response = reply->rawResult();
        printRawResponse(m_slaveId, response);
        QByteArray data = response.data();

        iDebug() << "Data size received:" << data.size();

        setSerialRelayStatus(STATUS_RECEIVED);

        if (!data.isEmpty()) {
            for (quint8 i = 0; i < m_relayCount; i++) {
                int highByteIdx = 1 + (i * 2);
                int lowByteIdx  = 2 + (i * 2);

                if (lowByteIdx < data.size()) {
                    quint16 regValue = (static_cast<quint8>(data.at(highByteIdx)) << 8)
                    |  static_cast<quint8>(data.at(lowByteIdx));

                    bool isOn = (regValue == 0x0001);
                    setStatus(i, isOn);
                    m_valueManager->publishValue(actor(i));
                }
            }
        }
        m_errorCount = 0;
    } else {
        iWarning() << "Modbus error:" << reply->error() << reply->errorString();
        m_errorCount++;
    }

    reply->deleteLater();
}

void RS485RelayController::setSerialRelayStatus(RELAY_STATUS status) {
    if (m_currentStatus != status) {
        m_currentStatus = status;
    }
}

void RS485RelayController::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

    QMutexLocker locker(&m_Mutex);

    if (m_modbusClient.state() == QModbusClient::UnconnectedState) {
        iDebug() << "Connecting to modbus";
        m_modbusClient.connectDevice();
    } else {
        if (m_currentStatus == RETRIEVING_STATUS) {
            m_warnManager->raiseWarning("No status from relay", QtCriticalMsg);
            m_errorCount++;
        }

        if (m_errorCount > 5) {
            iWarning() << "Too many errors - disconnecting";
            onErrorOccurred();
        } else {
            setSerialRelayStatus(RETRIEVING_STATUS);

            QModbusRequest req(QModbusRequest::ReadHoldingRegisters);
            req.encodeData(quint16(0x0001), quint16(m_relayCount));
            printRawMessage(m_slaveId, req);

            QModbusReply* reply = m_modbusClient.sendRawRequest(req, m_slaveId);
            connect(reply, &QModbusReply::finished, this, &RS485RelayController::onDataReceived);
        }
    }
}
