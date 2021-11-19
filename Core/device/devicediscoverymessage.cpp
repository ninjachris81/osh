#include "devicediscoverymessage.h"

DeviceDiscoveryMessage::DeviceDiscoveryMessage(QString serviceId, QString deviceId, QObject *parent) : MessageBase(parent), m_deviceId(deviceId), m_serviceId(serviceId)
{

}

QString DeviceDiscoveryMessage::deviceId() {
    return m_deviceId;
}

QString DeviceDiscoveryMessage::serviceId() {
    return m_serviceId;
}

MessageBase::MESSAGE_TYPE DeviceDiscoveryMessage::getMessageType() {
    return MESSAGE_TYPE_DEVICE_DISCOVERY;
}

QString DeviceDiscoveryMessage::getFirstLevelId() {
    return m_deviceId;
}

QString DeviceDiscoveryMessage::getSecondLevelId() {
    return m_serviceId;
}
