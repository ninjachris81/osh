#include "BrightnessController_GL55x.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "shared/value.h"
#include "FlashController.h"

BrightnessControllerGL55x::BrightnessControllerGL55x(String valueGroup) : AbstractIntervalTask(BRIGHTNESS_INTERVAL_MS), m_valueGroup(valueGroup) {
  
}

BrightnessControllerGL55x::~BrightnessControllerGL55x() {
}

void BrightnessControllerGL55x::init() {
  pinMode(PIN_BRIGHTNESS_SENSOR, INPUT);
}

void BrightnessControllerGL55x::update() {
  int v = analogRead(PIN_BRIGHTNESS_SENSOR);

  LOG_PRINTLN(v);
  
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroup + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), ((double) v / 4096 * 100));
}
