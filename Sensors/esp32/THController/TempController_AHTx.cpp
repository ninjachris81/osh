#include "TempController_AHTx.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>

TempControllerAHTx::TempControllerAHTx(String valueGroupTemp, String valueIdTemp, String valueGroupHum, String valueIdHum) : AbstractIntervalTask(TEMP_INTERVAL_MS), m_valueGroupTemp(valueGroupTemp), m_valueIdTemp(valueIdTemp), m_valueGroupHum(valueGroupHum), m_valueIdHum(valueIdHum) {
  
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
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupTemp + String(MQTT_PATH_SEP) + m_valueIdTemp), temp.temperature);
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupHum + String(MQTT_PATH_SEP) + m_valueIdHum), humidity.relative_humidity);
}
