#include "rs485relaycontroller.h"

#include <QDebug>
#include <QSerialPort>
#include <QMutexLocker>

#include "controller/controllermanager.h"

RS485RelayController::RS485RelayController(ControllerManager *manager, QString id, RELAY_MODEL model, quint8 relayCount, QObject *parent) : RelayControllerBase(manager, id, relayCount, parent), m_model(model)
{
    connect(&m_statusTimer, &QTimer::timeout, this, &RS485RelayController::retrieveStatus);

}

void RS485RelayController::init() {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 10000));

    m_slaveId = m_config->getInt(this, "slaveId", 1);

    m_modbusClient.setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_config->getString(this, "serial.port", "COM1"));
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::NoParity);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbusClient.setTimeout(500);
    m_modbusClient.setNumberOfRetries(1);

    connect(&m_modbusClient, &QModbusDevice::stateChanged, this, &RS485RelayController::onStateChanged);
    connect(&m_modbusClient, &QModbusDevice::errorOccurred, this, &RS485RelayController::onErrorOccurred);
}

void RS485RelayController::start() {
    iDebug() << Q_FUNC_INFO;

    iInfo() << "Connecting on" << m_modbusClient.connectionParameter(QModbusDevice::SerialPortNameParameter).toString();

    m_modbusClient.connectDevice();
}

void RS485RelayController::switchStatus(quint8 relayIndex, bool status) {
    iDebug() << Q_FUNC_INFO << relayIndex << status;
    QMutexLocker locker(&m_Mutex);

    if (m_modbusClient.state() == QModbusClient::ConnectedState) {
        QModbusRequest req(QModbusRequest::WriteSingleRegister);
        req.encodeData(quint16(relayIndex + 1), quint8(status ? '\x01' : '\x02'), quint8(0x00));
        QModbusReply* reply = m_modbusClient.sendRawRequest(req, m_slaveId);
        connect(reply, &QModbusReply::finished, this, [this, relayIndex, reply]() {
            QModbusResponse response = reply->rawResult();
            iDebug() << response.dataSize();
            setStatus(relayIndex, response.data().at(2) == 0x01);
        });
    } else {
        m_warnManager->raiseWarning("Serial not connected");
    }
}

quint8 RS485RelayController::getRelayCount(RELAY_MODEL model) {
    switch (model) {
    case RS485_SERIAL_32PORT:
        return 32;
    default:
        qWarning() << "Unknown relay model" << model;
        return 0;
    }
}

void RS485RelayController::onStateChanged() {
    iDebug() << Q_FUNC_INFO << m_modbusClient.state();

    switch(m_modbusClient.state()) {
    case QModbusClient::ConnectedState:
        m_statusTimer.start();
        Q_EMIT(controllerConnected());
        break;
    case QModbusClient::UnconnectedState:
        m_statusTimer.stop();
        Q_EMIT(controllerDisconnected());
        break;
    default:
        iDebug() << m_modbusClient.state();
        break;
    }

}

void RS485RelayController::onErrorOccurred() {
    iDebug() << Q_FUNC_INFO << m_modbusClient.errorString();

    m_warnManager->raiseWarning("Relay connection disconnected");
    m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}

void RS485RelayController::onDataReceived() {
    iDebug() << Q_FUNC_INFO;

    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        QModbusResponse response = reply->rawResult();

        iDebug() << response.dataSize();

        setSerialRelayStatus(STATUS_RECEIVED);

        for (quint8 i = 0;i<m_relayCount;i++) {
            setStatus(i, response.data().at((i * 2) + 2) == 0x01);
            m_valueManager->publishValue(actor(i));
        }
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        iWarning() << "Modbus error" << reply->error();
    } else {
        iWarning() << "Modbus error" << reply->error();
    }

    reply->deleteLater();
}

void RS485RelayController::setSerialRelayStatus(RELAY_STATUS status) {
    if (m_currentStatus != status) {
        //iDebug() << "New status" << status;
        m_currentStatus = status;
    }
}

void RS485RelayController::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

    QMutexLocker locker(&m_Mutex);

    if (m_currentStatus == RETRIEVING_STATUS) {
        m_warnManager->raiseWarning("No status from relay");
    }

    setSerialRelayStatus(RETRIEVING_STATUS);

    QByteArray data;
    data.append((char) 0x00);
    data.append((char) 0x20);

    QModbusRequest req(QModbusRequest::ReadHoldingRegisters);
    req.encodeData(quint16(0x0001), quint16(0x0020));

    QModbusReply* reply = m_modbusClient.sendRawRequest(req, m_slaveId);
    connect(reply, &QModbusReply::finished, this, &RS485RelayController::onDataReceived);
}
