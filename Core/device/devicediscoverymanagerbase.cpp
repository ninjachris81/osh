#include "devicediscoverymanagerbase.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "device/devicediscoverymessage.h"

#include "macros.h"
#include "shared/device.h"

QLatin1Literal DeviceDiscoveryManagerBase::MANAGER_ID = QLatin1Literal("DeviceDiscoveryManager");

DeviceDiscoveryManagerBase::DeviceDiscoveryManagerBase(QObject *parent) : ManagerBase(parent)
{
    connect(&m_ddTimer, &QTimer::timeout, this, &DeviceDiscoveryManagerBase::sendDDBroadcast);
}

LogCat::LOGCAT DeviceDiscoveryManagerBase::logCat() {
    return LogCat::DEVICE;
}

QString DeviceDiscoveryManagerBase::id() {
    return MANAGER_ID;
}

void DeviceDiscoveryManagerBase::init(LocalConfig *config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(CommunicationManagerBase);

    m_device = new ClientDevice(Identifyable::getDeviceSerialId(config));
    m_ddTimer.setInterval(config->getInt("dd.broadcastInterval", DEFAULT_DD_BROADCAST_INTERVAL));

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);

    connect(m_commManager, &CommunicationManagerBase::connected, this, &DeviceDiscoveryManagerBase::startDDBroadcast);
    connect(m_commManager, &CommunicationManagerBase::disconnected, this, &DeviceDiscoveryManagerBase::stopDDBroadcast);
}

ClientDevice* DeviceDiscoveryManagerBase::device() {
    return m_device;
}

void DeviceDiscoveryManagerBase::startDDBroadcast() {
    iDebug() << Q_FUNC_INFO;

    // send one directly
    sendDDBroadcast();
    m_ddTimer.start();
}

void DeviceDiscoveryManagerBase::stopDDBroadcast() {
    iDebug() << Q_FUNC_INFO;
    m_ddTimer.stop();
}


void DeviceDiscoveryManagerBase::sendDDBroadcast() {
    iDebug() << Q_FUNC_INFO;

    DeviceDiscoveryMessage message(m_device->id());
    m_commManager->sendMessage(message);
}
