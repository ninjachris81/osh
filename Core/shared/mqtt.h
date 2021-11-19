#ifndef MQTT_H
#define MQTT_H

#ifdef QT_VERSION
    #ifndef USES_MQTT_QT
        #error Should use Qt version
    #endif
#endif

/*
 * ROOT             TYPE             1st Level        2nd Level
 *
 * Value Structure:
 * MQTT_BASE_PATH / (message_type) / (valueGroupId) / (valueId)
 *
 * Actor Structure:
 * MQTT_BASE_PATH / (message_type) / (actorGroupId) / (actorId)
 *
 * Device Discovery Structure:
 * MQTT_BASE_PATH / (message_type) / (deviceId) / (serviceId)
 *
 * System Time Structure
 * MQTT_BASE_PATH / (message_type)
 *
 * System Warn Structure
 * MQTT_BASE_PATH / (message_type) / (deviceId)
 *
 * Controller Structure:
 * MQTT_BASE_PATH / (message_type) / (controllerId)
 *
 * Log Structure
 * MQTT_BASE_PATH / (message_type) / (deviceId)
*/


#define MQTT_PATH_SEP "/"
#define MQTT_BASE_PATH "osh"
#define MQTT_WILDCARD "#"

// types
#define MQTT_MESSAGE_TYPE_VA            "va"        // value
#define MQTT_MESSAGE_TYPE_AC            "ac"        // actor
#define MQTT_MESSAGE_TYPE_DD            "dd"        // device discovery
#define MQTT_MESSAGE_TYPE_ST            "st"        // system time
#define MQTT_MESSAGE_TYPE_SW            "sw"        // system warnings
#define MQTT_MESSAGE_TYPE_CO            "co"        // controller
#define MQTT_MESSAGE_TYPE_LO            "lo"        // log

// devices

#define MQTT_MIN_MSG_SIZE 2

// TYPES
#define MQTT_ID_DOUBLE 'd'
#define MQTT_ID_INTEGER 'i'
#define MQTT_ID_STRING 's'
#define MQTT_ID_BOOL 'b'
#define MQTT_ID_LONG 'l'
#define MQTT_ID_INVALID 'n'

#define MQTT_INVALID_PAYLOAD ' '


#endif // MQTT_H
