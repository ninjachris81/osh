#include "RelayController_Shutter.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/actor.h"
#include "shared/value.h"
#include "FlashController.h"
#include "LEDController.h"

RelayControllerShutter::RelayControllerShutter(String valueGroupState, String valueGroupCloseState, String valueGroupTiltState) : AbstractIntervalTask(500), m_valueGroupState(valueGroupState), m_valueGroupCloseState(valueGroupCloseState), m_valueGroupTiltState(valueGroupTiltState) {
  m_state.init(PROPERTY_STATE, ACTOR_OFF);
  m_state.registerValueChangeListener(this);

  m_closeState.init(PROPERTY_CLOSE_STATE, 0);
  m_closeState.registerValueChangeListener(this);

  m_tiltState.init(PROPERTY_TILT_STATE, 0);
  m_tiltState.registerValueChangeListener(this);
}

RelayControllerShutter::~RelayControllerShutter() {
}

void RelayControllerShutter::init() {
  pinMode(PIN_RELAY_UP, OUTPUT);
  pinMode(PIN_RELAY_DOWN, OUTPUT);
  digitalWrite(PIN_RELAY_UP, HIGH);
  digitalWrite(PIN_RELAY_DOWN, HIGH);
  
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->registerHandler(this);
  
  m_lastAction = millis();
  m_initializing = true;
}

void RelayControllerShutter::update() {
  // check send bc
  if (millis() - m_lastSend > (VALUE_TIMEOUT_MID / 2)) {
    sendState();
    sendCloseState();
    sendTiltState();
  }

  if (m_initializing) {
    if (millis() - m_lastAction > m_shutterDurationFull) {
      LOG_PRINTLN(F("Shutter init complete"));
      m_initializing = false;
      m_state.setValue(ACTOR_OFF);
    }
  } else {
    // check duration
    switch(m_state.getValue()) {
      case ACTOR_DOWN:
      case ACTOR_UP:
        if (m_lastAction > 0 && millis() - m_lastAction > (m_shutterDurationFull + SHUTTER_DURATION_FULL_OPEN_CLOSE_SURPLUS)) {
          LOG_PRINTLN(F("Shutter close/open timeout"));
          m_state.setValue(ACTOR_OFF);
        }
        break;
      case ACTOR_SHUTTER_HALF_CLOSE:
        if (m_lastAction > 0 && millis() - m_lastAction > (m_shutterDurationFull / 2)) {
          LOG_PRINTLN(F("Shutter half timeout"));
          m_state.setValue(ACTOR_OFF);
        }
        break;
      case ACTOR_SHUTTER_HALF_OPEN:
        if (m_lastAction > 0 && millis() - m_lastAction > (m_shutterDurationFull / 2)) {
          LOG_PRINTLN(F("Shutter half turn open"));
          m_state.setValue(ACTOR_SHUTTER_TURN_OPEN);
        }
        break;
      case ACTOR_SHUTTER_FULL_OPEN:
        if (m_lastAction > 0 && millis() - m_lastAction > m_shutterDurationFull) {
          LOG_PRINTLN(F("Shutter close, now turn open"));
          m_state.setValue(ACTOR_SHUTTER_TURN_OPEN);
        }
        break;
      case ACTOR_SHUTTER_TURN_OPEN:
      case ACTOR_SHUTTER_TURN_CLOSE:
        if (m_lastAction > 0 && millis() - m_lastAction > m_shutterDurationTurn) {
          LOG_PRINTLN(F("Shutter turn timeout"));
          m_state.setValue(ACTOR_OFF);
        }
        break;
    }
  }

/*
  if (m_relayUp) {
    //m_closeState = max(m_closeState - 1, SHUTTER_CLOSE_STATE_MIN);
  }
  if (m_relayDown) {
    //m_closeState = min(m_closeState + 1, SHUTTER_CLOSE_STATE_MAX);
  }
  */
}

