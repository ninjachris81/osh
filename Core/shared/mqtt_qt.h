#ifndef MQTT_QT_H
#define MQTT_QT_H

#define USES_MQTT_QT

#include "mqtt.h"

#include <QObject>
#include <QVariant>

static QString MQTT_MESSAGE_TYPES[] = {
    MQTT_MESSAGE_TYPE_VA,
    MQTT_MESSAGE_TYPE_AC,
    MQTT_MESSAGE_TYPE_DD,
    MQTT_MESSAGE_TYPE_ST,
    MQTT_MESSAGE_TYPE_SW,
    MQTT_MESSAGE_TYPE_CO
};


#endif // MQTT_QT_H
