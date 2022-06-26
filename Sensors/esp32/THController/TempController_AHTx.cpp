#include "TempController_AHTx.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "FlashController.h"

TempControllerAHTx::TempControllerAHTx(String valueGroupTemp, String valueGroupHum) : AbstractIntervalTask(TEMP_INTERVAL_MS), m_valueGroupTemp(valueGroupTemp), m_valueGroupHum(valueGroupHum) {
  
}

TempControllerAHTx::~TempControllerAHTx() {
}

void TempControllerAHTx::init() {
}

void TempControllerAHTx::update() {
    if (!isInitialized) {
    if (!aht.begin()) {
      LOG_PRINTLN(F("Could not find AHT"));
    } else {
      isInitialized = true;
    }
  } else {
    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
    taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupTemp + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), temp.temperature);
    taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupHum + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), humidity.relative_humidity);
  }
}
