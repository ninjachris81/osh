#include "kmtronicrelaycontroller.h"

#include <QDebug>

#include "controller/controllermanager.h"

KMTronicRelayController::KMTronicRelayController(ControllerManager *manager, QString id, RELAY_MODEL model, quint8 relayCount, QObject *parent) : RelayControllerBase(manager, id, relayCount, parent), m_model(model)
{
    connect(&m_statusTimer, &QTimer::timeout, this, &KMTronicRelayController::retrieveStatus);

}

void KMTronicRelayController::init() {
    qDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_NAME);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 10000));

    m_serialClient = new SerialPortClient(m_config->getString(this, "serial.port", "COM1"), QSerialPort::Baud9600);

    m_serialClient->setReadBufferSize(8);
    m_serialClient->setLineMode(false);
    m_serialClient->setReadDatagramSize(8);

    connect(m_serialClient, &SerialPortClient::connected, this, &KMTronicRelayController::onSerialConnected);
    connect(m_serialClient, &SerialPortClient::disconnected, this, &KMTronicRelayController::onSerialDisconnected);
    connect(m_serialClient, &SerialPortClient::dataReceived, this, &KMTronicRelayController::onSerialDataReceived);

    m_serialClient->start();
}

void KMTronicRelayController::switchStatus(quint8 relayIndex, bool status) {
    if (m_serialClient->isConnected()) {
        QByteArray data;
        data.append('\xFF');
        data.append(static_cast<signed char>(relayIndex + 1));
        data.append(status ? '\x01' : '\x00');
        m_serialClient->write(data, -1);
    } else {
        m_warnManager->raiseWarning("Serial not connected");
    }
}

quint8 KMTronicRelayController::getRelayCount(RELAY_MODEL model) {
    switch (model) {
    case USB_SERIAL_8PORT:
        return 8;
    default:
        qWarning() << "Unknown relay model" << model;
        return 0;
    }
}

void KMTronicRelayController::onSerialConnected() {
    qDebug() << Q_FUNC_INFO;

    m_statusTimer.start();
}

void KMTronicRelayController::onSerialDisconnected() {
    qDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Relay connection disconnected");
    m_statusTimer.stop();
}

void KMTronicRelayController::onSerialDataReceived(QByteArray data) {
    qDebug() << Q_FUNC_INFO << data;

    if (m_currentStatus == RETRIEVING_STATUS) {
        if (data.size() == m_relayCount) {
            setSerialRelayStatus(STATUS_RECEIVED);

            for (quint8 i = 0;i<m_relayCount;i++) {
                setStatus(i, data.at(i) == 1);
            }
        } else {
            setSerialRelayStatus(STATUS_ERROR);
            m_warnManager->raiseWarning("Invalid response size from relay" + QString::number(data.size()));
        }
    }
}

void KMTronicRelayController::setSerialRelayStatus(RELAY_STATUS status) {
    if (m_currentStatus != status) {
        //qDebug() << "New status" << status;
        m_currentStatus = status;
    }
}

void KMTronicRelayController::retrieveStatus() {
    qDebug() << Q_FUNC_INFO;

    if (m_currentStatus == RETRIEVING_STATUS) {
        m_warnManager->raiseWarning("No status from relay");
    }

    setSerialRelayStatus(RETRIEVING_STATUS);

    QByteArray data;

    switch(m_model) {
    case USB_SERIAL_8PORT:
        data.append('\xFF');
        data.append('\x09');
        data.append('\x00');
        m_serialClient->write(data, SERIAL_READ_TIMEOUT_MS);
        break;
    }
}
