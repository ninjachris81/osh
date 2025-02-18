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
#define VALUE_TYPE_BRIGHTNESS       1
#define VALUE_TYPE_TEMP             2
#define VALUE_TYPE_HUMIDITY         3
#define VALUE_TYPE_MOTION           4
#define VALUE_TYPE_WATER_FLOW       5
#define VALUE_TYPE_WATER_LEVEL      6
#define VALUE_TYPE_TIMESTAMP        7
#define VALUE_TYPE_ENERGY_CONS      8
#define VALUE_TYPE_ENERGY_CONS_TIME 9
#define VALUE_TYPE_SWITCH           10

#define VALUE_TYPE_SHUTTER_CLOSE_STATE  30
#define VALUE_TYPE_SHUTTER_TILT_STATE   31
#define VALUE_TYPE_SHUTTER_MODE         32

#define VALUE_TYPE_MOTION_RADAR 40
#define VALUE_TYPE_MOTION_PIR   41
#define VALUE_TYPE_REED_CONTACT 42

// actors
#define VALUE_TYPE_RELAY_LIGHT      50
#define VALUE_TYPE_RELAY_SHUTTER    51
#define VALUE_TYPE_RELAY_TEMP_VALVE 52
#define VALUE_TYPE_RELAY_DOOR_OPEN  53

#define VALUE_TYPE_AUDIO            60
#define VALUE_TYPE_AUDIO_VOLUME     61
#define VALUE_TYPE_ALARM_SOUND      62
#define VALUE_TYPE_SOUND_URL        63

#define VALUE_TYPE_DOOR             70
#define VALUE_TYPE_HEAT_PUMP_DATA   80

#define VALUE_TYPE_VIRTUAL_ACTOR    90

// static vars
#define VALUE_TYPE_STATIC_TEMP  100

#endif // VALUE_H
