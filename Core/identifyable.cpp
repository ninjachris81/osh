#include "identifyable.h"

#include "shared/device.h"

#include <QRandomGenerator64>

Identifyable::Identifyable(QString id, QObject *parent) : QObject(parent), m_id(id)
{
}

QString Identifyable::id() {
    return m_id;
}

LogCat::LOGCAT  Identifyable::logCat() {
    return LogCat::LOGCAT::COMMON;
}

QString Identifyable::logCatName() {
    return LogCat::LOGGING_CATEGORIES[logCat()] + "." + id();
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
