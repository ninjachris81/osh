#include "devicebase.h"

#include <QDateTime>
#include <QRandomGenerator64>

#include "device/devicediscoverymanagerbase.h"

DeviceBase::DeviceBase(QString id, QString serviceId, QObject *parent) : Identifyable(id, parent), m_serviceId(serviceId) {
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
    return m_id + "." + m_serviceId;
}

QString DeviceBase::serviceId() {
    return m_serviceId;
}
