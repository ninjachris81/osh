#include "rs485relaycontroller.h"

#include <QDebug>

#include "controller/controllermanager.h"
#include "modbuscrc.h"

RS485RelayController::RS485RelayController(ControllerManager *manager, QString id, RELAY_MODEL model, quint8 relayCount, QObject *parent) : RelayControllerBase(manager, id, relayCount, parent), m_model(model)
{
    connect(&m_statusTimer, &QTimer::timeout, this, &RS485RelayController::retrieveStatus);

}

void RS485RelayController::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 10000));

    m_serialClient = new SerialPortClient(m_config->getString(this, "serial.port", "COM1"), QSerialPort::Baud9600);

    m_slaveId = m_config->getInt(this, "slaveId", 1);

    m_expectedDatagramSize = (m_relayCount * 2) + MODBUS_HEADER_LENGTH + MODBUS_CRC_LENTH;

    m_serialClient->setReadBufferSize(m_expectedDatagramSize);
    m_serialClient->setReadDatagramSize(m_expectedDatagramSize);
    m_serialClient->setLineMode(false);

    connect(m_serialClient, &SerialPortClient::connected, this, &RS485RelayController::onSerialConnected);
    connect(m_serialClient, &SerialPortClient::disconnected, this, &RS485RelayController::onSerialDisconnected);
    connect(m_serialClient, &SerialPortClient::dataReceived, this, &RS485RelayController::onSerialDataReceived);
}

void RS485RelayController::start() {
    iDebug() << Q_FUNC_INFO;

    m_serialClient->start();
}

void RS485RelayController::switchStatus(quint8 relayIndex, bool status) {
    iDebug() << Q_FUNC_INFO << relayIndex << status;

    if (m_serialClient->isConnected()) {
        QByteArray data;

        data.append((char) m_slaveId);
        data.append((char) 0x06);
        data.append((char) 0x00);
        data.append(static_cast<signed char>(relayIndex + 1));
        data.append(status ? '\x01' : '\x02');
        data.append((char) 0x00);

        ModbusCRC::appendCRC(data);

        QByteArray readData = m_serialClient->writeReadSync(data, 8, 500);
        qDebug() << "Write returned" << readData;
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

void RS485RelayController::onSerialConnected() {
    iDebug() << Q_FUNC_INFO;

    m_statusTimer.start();
    Q_EMIT(controllerConnected());
}

void RS485RelayController::onSerialDisconnected() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Relay connection disconnected");
    m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}

void RS485RelayController::onSerialDataReceived(QByteArray data) {
    iDebug() << Q_FUNC_INFO << data;

    if (m_currentStatus == RETRIEVING_STATUS) {
        switch(m_model) {
        case RS485_SERIAL_32PORT:
            if (data.size() == m_expectedDatagramSize) {
                setSerialRelayStatus(STATUS_RECEIVED);
                for (quint8 i = 0;i<m_relayCount;i++) {
                    setStatus(i, data.at(MODBUS_HEADER_LENGTH + (i * 2) + 1) == 0x01);
                }
            } else {
                setSerialRelayStatus(STATUS_ERROR);
                m_warnManager->raiseWarning("Invalid response size from relay" + QString::number(data.size()));
            }

            break;
        }
    }
}

void RS485RelayController::setSerialRelayStatus(RELAY_STATUS status) {
    if (m_currentStatus != status) {
        //iDebug() << "New status" << status;
        m_currentStatus = status;
    }
}

void RS485RelayController::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

    if (m_currentStatus == RETRIEVING_STATUS) {
        m_warnManager->raiseWarning("No status from relay");
    }

    setSerialRelayStatus(RETRIEVING_STATUS);

    QByteArray data;

    switch(m_model) {
    case RS485_SERIAL_32PORT:
        data.append((char) m_slaveId);
        data.append((char) 0x03);
        data.append((char) 0x00);
        data.append((char) 0x01);
        data.append((char) 0x00);
        data.append((char) 0x20);

        ModbusCRC::appendCRC(data);

        m_serialClient->write(data, SERIAL_READ_TIMEOUT_MS);
        break;
    }
}
