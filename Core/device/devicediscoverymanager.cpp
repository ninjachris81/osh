#include "devicediscoverymanager.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "device/devicediscoverymessage.h"

QString DeviceDiscoveryManager::MANAGER_NAME = QStringLiteral("DeviceDiscoveryManager");

DeviceDiscoveryManager::DeviceDiscoveryManager(QObject *parent) : ManagerBase(parent)
{

}

void DeviceDiscoveryManager::init(LocalConfig *config) {
}

QString DeviceDiscoveryManager::getName() {
    return MANAGER_NAME;
}

DeviceBase *DeviceDiscoveryManager::registerUnknownDevice(QString id) {
    qDebug() << Q_FUNC_INFO << id;

    DeviceBase* device = new DeviceBase(id);
    m_unknownDevices.insert(id, device);
    return device;
}

MessageBase::MESSAGE_TYPE DeviceDiscoveryManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY;
}

void DeviceDiscoveryManager::handleReceivedMessage(MessageBase* msg) {
    qDebug() << Q_FUNC_INFO;
    DeviceDiscoveryMessage* ddMessage = static_cast<DeviceDiscoveryMessage*>(msg);

    DeviceBase* device;
    if (!m_unknownDevices.contains(ddMessage->deviceId())) {
        device = registerUnknownDevice(ddMessage->deviceId());
    } else if (!m_knownDevices.contains(ddMessage->deviceId())) {
        device = m_unknownDevices.value(ddMessage->deviceId());
    } else {
        device = m_knownDevices.value(ddMessage->deviceId());
    }

    device->updatePing();
}
