#ifndef VALUE_QT_H
#define VALUE_QT_H

#include <QObject>

#define USES_VALUE_QT

#include "constants.h"
#include "value.h"


namespace value {
Q_NAMESPACE

    enum VALUE_TYPE {
        VT_UNKNOWN = ENUM_UNKNOWN,
        VT_SWITCH = VALUE_TYPE_SWITCH,
        VT_BRIGHTNESS = VALUE_TYPE_BRIGHTNESS,
        VT_TEMP = VALUE_TYPE_TEMP,
        VT_HUMIDITY = VALUE_TYPE_HUMIDITY,
        VT_MOTION = VALUE_TYPE_MOTION,
        VT_WATER_FLOW = VALUE_TYPE_WATER_FLOW,
        VT_TIMESTAMP = VALUE_TYPE_TIMESTAMP,

        VT_RELAY_LIGHT = VALUE_TYPE_RELAY_LIGHT,
        VT_RELAY_SHUTTER = VALUE_TYPE_RELAY_SHUTTER,
        VT_ALARM_SOUND = VALUE_TYPE_ALARM_SOUND
    };

    Q_ENUM_NS(VALUE_TYPE)
}
#endif // VALUE_QT_H
