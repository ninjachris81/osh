#include "TOFController_CJVL53.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "FlashController.h"

TOFControllerCJVL53::TOFControllerCJVL53(String valueGroup) : AbstractIntervalTask(TOF_INTERVAL_MS), m_valueGroup(valueGroup) {
  
}

void TOFControllerCJVL53::init() {
  LOG_PRINTLN(F("TOF init"));
}

void TOFControllerCJVL53::update() {
  if (!isInitialized) {
    if (!m_lox.begin()) {
      LOG_PRINTLN(F("Could not find TOF"));
      taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishWarn(F("Cannot find TOF"));
    } else {
      m_lox.startRangeContinuous();
      isInitialized = true;
    }
  } else {
    if (m_lox.isRangeComplete()) {
      taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroup + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), m_lox.readRange());
    } else {
      LOG_PRINTLN(F("TOF not complete"));
    }
  }
}
