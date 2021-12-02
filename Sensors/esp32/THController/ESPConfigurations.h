#define CONFIG_ROOM_SENSOR 0

#define ACTIVE_CONFIG CONFIG_ROOM_SENSOR

#define WIFI_SSID_STALNET "Stalnet"
#define WIFI_SSID_STALNET2 "Stalnet2"

#if ACTIVE_CONFIG == CONFIG_ROOM_SENSOR
  #warning Room Sensor Configuration
  #define DEVICE_ID "00001"
  #define SERVICE_ID "THService1"
  #define WIFI_SSID WIFI_SSID_STALNET2
  #define WIFI_OTA_SUPPORT true
#endif
