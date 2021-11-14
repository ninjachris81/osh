#include "clientdevicemanager.h"
#include <QDebug>

#include "device/devicediscoverymessage.h"
#include "macros.h"

ClientDeviceDiscoveryManager::ClientDeviceDiscoveryManager(QObject *parent) : DeviceDiscoveryManagerBase(parent)
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
