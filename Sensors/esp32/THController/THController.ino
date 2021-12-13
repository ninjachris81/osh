
#include "ESPConfigurations.h"
#include "MQTTController.h"
#include "DeviceController.h"
#include "TempController_AHTx.h"
#include "MotionController_SR501.h"
#include "BrightnessController_GL55x.h"
#include "SoundController_Piezo.h"
#include <LogHelper.h>

#if WIFI_OTA_SUPPORT
  #include "OTAController.h"
#endif

TaskManager taskManager;

MQTTController mqttController;
DeviceController deviceController(DEVICE_ID, SERVICE_ID);

TempControllerAHTx tempController("temps", "0", "hums", "0");
MotionControllerSR501 motionController("motions", "0");
BrightnessControllerGL55x brightnessController("brightnesses", "0");
SoundControllerPiezo soundController("alarms", "0");

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

#if WIFI_OTA_SUPPORT
  taskManager.registerTask(&otaController);
#endif

  taskManager.init();
}

void loop() {
  taskManager.update();
  delay(100);
}
