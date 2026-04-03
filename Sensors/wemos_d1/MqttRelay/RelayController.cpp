#include "RelayController.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/actor.h"
#include "shared/value.h"
#include "FlashController.h"
#include "LEDController.h"

RelayController::RelayController(String valueGroupState, int valueIndex) : AbstractIntervalTask(500), m_valueGroupState(valueGroupState), m_valueIndex(valueIndex)
{
}

RelayController::~RelayController() {
}

void RelayController::init() {
  pinMode(PIN_RELAY, OUTPUT);
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->registerHandler(this);
  switchRelay(false);
  m_lastAction = millis();
}

void RelayController::update() {
  // check send bc
  if (millis() - m_lastSend > (VALUE_TIMEOUT_MID / 2)) {
    sendState();
  }

  if (millis() - m_lastAction > RENEWAL_INTERVAL) {
    switchRelay(false);
  }
}

void RelayController::onMsgReceived(String topic, int value) {
  LOG_PRINT(F("SHUTTER ACTOR MSG "));
  LOG_PRINTLN(value);

  m_lastAction = millis();

  if (value == ACTOR_ON) {
    switchRelay(true);
  } else if (value == ACTOR_OFF) {
    switchRelay(false);
  } else {
    LOG_PRINTLN(F("Invalid cmd"));
  }
}


String RelayController::getTopics() {
  return BUILD_PATH(MQTT_MESSAGE_TYPE_AC + String(MQTT_PATH_SEP) + m_valueGroupState + String(MQTT_PATH_SEP) + String(m_valueIndex)) + String(TOPIC_DELIMITER);
}

void RelayController::sendState() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupState + String(MQTT_PATH_SEP) + String(m_valueIndex)), m_state);
  m_lastSend = millis();
}

bool RelayController::switchRelay(bool state) {
  if (state == m_state) return false;

  m_state = state;

  digitalWrite(PIN_RELAY, state ? HIGH : LOW);
  
  sendState();
  
  return true;
}
