/*
 * MH ET LIVE ESP32MiniKit
 */

#include "ESPConfigurations.h"
#include "MQTTController.h"
#include "DeviceController.h"
#include "FlashController.h"
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

#if HAS_OTA_SUPPORT
  #include "OTAController.h"
#endif

TaskManager taskManager;

MQTTController mqttController;
DeviceController deviceController(DEVICE_ID_PREFIX, SERVICE_ID_PREFIX);
FlashController flashController;

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
#if HAS_OTA_SUPPORT
  OTAController otaController;
#endif

void setup() {
  LOG_INIT();

  taskManager.registerTask(&mqttController, MQTT_CONTROLLER);
  taskManager.registerTask(&deviceController, DEVICE_CONTROLLER);
  taskManager.registerTask(&flashController, FLASH_CONTROLLER);

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

#if HAS_OTA_SUPPORT
  taskManager.registerTask(&otaController, OTA_CONTROLLER);
#endif

  taskManager.init();

  mqttController.setClientId(String(deviceController.getDeviceId()) + String(DEVICE_FULLID_SEP) + String(deviceController.getServiceId()));
}

void loop() {
  taskManager.update();
  delay(100);
}
