#include "devicediscoverymessage.h"

DeviceDiscoveryMessage::DeviceDiscoveryMessage(QString deviceId, QObject *parent) : MessageBase(parent), m_deviceId(deviceId)
{

}

QString DeviceDiscoveryMessage::deviceId() {
    return m_deviceId;
}

MessageBase::MESSAGE_TYPE DeviceDiscoveryMessage::getMessageType() {
    return MESSAGE_TYPE_DEVICE_DISCOVERY;
}

QString DeviceDiscoveryMessage::getFirstLevelId() {
    return m_deviceId;
}

QString DeviceDiscoveryMessage::getSecondLevelId() {
    return "";
}
