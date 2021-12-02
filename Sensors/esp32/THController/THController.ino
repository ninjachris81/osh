
#include "ESPConfigurations.h"
#include "MQTTController.h"
#include "TempController_AHTx.h"
#include "DeviceController.h"
#include <LogHelper.h>

#if WIFI_OTA_SUPPORT
  #include "OTAController.h"
#endif

TaskManager taskManager;

MQTTController mqttController;
DeviceController deviceController(DEVICE_ID, SERVICE_ID);

TempControllerAHTx tempController;

#if WIFI_OTA_SUPPORT
  OTAController otaController;
#endif

void setup() {
  LOG_INIT();

  taskManager.registerTask(&mqttController);
  taskManager.registerTask(&deviceController);
  taskManager.registerTask(&tempController);

#if WIFI_OTA_SUPPORT
  taskManager.registerTask(&otaController);
#endif

  taskManager.init();
}

void loop() {
  taskManager.update();
  delay(100);
}
