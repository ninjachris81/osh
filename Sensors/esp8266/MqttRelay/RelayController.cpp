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

RelayController::RelayController(byte relayIndex) : AbstractIntervalTask(500), m_relayIndex(relayIndex) {
}

RelayController::~RelayController() {
}

void RelayController::init() {
}

void RelayController::lateInit(RelayController* invertController, String valueGroupState, int valueIndex) {
  m_valueGroupState = valueGroupState;
  m_valueIndex = valueIndex;
  m_invertController = invertController;

  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->registerHandler(this);
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
  byte stateByte;
  if (state == m_state) return false;
  
  if (state) {
    if (m_invertController->switchRelay(false)) {
      delay(500);
    }
    stateByte = 0x01;
  } else {
    stateByte = 0x00;
  }

  Serial.write(0xA0);
  Serial.write(m_relayIndex);
  Serial.write(stateByte);
  byte chksum = 0xA0 + m_relayIndex + stateByte;
  Serial.write(chksum);
  Serial.flush();

  while(Serial.available() > 0) {
    Serial.read();
  }

  m_state = state;
  sendState();
  
  return true;
}
