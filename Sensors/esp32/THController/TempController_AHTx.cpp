#include "TempController_AHTx.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>

TempControllerAHTx::TempControllerAHTx() : AbstractIntervalTask(TEMP_INTERVAL_MS) {
  
}

TempControllerAHTx::~TempControllerAHTx() {
}

void TempControllerAHTx::init() {
  if (! aht.begin()) {
    LOG_PRINTLN(F("Could not find AHT"));
    while (1) delay(10);
  }
}

void TempControllerAHTx::update() {
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + "egTemps0" + String(MQTT_PATH_SEP) + String("0")), temp.temperature);
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + "egHums0" + String(MQTT_PATH_SEP) + String("0")), humidity.relative_humidity);
}
