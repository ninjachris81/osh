#include "wbb12controller.h"

#include <QDebug>
#include <QSerialPort>

#include "controller/controllermanager.h"

WBB12Controller::WBB12Controller(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent) {
    connect(&m_statusTimer, &QTimer::timeout, this, &WBB12Controller::retrieveStatus);
}

void WBB12Controller::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 10000));

    m_slaveId = m_config->getInt(this, "slaveId", 1);

    m_modbusClient.setConnectionParameter(QModbusDevice::NetworkAddressParameter, m_config->getString(this, "tcp.ip", "127.0.0.1"));
    m_modbusClient.setConnectionParameter(QModbusDevice::NetworkPortParameter, m_config->getString(this, "tcp.port", "502"));
    m_modbusClient.setTimeout(500);
    m_modbusClient.setNumberOfRetries(1);

    connect(&m_modbusClient, &QModbusDevice::stateChanged, this, &WBB12Controller::onStateChanged);
    connect(&m_modbusClient, &QModbusDevice::errorOccurred, this, &WBB12Controller::onErrorOccurred);
}

void WBB12Controller::start() {
    iDebug() << Q_FUNC_INFO;

    m_modbusClient.connectDevice();
}

void WBB12Controller::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void WBB12Controller::onStateChanged() {
    iDebug() << Q_FUNC_INFO;

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

void WBB12Controller::onErrorOccurred() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Relay connection disconnected");
    m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}

void WBB12Controller::onDataReceived() {
    iDebug() << Q_FUNC_INFO;

    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        QModbusResponse response = reply->rawResult();
        iDebug() << response.dataSize();
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        iWarning() << "Modbus error" << reply->error();
    } else {
        iWarning() << "Modbus error" << reply->error();
    }

    reply->deleteLater();
}


void WBB12Controller::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

    QByteArray data;
    data.append((char) 0x00);
    data.append((char) 0x20);

    QModbusRequest req(QModbusRequest::ReadInputRegisters);
    req.encodeData(quint16(0x0001), quint16(0x0020));

    QModbusReply* reply = m_modbusClient.sendRawRequest(req, m_slaveId);
    connect(reply, &QModbusReply::finished, this, &WBB12Controller::onDataReceived);
}
