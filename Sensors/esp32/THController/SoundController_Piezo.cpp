#include "SoundController_Piezo.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/actor.h"
#include "FlashController.h"

SoundControllerPiezo::SoundControllerPiezo(String valueGroup) : AbstractIntervalTask(SOUND_INTERVAL_MS), m_valueGroup(valueGroup) {
  m_state.init(0, ACTOR_OFF);
  m_state.registerValueChangeListener(this);
}

SoundControllerPiezo::~SoundControllerPiezo() {
}

void SoundControllerPiezo::init() {
  ledcSetup(TONE_PWM_CHANNEL, 0, 8);
  ledcAttachPin(PIN_SOUND_PIEZO, TONE_PWM_CHANNEL);
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->registerHandler(this);
}

void SoundControllerPiezo::update() {
  // BC value
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
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroup + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), (int)newValue);

  if (newValue==ACTOR_ON) {
    LOG_PRINTLN(F("Play tone"));
    ledcWriteTone(TONE_PWM_CHANNEL, 1000);
    //tone(PIN_SOUND_PIEZO, 55);
  } else {
    LOG_PRINTLN(F("Stop tone"));
    ledcWrite(TONE_PWM_CHANNEL, 0);
    //noTone(PIN_SOUND_PIEZO);
  }
}
