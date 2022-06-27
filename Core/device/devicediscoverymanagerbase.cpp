#include "devicediscoverymanagerbase.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "device/devicediscoverymessage.h"

#include "macros.h"
#include "shared/device.h"

QLatin1String DeviceDiscoveryManagerBase::MANAGER_ID = QLatin1String("DeviceDiscoveryManager");

DeviceDiscoveryManagerBase::DeviceDiscoveryManagerBase(QString serviceId, QObject *parent) : ManagerBase(parent), m_serviceId(serviceId)
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

    m_startedTime = QDateTime::currentMSecsSinceEpoch();

    REQUIRE_MANAGER(CommunicationManagerBase);

    m_device = new ClientDevice(Identifyable::getDeviceSerialId(config), m_serviceId);
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

    DeviceDiscoveryMessage message(m_device->id(), m_device->serviceId(), QDateTime::currentMSecsSinceEpoch() - m_startedTime);
    m_commManager->sendMessage(message);
}
