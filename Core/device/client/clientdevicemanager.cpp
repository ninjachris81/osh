#include "clientdevicemanager.h"
#include <QDebug>

#include "shared/device.h"
#include "device/devicediscoverymessage.h"
#include "macros.h"

QString ClientDeviceManager::MANAGER_NAME = QStringLiteral("ClientDeviceManager");

ClientDeviceManager::ClientDeviceManager(QObject *parent) : ManagerBase(parent)
{
    connect(&m_ddTimer, &QTimer::timeout, this, &ClientDeviceManager::sendDDBroadcast);
}

void ClientDeviceManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(CommunicationManagerBase);

    m_device = new ClientDevice(Identifyable::getDeviceSerialId(config));
    m_ddTimer.setInterval(config->getInt("dd.interval", DEFAULT_DD_BROADCAST_INTERVAL));

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_NAME);

    connect(m_commManager, &CommunicationManagerBase::connected, this, &ClientDeviceManager::startDDBroadcast);
    connect(m_commManager, &CommunicationManagerBase::disconnected, this, &ClientDeviceManager::stopDDBroadcast);
}

QString ClientDeviceManager::getName() {
    return MANAGER_NAME;
}

ClientDevice* ClientDeviceManager::device() {
    return m_device;
}

void ClientDeviceManager::startDDBroadcast() {
    qDebug() << Q_FUNC_INFO;
    m_ddTimer.start();
}

void ClientDeviceManager::stopDDBroadcast() {
    qDebug() << Q_FUNC_INFO;
    m_ddTimer.stop();
}


void ClientDeviceManager::sendDDBroadcast() {
    qDebug() << Q_FUNC_INFO;

    DeviceDiscoveryMessage message(m_device->id());
    m_commManager->sendMessage(message);
}

MessageBase::MESSAGE_TYPE ClientDeviceManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void ClientDeviceManager::handleReceivedMessage(MessageBase* msg) {

}
