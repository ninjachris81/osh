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
#include "TempController_DS18x.h"
#include "AnalogInputController.h"

TaskManager taskManager;

FlashController flashController;
DeviceController deviceController(DEVICE_ID_PREFIX, SERVICE_ID_PREFIX);
LEDController ledController;
WifiController wifiController;
MQTTController mqttController;
OTAController otaController;
RelayController relayController(RELAY_VALUE_GROUP_ID, RELAY_VALUE_INDEX);
TempControllerDS18x tempControllerOneWire(TEMPS_VALUE_GROUP_ID, TEMPS_VALUE_INDEX);
AnalogInputController analogInputController(ANALOG_INPUT_VALUE_GROUP_ID, ANALOG_INPUT_VALUE_INDEX);

void setup() {
  Serial.begin(115200);
  
  taskManager.registerTask(&flashController, FLASH_CONTROLLER);
  taskManager.registerTask(&deviceController, DEVICE_CONTROLLER);
  taskManager.registerTask(&ledController, LED_CONTROLLER);
  
  taskManager.registerTask(&wifiController, ETH_WIFI_CONTROLLER);
  mqttController.setClient(wifiController.getClient());

  taskManager.registerTask(&mqttController, MQTT_CONTROLLER);
  taskManager.registerTask(&otaController, OTA_CONTROLLER);
  taskManager.registerTask(&relayController, RELAY_CONTROLLER);

  taskManager.registerTask(&tempControllerOneWire, TEMP_CONTROLLER_ONEWIRE);
  taskManager.registerTask(&analogInputController, ANALOG_INPUT_CONTROLLER);

  taskManager.init();
}

void loop() {
  taskManager.update();
  delay(10);
}
