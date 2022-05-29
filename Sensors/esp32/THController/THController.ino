/*
 * MH ET LIVE ESP32MiniKit
 */

#include "ESPConfigurations.h"
#include "MQTTController.h"
#include "DeviceController.h"
#include "FlashController.h"
#include "LEDController.h"
#include "OTAController.h"
#include <LogHelper.h>
#include "shared/device.h"

#if HAS_TEMP_CONTROLLER
  #include "TempController_AHTx.h"
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

TaskManager taskManager;

MQTTController mqttController;
DeviceController deviceController(DEVICE_ID_PREFIX, SERVICE_ID_PREFIX);
FlashController flashController;
LEDController ledController;
OTAController otaController;

#if HAS_TEMP_CONTROLLER
  TempControllerAHTx tempController("temps", "hums");
#endif
#if HAS_MOTION_CONTROLLER
  MotionController motionController("motions");
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
  RelayControllerShutter relayController("shutters");
#endif
#if HAS_REED_CONTROLLER
  ReedController reedController("reedContacts");
#endif

void setup() {
  LOG_INIT();

  taskManager.registerTask(&mqttController, MQTT_CONTROLLER);
  taskManager.registerTask(&deviceController, DEVICE_CONTROLLER);
  taskManager.registerTask(&flashController, FLASH_CONTROLLER);
  taskManager.registerTask(&ledController, LED_CONTROLLER);
  taskManager.registerTask(&otaController, OTA_CONTROLLER);
  
#if HAS_TEMP_CONTROLLER
  taskManager.registerTask(&tempController, TEMP_CONTROLLER);
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

  taskManager.init();

  otaController.postInit(String(deviceController.getDeviceId()) + String(DEVICE_FULLID_SEP) + String(deviceController.getServiceId()));
  mqttController.setClientId(String(deviceController.getDeviceId()) + String(DEVICE_FULLID_SEP) + String(deviceController.getServiceId()));
}

void loop() {
  taskManager.update();
  delay(10);
}
