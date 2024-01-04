#include "TOFController_AJSR04M.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "FlashController.h"
#include "Pins.h"

TOFControllerAJSR04M::TOFControllerAJSR04M(String valueGroup) : AbstractIntervalTask(TOF_INTERVAL_MS), m_valueGroup(valueGroup) {
  
}

void TOFControllerAJSR04M::init() {
  LOG_PRINTLN(F("TOF init"));

  pinMode(PIN_TOF_TRIGGER, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(PIN_TOF_ECHO, INPUT); // Sets the echoPin as an INPUT
}

void TOFControllerAJSR04M::update() {
  // Clears the trigPin condition
  digitalWrite(PIN_TOF_TRIGGER, LOW);  //
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(PIN_TOF_TRIGGER, HIGH);
  delayMicroseconds(10);
  
  long duration = pulseIn(PIN_TOF_ECHO, HIGH);
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroup + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), distance);
}
