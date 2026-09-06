#include "rs485relaycontroller.h"

#include <QDebug>
#include <QSerialPort>
#include <QMutexLocker>

#include "controller/controllermanager.h"

RS485RelayController::RS485RelayController(ControllerManager *manager, QString id, RELAY_MODEL model, QObject *parent) : RelayControllerBase(manager, id, getRelayCount(model), parent), m_model(model)
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

void RS485RelayController::switchStatus(quint8 relayIndex, bool status) {
    iDebug() << Q_FUNC_INFO << relayIndex << status;
    QMutexLocker locker(&m_Mutex);

    if (m_modbusClient.state() == QModbusClient::ConnectedState) {
        int targetAddress = 0;

        quint8 relayNumber = relayIndex + 1;
        quint8 actionValue = status ? 0x01 : 0x02;
        quint16 controlValue = (static_cast<quint16>(relayNumber) << 8) | actionValue;

        QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, targetAddress, 1);
        writeUnit.setValue(0, controlValue);

        QModbusReply* reply = m_modbusClient.sendWriteRequest(writeUnit, m_slaveId);

        if (!reply) {
            iWarning() << "Failed to enqueue write request.";
            return;
        }

        connect(reply, &QModbusReply::finished, this, [this, relayIndex, reply, status]() {
            if (reply->error() == QModbusDevice::NoError) {
                setStatus(relayIndex, status);
                m_valueManager->publishValue(actor(relayIndex));
                iDebug() << "Relay" << relayIndex << "successfully switched to" << status;
            } else {
                iWarning() << "Write failed for relay" << relayIndex << "Error:" << reply->errorString();
            }
            reply->deleteLater();
        });
    } else {
        m_warnManager->raiseWarning("Serial not connected", QtCriticalMsg);
    }
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

                    bool isOn = ((regValue & 0x00FF) == 0x0001);
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

            QModbusReply* reply = m_modbusClient.sendRawRequest(req, m_slaveId);
            connect(reply, &QModbusReply::finished, this, &RS485RelayController::onDataReceived);
        }
    }
}
