#include "clientdevicemanager.h"
#include <QDebug>

#include "device/devicediscoverymessage.h"
#include "macros.h"

ClientDeviceDiscoveryManager::ClientDeviceDiscoveryManager(QString serviceId, QObject *parent) : DeviceDiscoveryManagerBase(serviceId, parent)
{
}

void ClientDeviceDiscoveryManager::init(LocalConfig* config) {
    DeviceDiscoveryManagerBase::init(config);
}

MessageBase::MESSAGE_TYPE ClientDeviceDiscoveryManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void ClientDeviceDiscoveryManager::handleReceivedMessage(MessageBase* msg) {

}
