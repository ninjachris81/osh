#include "MotionController.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/value.h"
#include "FlashController.h"

MotionController::MotionController(String valueGroupStatus) : AbstractIntervalTask(MOTION_INTERVAL_MS), m_valueGroupStatus(valueGroupStatus) {
  
}

void MotionController::init() {
  radarController.init();
  pirController.init();

  m_status.init(false, 0);
  m_status.registerValueChangeListener(this);
}

void MotionController::update() {
  radarController.update();
  pirController.update();

  m_status.setValue(radarController.getStatus() || pirController.getStatus());

  LOG_PRINT("Radar: ");
  LOG_PRINTLN(radarController.getStatus());
  LOG_PRINT("PIR: ");
  LOG_PRINTLN(pirController.getStatus());

  if (millis() - m_lastSend > (VALUE_TIMEOUT_MID / 2)) {
    sendValue();
  }
}

void MotionController::onPropertyValueChange(uint8_t id, bool newValue, bool oldValue) {
  sendValue();
}

void MotionController::sendValue() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupStatus + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_status.getValue());
  m_lastSend = millis();
}
