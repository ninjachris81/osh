#include "devicediscoverymodelbridge.h"

#include <QDebug>
#include "datamodel/datamodelmanager.h"

#include "macros.h"
#include "shared/device.h"

DeviceDiscoveryModelBridge::DeviceDiscoveryModelBridge(DeviceDiscoveryManagerBase *parent) : QObject(parent), m_parent(parent)
{
    connect(&m_onlineCheckTimer, &QTimer::timeout, this, &DeviceDiscoveryModelBridge::onOnlineCheck);
}

void DeviceDiscoveryModelBridge::init(LocalConfig *config) {
    REQUIRE_MANAGER_X(m_parent, DatamodelManager);
    m_datamodelManager = m_parent->getManager<DatamodelManager>(DatamodelManager::MANAGER_NAME);

    m_onlineCheckTimer.start(config->getInt("dd.onlineCheckInterval", DEFAULT_DD_ONLINE_CHECK_INTERVAL));
    m_onlineCheckTimeout = config->getInt("dd.onlineCheckTimeout", DEFAULT_DD_ONLINE_CHECK_TIMEOUT);
}

DeviceBase *DeviceDiscoveryModelBridge::registerUnknownDevice(QString id) {
    qDebug() << Q_FUNC_INFO << id;

    DeviceBase* device = new DeviceBase(id);
    m_unknownDevices.insert(id, device);
    Q_EMIT(unknownDevicesChanged());
    return device;
}

DeviceBase *DeviceDiscoveryModelBridge::handleReceivedMessage(DeviceDiscoveryMessage* msg) {
    DeviceBase* device;
    if (m_datamodelManager->datamodel()->knownDevices().contains(msg->deviceId())) {
        device = m_datamodelManager->datamodel()->knownDevices().value(msg->deviceId());
    } else {
        if (!m_unknownDevices.contains(msg->deviceId())) {
            device = registerUnknownDevice(msg->deviceId());
        } else {
            device = m_unknownDevices.value(msg->deviceId());
        }
    }

    device->updatePing();

    return device;
}

void DeviceDiscoveryModelBridge::onOnlineCheck() {
    QMapIterator<QString, KnownDevice*> it(m_datamodelManager->datamodel()->knownDevices());
    while(it.hasNext()) {
        it.next();
        it.value()->updateOnline(m_onlineCheckTimeout);
    }

    QMapIterator<QString, DeviceBase*> it2(m_unknownDevices);
    while(it2.hasNext()) {
        it2.next();
        it2.value()->updateOnline(m_onlineCheckTimeout);
    }
}

QMap<QString, DeviceBase*> DeviceDiscoveryModelBridge::unknownDevices() {
    return m_unknownDevices;
}

QMap<QString, KnownDevice*> DeviceDiscoveryModelBridge::knownDevices() {
    return m_datamodelManager->datamodel()->knownDevices();
}
