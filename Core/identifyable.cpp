#include "identifyable.h"

#include "shared/device.h"

#include <QRandomGenerator64>

QLatin1String Identifyable::PROPERTY_ID = QLatin1String("id");
QLatin1String Identifyable::PROPERTY_CLASSTYPE = QLatin1String("class_type");
QLatin1String Identifyable::PROPERTY_VALUE_GROUP_ID = QLatin1String("value_group_id");

Identifyable::Identifyable(QString id) : m_id(id)
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