void RelayControllerShutter::onMsgReceived(String topic, int value) {
  LOG_PRINT(F("SHUTTER ACTOR MSG "));
  LOG_PRINTLN(value);
  
  m_state.setValue(value);
}


String RelayControllerShutter::getTopics() {
  return BUILD_PATH(MQTT_MESSAGE_TYPE_AC + String(MQTT_PATH_SEP) + m_valueGroupState + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())) + String(TOPIC_DELIMITER);
}

void RelayControllerShutter::onPropertyValueChange(uint8_t id, int newValue, int oldValue) {
  switch(id) {
    case PROPERTY_STATE:
      onPropertyValueChangeState(newValue, oldValue);
      break;
    case PROPERTY_CLOSE_STATE:
      onPropertyValueChangeCloseState(newValue, oldValue);
      break;
    case PROPERTY_TILT_STATE:
      onPropertyValueChangeTiltState(newValue, oldValue);
      break;
  }
}

void RelayControllerShutter::onPropertyValueChangeState(int newValue, int oldValue) {
  sendState();

  uint16_t ledFreq = 2000;

  if (newValue == ACTOR_UP) {
    LOG_PRINTLN(F("Shutter up"));
    switchRelay(true, false);
    m_lastAction = millis();
  } else if (newValue == ACTOR_DOWN || newValue == ACTOR_SHUTTER_FULL_OPEN) {
    LOG_PRINTLN(F("Shutter down"));
    switchRelay(false, true);
    m_lastAction = millis();
  } else if (newValue == ACTOR_SHUTTER_HALF_CLOSE) {
    // TODO
  } else if (newValue == ACTOR_SHUTTER_HALF_OPEN) {
    // TODO
  } else if (newValue == ACTOR_SHUTTER_TURN_OPEN) {
    LOG_PRINTLN(F("Shutter open"));
    switchRelay(true, false);
    m_lastAction = millis();
  } else if (newValue == ACTOR_SHUTTER_TURN_CLOSE) {
    LOG_PRINTLN(F("Shutter close"));
    switchRelay(false, true);
    m_lastAction = millis();
  } else {
    LOG_PRINTLN(F("Shutter stop"));
    switchRelay(false, false);
    m_lastAction = 0;
    ledFreq = LED_FREQUENCY_OK;
  }

  taskManager->getTask<LEDController*>(LED_CONTROLLER)->setFlashFrequency(ledFreq);
}

void RelayControllerShutter::onPropertyValueChangeCloseState(int newValue, int oldValue) {
  sendCloseState();
}

void RelayControllerShutter::onPropertyValueChangeTiltState(int newValue, int oldValue) {
  sendTiltState();
  
}

void RelayControllerShutter::sendState() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupState + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_state.getValue());
  m_lastSend = millis();
}

void RelayControllerShutter::sendCloseState() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupCloseState + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_closeState.getValue());
}

void RelayControllerShutter::sendTiltState() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupTiltState + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_tiltState.getValue());
}

void RelayControllerShutter::switchRelay(bool relayUp, bool relayDown) {
  if (relayUp && relayDown) return;   // invalid state
  
  // first switch OFF  
  if (!relayUp) {
    digitalWrite(PIN_RELAY_UP, HIGH);
  }
  if (!relayDown) {
    digitalWrite(PIN_RELAY_DOWN, HIGH);
  }
  
  // then, switch ON
  if (relayUp || relayDown) {
    delay(300);
    if (relayUp) {
      digitalWrite(PIN_RELAY_UP, LOW);
      LOG_PRINTLN(F("Relay up ON"));
    }
    if (relayDown) {
      digitalWrite(PIN_RELAY_DOWN, LOW);
      LOG_PRINTLN(F("Relay down ON"));
    }
  }

  if (relayUp) {
    m_direction = SHUTTER_DIRECTION_UP;
  } else if (relayDown) {
    m_direction = SHUTTER_DIRECTION_DOWN;
  } else {
    m_direction = SHUTTER_DIRECTION_NONE;
  }
}
