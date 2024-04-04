#include "devicebase.h"

#include <QDateTime>
#include <QRandomGenerator64>

#include "device/devicediscoverymanagerbase.h"
#include "shared/device.h"

DeviceBase::DeviceBase() : SerializableIdentifyable() {
}

DeviceBase::DeviceBase(QString id, QString serviceId, QObject *parent) : QObject(parent), SerializableIdentifyable(id), m_serviceId(serviceId) {
}

void DeviceBase::serialize(QJsonObject &obj) {
    SerializableIdentifyable::serialize(obj);
    obj.insert("serviceId", m_serviceId);
}

void DeviceBase::deserialize(QJsonObject obj) {
    SerializableIdentifyable::deserialize(obj);
    m_serviceId = obj.value("serviceId").toString();
}

QString DeviceBase::getClassName() {
    return metaObject()->className();
}

void DeviceBase::updatePing() {
    m_lastPing = QDateTime::currentMSecsSinceEpoch();

    Q_EMIT(lastPingChanged());

    if (!m_isOnline) {
        m_isOnline = true;
        Q_EMIT(isOnlineChanged());
    }
}

void DeviceBase::updateOnline(qint64 onlineTimeout) {
    bool isOnline = QDateTime::currentMSecsSinceEpoch() < m_lastPing + onlineTimeout;

    if (isOnline != m_isOnline) {
        m_isOnline = isOnline;
        Q_EMIT(isOnlineChanged());
    }
}

qint64 DeviceBase::lastPing() {
    return m_lastPing;
}

bool DeviceBase::isOnline() {
    return m_isOnline;
}

QString DeviceBase::fullId() {
    return m_id + DEVICE_FULLID_SEP + m_serviceId;
}

QString DeviceBase::serviceId() {
    return m_serviceId;
}

