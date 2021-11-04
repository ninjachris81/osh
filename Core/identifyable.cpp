#include "identifyable.h"

#include "shared/device.h"

#include <QRandomGenerator64>

Identifyable::Identifyable(QString id, QObject *parent) : QObject(parent), m_id(id)
{
    Q_ASSERT(id != nullptr);
    Q_ASSERT(!id.isEmpty());
}

QString Identifyable::id() {
    return m_id;
}

QString Identifyable::getDeviceSerialId(LocalConfig* config) {
    if (!config->exists(DEVICE_CONFIG_SERIAL_ID)) {
        config->updateValue(DEVICE_CONFIG_SERIAL_ID, generateDeviceSerialId());
    }

    return config->getString(DEVICE_CONFIG_SERIAL_ID, "");
}

QString Identifyable::generateDeviceSerialId() {
    return QString::number(QRandomGenerator64::global()->bounded(10000, INT_MAX));
}
