/*
 * MH ET LIVE ESP32MiniKit
 */

#include "ESPConfigurations.h"
#include "FlashController.h"
#include "DeviceController.h"
#include "LEDController.h"
#include "MQTTController.h"
#include "OTAController.h"
#include <LogHelper.h>
#include "shared/device.h"
#include "Pins.h"

#if USES_ETH
  //#include "EthController.h"
#else
  #include "WifiController.h"
#endif
#if HAS_TEMP_CONTROLLER
  #include "TempController_AHTx.h"
#endif
#if HAS_TEMP_CONTROLLER_ONEWIRE
    #include "TempController_DS18x.h"
#endif
#if HAS_MOTION_CONTROLLER
  #include "MotionController.h"
  #include "MotionController_RCWL0516.h"
#endif
#if HAS_BRIGHTNESS_CONTROLLER
  #include "BrightnessController_GL55x.h"
#endif
#if HAS_SOUND_CONTROLLER
  #include "SoundController_Piezo.h"
#endif
#if HAS_FLOW_CONTROLLER
  #include "FlowController_Reed.h"
#endif
#if HAS_RELAY_CONTROLLER
  #include "RelayController_Shutter.h"
#endif
#if HAS_REED_CONTROLLER
  #include "ReedController.h"
#endif
#if HAS_TOF_CONTROLLER
  #include "TOFController_AJSR04M.h"
#endif

TaskManager taskManager;

FlashController flashController;
DeviceController deviceController(DEVICE_ID_PREFIX, SERVICE_ID_PREFIX);
LEDController ledController;
#if USES_ETH
  EthController ethController;
#else
  WifiController wifiController;
#endif
MQTTController mqttController;
OTAController otaController;

#if HAS_TEMP_CONTROLLER
  TempControllerAHTx tempController(TEMPS_VALUE_GROUP_ID, HUMS_VALUE_GROUP_ID);
#endif
#if HAS_TEMP_CONTROLLER_ONEWIRE
  TempControllerDS18x tempControllerOneWire(TEMPS_VALUE_GROUP_ID);
#endif
#if HAS_MOTION_CONTROLLER
  MotionController motionController("motions_pirs", "motions_radars");
#endif
#if HAS_BRIGHTNESS_CONTROLLER
  BrightnessControllerGL55x brightnessController("brightnesses");
#endif
#if HAS_SOUND_CONTROLLER
  SoundControllerPiezo soundController("alarms");
#endif
#if HAS_FLOW_CONTROLLER
  FlowControllerReed flowController("waterflows");
#endif
#if HAS_RELAY_CONTROLLER
  RelayControllerShutter relayController("shutters", "closeStates", "tiltStates");
#endif
#if HAS_REED_CONTROLLER
  ReedController reedController("reedContacts");
#endif
#if HAS_TOF_CONTROLLER
  TOFControllerAJSR04M tofController("waterLevels1");
#endif

void setup() {
  LOG_INIT();

  taskManager.setDebugOutput(&Serial);

  taskManager.registerTask(&flashController, FLASH_CONTROLLER);
  taskManager.registerTask(&deviceController, DEVICE_CONTROLLER);
  taskManager.registerTask(&ledController, LED_CONTROLLER);
  
#if USES_ETH
  taskManager.registerTask(&ethController, ETH_WIFI_CONTROLLER);
  mqttController.setClient(ethController.getClient());
#else
  taskManager.registerTask(&wifiController, ETH_WIFI_CONTROLLER);
  mqttController.setClient(wifiController.getClient());
#endif

  taskManager.registerTask(&mqttController, MQTT_CONTROLLER);
  taskManager.registerTask(&otaController, OTA_CONTROLLER);
  
#if HAS_TEMP_CONTROLLER
  taskManager.registerTask(&tempController, TEMP_CONTROLLER);
#endif
#if HAS_TEMP_CONTROLLER_ONEWIRE
  taskManager.registerTask(&tempControllerOneWire, TEMP_CONTROLLER_ONEWIRE);
#endif
#if HAS_MOTION_CONTROLLER
  taskManager.registerTask(&motionController, MOTION_CONTROLLER);
#endif
#if HAS_BRIGHTNESS_CONTROLLER
  taskManager.registerTask(&brightnessController, BRIGHTNESS_CONTROLLER);
#endif
#if HAS_SOUND_CONTROLLER
  taskManager.registerTask(&soundController, SOUND_CONTROLLER);
#endif
#if HAS_FLOW_CONTROLLER
  taskManager.registerTask(&flowController, FLOW_CONTROLLER);
#endif
#if HAS_RELAY_CONTROLLER
  taskManager.registerTask(&relayController, RELAY_CONTROLLER);
#endif
#if HAS_REED_CONTROLLER
  taskManager.registerTask(&reedController, REED_CONTROLLER);
#endif
#if HAS_TOF_CONTROLLER
  taskManager.registerTask(&tofController, TOF_CONTROLLER);
#endif

  taskManager.init();
}

void loop() {
  taskManager.update();
  delay(10);
}
