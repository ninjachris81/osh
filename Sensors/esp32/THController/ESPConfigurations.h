#define CONFIG_ROOM_SENSOR 0
#define CONFIG_WATER_SENSOR 1

//#define ACTIVE_CONFIG CONFIG_ROOM_SENSOR
#define ACTIVE_CONFIG CONFIG_WATER_SENSOR

#define WIFI_SSID_STALNET "Stalnet"
#define WIFI_SSID_STALNET2 "Stalnet2"

#if ACTIVE_CONFIG == CONFIG_ROOM_SENSOR
  #warning Room Sensor Configuration
  #define DEVICE_ID_PREFIX "00"
  #define SERVICE_ID_PREFIX "RSS_"
  #define WIFI_SSID WIFI_SSID_STALNET2

  #define HAS_TEMP_CONTROLLER true
  #define HAS_MOTION_CONTROLLER true
  #define HAS_BRIGHTNESS_CONTROLLER true
  #define HAS_SOUND_CONTROLLER true
  #define HAS_OTA_SUPPORT true
#elif ACTIVE_CONFIG == CONFIG_WATER_SENSOR
  #warning Water Sensor Configuration
  #define DEVICE_ID_PREFIX "00"
  #define SERVICE_ID_PREFIX "WSS_"
  #define WIFI_SSID WIFI_SSID_STALNET2
  
  #define HAS_TEMP_CONTROLLER false
  #define HAS_MOTION_CONTROLLER false
  #define HAS_BRIGHTNESS_CONTROLLER false
  #define HAS_SOUND_CONTROLLER false
  #define HAS_OTA_SUPPORT true
#endif
