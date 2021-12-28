
#include "ESPConfigurations.h"
#include "MQTTController.h"
#include "DeviceController.h"
#include "TempController_AHTx.h"
#include "MotionController_SR501.h"
#include "BrightnessController_GL55x.h"
#include "SoundController_Piezo.h"
#include "FlashController.h"
#include <LogHelper.h>
#include "shared/device.h"

#if WIFI_OTA_SUPPORT
  #include "OTAController.h"
#endif

TaskManager taskManager;

MQTTController mqttController;
DeviceController deviceController(DEVICE_ID_PREFIX, SERVICE_ID_PREFIX);

TempControllerAHTx tempController("temps", "hums");
MotionControllerSR501 motionController("motions");
BrightnessControllerGL55x brightnessController("brightnesses");
SoundControllerPiezo soundController("alarms");
FlashController flashController;

#if WIFI_OTA_SUPPORT
  OTAController otaController;
#endif

void setup() {
  LOG_INIT();

  taskManager.registerTask(&mqttController);
  taskManager.registerTask(&deviceController);
  taskManager.registerTask(&tempController);
  taskManager.registerTask(&motionController);
  taskManager.registerTask(&brightnessController);
  taskManager.registerTask(&soundController);
  taskManager.registerTask(&flashController);

#if WIFI_OTA_SUPPORT
  taskManager.registerTask(&otaController);
#endif

  taskManager.init();

  mqttController.setClientId(String(deviceController.getDeviceId()) + String(DEVICE_FULLID_SEP) + String(deviceController.getServiceId()));
}

void loop() {
  taskManager.update();
  delay(100);
}
