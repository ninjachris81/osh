#define CONFIG_ROOM_SENSOR 0
#define CONFIG_WATER_SENSOR 1
#define CONFIG_SHUTTER_SENSOR 2
#define CONFIG_TANK_SENSOR 3

#define ACTIVE_CONFIG CONFIG_ROOM_SENSOR
//#define ACTIVE_CONFIG CONFIG_WATER_SENSOR
//#define ACTIVE_CONFIG CONFIG_SHUTTER_SENSOR
//#define ACTIVE_CONFIG CONFIG_TANK_SENSOR

#define WIFI_SSID_STALNET "Stalnet"
#define WIFI_SSID_STALNET2 "Stalnet2"
#define WIFI_SSID_HOME21 "Home21"


#if ACTIVE_CONFIG == CONFIG_ROOM_SENSOR
  #warning Room Sensor Configuration
  #define DEVICE_ID_PREFIX "00"
  #define SERVICE_ID_PREFIX "RSS-"
  #define WIFI_SSID WIFI_SSID_HOME21
  #define USES_ETH false

  #define HAS_TEMP_CONTROLLER true
  #define HAS_TEMP_CONTROLLER_ONEWIRE false
  #define HAS_MOTION_CONTROLLER true
  #define HAS_BRIGHTNESS_CONTROLLER true
  #define HAS_SOUND_CONTROLLER true
  #define HAS_FLOW_CONTROLLER false
  #define HAS_RELAY_CONTROLLER false
  #define HAS_REED_CONTROLLER false
  #define HAS_TOF_CONTROLLER false

  #define TEMP_INTERVAL_MS 6000
  #define TOF_INTERVAL_MS  2000
  #define BRIGHTNESS_INTERVAL_MS 6000
  
  #define TEMPS_VALUE_GROUP_ID "temps0"
  #define HUMS_VALUE_GROUP_ID "hums0"
#elif ACTIVE_CONFIG == CONFIG_WATER_SENSOR
  #warning Water Sensor Configuration
  #define DEVICE_ID_PREFIX "00"
  #define SERVICE_ID_PREFIX "WSS-"
  #define WIFI_SSID WIFI_SSID_HOME21
  #define USES_ETH false
  
  #define HAS_TEMP_CONTROLLER false
  #define HAS_TEMP_CONTROLLER_ONEWIRE false
  #define HAS_MOTION_CONTROLLER false
  #define HAS_BRIGHTNESS_CONTROLLER false
  #define HAS_SOUND_CONTROLLER true
  #define HAS_FLOW_CONTROLLER true
  #define HAS_RELAY_CONTROLLER false
  #define HAS_REED_CONTROLLER false
  #define HAS_TOF_CONTROLLER false

  #define TEMP_INTERVAL_MS 6000
  #define TOF_INTERVAL_MS  2000
  #define BRIGHTNESS_INTERVAL_MS 6000
  
  #define TEMPS_VALUE_GROUP_ID "temps0"
  #define HUMS_VALUE_GROUP_ID "hums0"
#elif ACTIVE_CONFIG == CONFIG_SHUTTER_SENSOR
  #warning Shutter Sensor Configuration
  #define DEVICE_ID_PREFIX "00"
  #define SERVICE_ID_PREFIX "SSS-"
  #define WIFI_SSID WIFI_SSID_HOME21
  #define USES_ETH false

  #define HAS_TEMP_CONTROLLER false
  #define HAS_TEMP_CONTROLLER_ONEWIRE false
  #define HAS_MOTION_CONTROLLER false
  #define HAS_BRIGHTNESS_CONTROLLER false
  #define HAS_SOUND_CONTROLLER true
  #define HAS_FLOW_CONTROLLER false
  #define HAS_RELAY_CONTROLLER true
  #define HAS_REED_CONTROLLER true
  #define HAS_TOF_CONTROLLER false

  #define TEMP_INTERVAL_MS 6000
  #define TOF_INTERVAL_MS  2000
  #define BRIGHTNESS_INTERVAL_MS 6000
  
  #define TEMPS_VALUE_GROUP_ID "temps0"
  #define HUMS_VALUE_GROUP_ID "hums0"
#elif ACTIVE_CONFIG == CONFIG_TANK_SENSOR
  #warning Tank Sensor Configuration
  #define DEVICE_ID_PREFIX "00"
  #define SERVICE_ID_PREFIX "TSS-"
  #define WIFI_SSID WIFI_SSID_HOME21
  #define USES_ETH true
  
  #define HAS_TEMP_CONTROLLER true
  #define HAS_TEMP_CONTROLLER_ONEWIRE true
  #define HAS_MOTION_CONTROLLER false
  #define HAS_BRIGHTNESS_CONTROLLER false
  #define HAS_SOUND_CONTROLLER false
  #define HAS_FLOW_CONTROLLER false
  #define HAS_RELAY_CONTROLLER false
  #define HAS_REED_CONTROLLER false
  #define HAS_TOF_CONTROLLER true

  #define TEMP_INTERVAL_MS 120000
  #define TOF_INTERVAL_MS  120000
  #define BRIGHTNESS_INTERVAL_MS 6000
  
  #define TEMPS_VALUE_GROUP_ID "temps1"
  #define HUMS_VALUE_GROUP_ID "hums1"
#endif
