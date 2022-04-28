#ifndef VALUE_H
#define VALUE_H

#ifdef QT_VERSION
    #ifndef USES_VALUE_QT
        #error Should use Qt version
    #endif
#endif

#define VALUE_TIMEOUT_SHORT 5000
#define VALUE_TIMEOUT_MID 30000
#define VALUE_TIMEOUT_LONG 120000

// values
#define VALUE_TYPE_SWITCH       0
#define VALUE_TYPE_BRIGHTNESS   1
#define VALUE_TYPE_TEMP         2
#define VALUE_TYPE_HUMIDITY     3
#define VALUE_TYPE_MOTION       4
#define VALUE_TYPE_WATER_FLOW   5
#define VALUE_TYPE_WATER_LEVEL   6
#define VALUE_TYPE_TIMESTAMP    7

// actors
#define VALUE_TYPE_RELAY_LIGHT  50
#define VALUE_TYPE_RELAY_SHUTTER    51
#define VALUE_TYPE_ALARM_SOUND  60


#endif // VALUE_H
