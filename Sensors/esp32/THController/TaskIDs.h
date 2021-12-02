#include "ESPConfigurations.h"

#define MQTT_CONTROLLER 0
#define DEVICE_CONTROLLER 1
#define TEMP_CONTROLLER 2
#define MOTION_CONTROLLER 3
#define BRIGHTNESS_CONTROLLER 4

#if WIFI_OTA_SUPPORT
  #define OTA_CONTROLLER 5
#endif
