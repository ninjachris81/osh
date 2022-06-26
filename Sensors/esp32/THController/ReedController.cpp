#include "ReedController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "MQTTController.h"
#include "FlashController.h"

ReedController::ReedController(String valueGroupStatus) : AbstractIntervalTask(FLOW_UPDATE_INTERVAL_MS), m_valueGroupStatus(valueGroupStatus) {
}

void ReedController::init() {
  pinMode(PIN_REED_SENSOR_1_CHECK, INPUT_PULLUP);
  pinMode(PIN_REED_SENSOR_1_VALUE, INPUT_PULLUP);
  pinMode(PIN_REED_SENSOR_2_CHECK, INPUT_PULLUP);
  pinMode(PIN_REED_SENSOR_2_VALUE, INPUT_PULLUP);
}

void ReedController::update() {
  int s1Check = digitalRead(PIN_REED_SENSOR_1_CHECK);
  if (s1Check == LOW) {
    int s1Val = digitalRead(PIN_REED_SENSOR_1_VALUE);
    taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupStatus + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), s1Val == LOW ? true : false);
  } else {
    LOG_PRINTLN(F("Reed 1 not connected"));
  }
  
  int s2Check = digitalRead(PIN_REED_SENSOR_2_CHECK);
  if (s2Check == LOW) {
    int s2Val = digitalRead(PIN_REED_SENSOR_2_VALUE);
    taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupStatus + String(MQTT_PATH_SEP) + String((taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex() + 1))), s2Val == LOW ? true : false);
  } else {
    LOG_PRINTLN(F("Reed 2 not connected"));
  }
}
