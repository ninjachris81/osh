#include "SoundController_Piezo.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/actor.h"
#include "shared/value.h"
#include "FlashController.h"

SoundControllerPiezo::SoundControllerPiezo(String valueGroup) : AbstractIntervalTask(SOUND_INTERVAL_MS), m_valueGroup(valueGroup) {
  m_state.init(0, ACTOR_OFF);
  m_state.registerValueChangeListener(this);
}

SoundControllerPiezo::~SoundControllerPiezo() {
}

void SoundControllerPiezo::init() {
  ledcSetup(TONE_PWM_CHANNEL, TONE_FREQ, 8);
  ledcAttachPin(PIN_SOUND_PIEZO, TONE_PWM_CHANNEL);
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->registerHandler(this);
}

void SoundControllerPiezo::update() {
  // check send bc
  if (millis() - m_lastSend > (VALUE_TIMEOUT_MID / 2)) {
    sendValue();
  }

  updateBeep();
}

void SoundControllerPiezo::onMsgReceived(String topic, int value) {
  LOG_PRINT(F("SOUND ACTOR MSG "));
  LOG_PRINTLN(value);
  
  m_state.setValue(value);
}


String SoundControllerPiezo::getTopics() {
  return BUILD_PATH(MQTT_MESSAGE_TYPE_AC + String(MQTT_PATH_SEP) + m_valueGroup + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())) + String(TOPIC_DELIMITER);
}

void SoundControllerPiezo::onPropertyValueChange(uint8_t id, int newValue, int oldValue) {
  if (newValue==ACTOR_ON) {
    LOG_PRINTLN(F("Play tone"));
    setupBeep(800);
  } else {
    LOG_PRINTLN(F("Stop tone"));
    stopBeep();
  }
  
  sendValue();
}

void SoundControllerPiezo::sendValue() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroup + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_state.getValue());
  m_lastSend = millis();
}

void SoundControllerPiezo::setupBeep(uint8_t intervalMs) {
  m_intervalMs = intervalMs;
  m_beepState = millis() + intervalMs;
  m_beepOn = false;
  updateBeep();
}

void SoundControllerPiezo::updateBeep() {
  if (m_state.getValue() == ACTOR_ON) {
    if (millis() > m_beepState + m_intervalMs) {    // check toggle
      if (!m_beepOn) {
        ledcWriteTone(TONE_PWM_CHANNEL, TONE_FREQ);
        //tone(PIN_SOUND_PIEZO, 55);
      } else {
        ledcWrite(TONE_PWM_CHANNEL, 0);
        //noTone(PIN_SOUND_PIEZO);
      }
      m_beepOn = !m_beepOn;
      m_beepState = millis();
    }
  }
}

void SoundControllerPiezo::stopBeep() {
  m_intervalMs = 0;
  m_beepState = 0;
  m_beepOn = false;
  ledcWrite(TONE_PWM_CHANNEL, 0);
  //noTone(PIN_SOUND_PIEZO);
}
