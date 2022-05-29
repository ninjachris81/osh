#include "RelayController_Shutter.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/actor.h"
#include "shared/value.h"
#include "FlashController.h"

RelayControllerShutter::RelayControllerShutter(String valueGroup) : AbstractIntervalTask(250), m_valueGroup(valueGroup) {
  m_state.init(0, ACTOR_OFF);
  m_state.registerValueChangeListener(this);
}

RelayControllerShutter::~RelayControllerShutter() {
}

void RelayControllerShutter::init() {
  pinMode(PIN_RELAY_UP, OUTPUT);
  pinMode(PIN_RELAY_DOWN, OUTPUT);
  digitalWrite(PIN_RELAY_UP, HIGH);
  digitalWrite(PIN_RELAY_DOWN, HIGH);
  
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->registerHandler(this);
}

void RelayControllerShutter::update() {
  // check send bc
  if (millis() - m_lastSend > (VALUE_TIMEOUT_MID / 2)) {
    sendValue();
  }

  // check duration
  if (m_lastAction > 0 && millis() - m_lastAction > SHUTTER_DURATION_MS) {
    LOG_PRINTLN(F("Shutter timeout"));
    m_state.setValue(ACTOR_OFF);
  }
}

void RelayControllerShutter::onMsgReceived(String topic, int value) {
  LOG_PRINT(F("SHUTTER ACTOR MSG "));
  LOG_PRINTLN(value);
  
  m_state.setValue(value);
}


String RelayControllerShutter::getTopics() {
  return BUILD_PATH(MQTT_MESSAGE_TYPE_AC + String(MQTT_PATH_SEP) + m_valueGroup + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())) + String(TOPIC_DELIMITER);
}

void RelayControllerShutter::onPropertyValueChange(uint8_t id, int newValue, int oldValue) {
  if (newValue == ACTOR_UP) {
    LOG_PRINTLN(F("Shutter up"));
    switchRelay(true, false);
    m_lastAction = millis();
  } else if (newValue == ACTOR_DOWN) {
    LOG_PRINTLN(F("Shutter down"));
    switchRelay(false, true);
    m_lastAction = millis();
  } else {
    LOG_PRINTLN(F("Shutter stop"));
    switchRelay(false, false);
    m_lastAction = 0;
  }
  
  sendValue();
}

void RelayControllerShutter::sendValue() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroup + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_state.getValue());
  m_lastSend = millis();
}

void RelayControllerShutter::switchRelay(bool relayUp, bool relayDown) {
  // first switch OFF  
  if (!relayUp) {
    digitalWrite(PIN_RELAY_UP, HIGH);
  }
  if (!relayDown) {
    digitalWrite(PIN_RELAY_DOWN, HIGH);
  }
  
  // then, switch ON
  if (relayUp || relayDown) {
    delay(500);
    if (relayUp) {
      digitalWrite(PIN_RELAY_UP, LOW);
    }
    if (relayDown) {
      digitalWrite(PIN_RELAY_DOWN, LOW);
    }
  }
}
