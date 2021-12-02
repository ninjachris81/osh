#include "MotionController_SR501.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/value.h"

MotionControllerSR501::MotionControllerSR501(String valueGroupStatus, String valueIdStatus) : AbstractIntervalTask(MOTION_INTERVAL_MS), m_valueGroupStatus(valueGroupStatus), m_valueIdStatus(valueIdStatus) {
  
}

MotionControllerSR501::~MotionControllerSR501() {
}

void MotionControllerSR501::init() {
  m_status.init(false, 0);
  m_status.registerValueChangeListener(this);
  pinMode(PIN_MOTION_SENSOR, INPUT);
}

void MotionControllerSR501::update() {
  m_countsSec++;
  if (digitalRead(PIN_MOTION_SENSOR)==HIGH) {
    m_highCountsSec++;
  }

  if (m_countsSec>=10) {
    //LOG_PRINTLN(m_highCountsSec);
    //LOG_PRINTLN(m_status.getValue());

    m_status.setValue(m_highCountsSec > 5);
    m_countsSec = 0;
    m_highCountsSec = 0;
  }

  if (millis() - m_lastSend > (VALUE_TIMEOUT_MID / 2)) {
    sendValue();
  }
}

void MotionControllerSR501::onPropertyValueChange(uint8_t id, bool newValue, bool oldValue) {
  LOG_PRINTLN(F("PIR changed"));
  sendValue();
}

void MotionControllerSR501::sendValue() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupStatus + String(MQTT_PATH_SEP) + m_valueIdStatus), m_status.getValue());
  m_lastSend = millis();
}
