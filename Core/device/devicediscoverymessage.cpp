#include "devicediscoverymessage.h"
#include "shared/device.h"
#include "shared/mqtt_qt.h"

#include <QDateTime>

DeviceDiscoveryMessage::DeviceDiscoveryMessage(QString deviceId, QString serviceId, QObject *parent) : MessageBase(parent), m_deviceId(deviceId), m_serviceId(serviceId)
{
    m_deviceInfos.insert(MQTT_SINGLE_VALUE_ATTR, QDateTime::currentMSecsSinceEpoch());
}

DeviceDiscoveryMessage::DeviceDiscoveryMessage(QString deviceId, QString serviceId, QVariantMap deviceInfos, QObject *parent) : MessageBase(parent), m_deviceId(deviceId), m_serviceId(serviceId), m_deviceInfos(deviceInfos)
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

QVariantMap DeviceDiscoveryMessage::deviceInfos() {
    return m_deviceInfos;
}
