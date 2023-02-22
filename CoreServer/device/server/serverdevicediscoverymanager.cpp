#include "serverdevicediscoverymanager.h"

#include <QDebug>

#include "communication/communicationmanagerbase.h"
#include "device/devicediscoverymessage.h"
#include "datamodel/datamodelmanager.h"
#include "device/devicediscoverymanagerbase.h"

#include "macros.h"

ServerDeviceDiscoveryManager::ServerDeviceDiscoveryManager(QString serviceId, QObject *parent) : DeviceDiscoveryManagerBase(serviceId, parent)
{
    m_modelBridge = new DeviceDiscoveryModelBridge(this);
}

void ServerDeviceDiscoveryManager::init(LocalConfig *config) {
    DeviceDiscoveryManagerBase::init(config);
    m_modelBridge->init(config);
}

MessageBase::MESSAGE_TYPE ServerDeviceDiscoveryManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY;
}

void ServerDeviceDiscoveryManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    DeviceDiscoveryMessage* ddMessage = static_cast<DeviceDiscoveryMessage*>(msg);

    DeviceBase* device = m_modelBridge->handleReceivedMessage(ddMessage);
}
