#define CONFIG_ROOM_SENSOR 0

#define ACTIVE_CONFIG CONFIG_ROOM_SENSOR

#define WIFI_SSID_STALNET "Stalnet"
#define WIFI_SSID_STALNET2 "Stalnet2"

#if ACTIVE_CONFIG == CONFIG_ROOM_SENSOR
  #warning Room Sensor Configuration
  #define DEVICE_ID_PREFIX "00"
  #define SERVICE_ID_PREFIX "SensorService_"
  #define WIFI_SSID WIFI_SSID_STALNET2
  #define WIFI_OTA_SUPPORT true
#endif
