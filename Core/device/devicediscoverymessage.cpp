#include "devicediscoverymessage.h"
#include "shared/device.h"
#include "shared/mqtt_qt.h"

#include <QDateTime>

DeviceDiscoveryMessage::DeviceDiscoveryMessage(QString deviceId, QString serviceId, quint64 upTime, DeviceHealthState healthState, QObject *parent) : MessageBase(parent), m_deviceId(deviceId), m_serviceId(serviceId), m_upTime(upTime), m_healthState(healthState)
{
}

QString DeviceDiscoveryMessage::fullId() {
    return m_deviceId + DEVICE_FULLID_SEP + m_serviceId;
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

quint64 DeviceDiscoveryMessage::upTime() {
    return m_upTime;
}

DeviceDiscoveryMessage::DeviceHealthState DeviceDiscoveryMessage::healthState() {
    return m_healthState;
}
