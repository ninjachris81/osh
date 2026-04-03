/*
 * ESP-01
 */

#include "ESPConfigurations.h"
#include "FlashController.h"
#include "DeviceController.h"
#include "LEDController.h"
#include "MQTTController.h"
#include "OTAController.h"
#include <LogHelper.h>
#include "Pins.h"
#include "WifiController.h"
#include "RelayController.h"

TaskManager taskManager;

FlashController flashController;
DeviceController deviceController(DEVICE_ID_PREFIX, SERVICE_ID_PREFIX);
LEDController ledController;
WifiController wifiController;
MQTTController mqttController;
OTAController otaController;
RelayController relayControllerUp(0x01);
RelayController relayControllerDown(0x02);


void setup() {
  Serial.begin(115200);
  
  taskManager.registerTask(&flashController, FLASH_CONTROLLER);
  taskManager.registerTask(&deviceController, DEVICE_CONTROLLER);
  taskManager.registerTask(&ledController, LED_CONTROLLER);
  
  taskManager.registerTask(&wifiController, ETH_WIFI_CONTROLLER);
  mqttController.setClient(wifiController.getClient());

  taskManager.registerTask(&mqttController, MQTT_CONTROLLER);
  taskManager.registerTask(&otaController, OTA_CONTROLLER);
  taskManager.registerTask(&relayControllerUp, RELAY_CONTROLLER_UP);
  taskManager.registerTask(&relayControllerDown, RELAY_CONTROLLER_DOWN);

  taskManager.init();

  relayControllerUp.lateInit(&relayControllerDown, RELAY_VALUE_GROUP_ID, 0);
  relayControllerDown.lateInit(&relayControllerUp, RELAY_VALUE_GROUP_ID, 1);
}

void loop() {
  taskManager.update();
  delay(10);
}
