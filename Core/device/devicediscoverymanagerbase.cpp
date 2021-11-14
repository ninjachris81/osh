#include "devicediscoverymanagerbase.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "device/devicediscoverymessage.h"
#include "datamodel/datamodelmanager.h"

#include "macros.h"
#include "shared/device.h"

QString DeviceDiscoveryManagerBase::MANAGER_NAME = QStringLiteral("DeviceDiscoveryManager");

DeviceDiscoveryManagerBase::DeviceDiscoveryManagerBase(QObject *parent) : ManagerBase(parent)
{
    connect(&m_ddTimer, &QTimer::timeout, this, &DeviceDiscoveryManagerBase::sendDDBroadcast);
}

QString DeviceDiscoveryManagerBase::getName() {
    return MANAGER_NAME;
}

void DeviceDiscoveryManagerBase::init(LocalConfig *config) {
    qDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(CommunicationManagerBase);

    m_device = new ClientDevice(Identifyable::getDeviceSerialId(config));
    m_ddTimer.setInterval(config->getInt("dd.broadcastInterval", DEFAULT_DD_BROADCAST_INTERVAL));

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_NAME);

    connect(m_commManager, &CommunicationManagerBase::connected, this, &DeviceDiscoveryManagerBase::startDDBroadcast);
    connect(m_commManager, &CommunicationManagerBase::disconnected, this, &DeviceDiscoveryManagerBase::stopDDBroadcast);
}

ClientDevice* DeviceDiscoveryManagerBase::device() {
    return m_device;
}

void DeviceDiscoveryManagerBase::startDDBroadcast() {
    qDebug() << Q_FUNC_INFO;

    // send one directly
    sendDDBroadcast();
    m_ddTimer.start();
}

void DeviceDiscoveryManagerBase::stopDDBroadcast() {
    qDebug() << Q_FUNC_INFO;
    m_ddTimer.stop();
}


void DeviceDiscoveryManagerBase::sendDDBroadcast() {
    qDebug() << Q_FUNC_INFO;

    DeviceDiscoveryMessage message(m_device->id());
    m_commManager->sendMessage(message);
}
