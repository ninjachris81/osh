#include "MotionController.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/value.h"
#include "FlashController.h"

MotionController::MotionController(String valueGroupPir, String valueGroupRadar) : AbstractIntervalTask(MOTION_INTERVAL_MS), m_valueGroupPir(valueGroupPir), m_valueGroupRadar(valueGroupRadar) {
  
}

void MotionController::init() {
  radarController.init();
  pirController.init();

  m_statusRadar.init(PROPERTY_MOTION_RADAR, false);
  m_statusRadar.registerValueChangeListener(this);
  
  m_statusPir.init(PROPERTY_MOTION_PIR, false);
  m_statusPir.registerValueChangeListener(this);
}

void MotionController::update() {
  radarController.update();
  pirController.update();

  m_statusRadar.setValue(radarController.getStatus());
  m_statusPir.setValue(pirController.getStatus());

  /*
  LOG_PRINT("Radar: ");
  LOG_PRINTLN(radarController.getStatus());
  LOG_PRINT("PIR: ");
  LOG_PRINTLN(pirController.getStatus());
  */

  if (millis() - m_lastSend > (VALUE_TIMEOUT_MID / 2)) {
    sendValue();
  }
}

void MotionController::onPropertyValueChange(uint8_t id, bool newValue, bool oldValue) {
  switch(id) {
    case PROPERTY_MOTION_RADAR:
      sendValueRadar();
      break;
    case PROPERTY_MOTION_PIR:
      sendValuePir();
      break;
  }
}

void MotionController::sendValue() {
  sendValuePir();
  sendValueRadar();
  m_lastSend = millis();
}

void MotionController::sendValueRadar() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupRadar + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_statusRadar.getValue());
}

void MotionController::sendValuePir() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupPir + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_statusPir.getValue());
}
