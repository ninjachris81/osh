#include "TempController_DS18x.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "FlashController.h"
#include "Pins.h"

TempControllerDS18x::TempControllerDS18x(String valueGroupTemp) : AbstractIntervalTask(TEMP_INTERVAL_MS), m_valueGroupTemp(valueGroupTemp) {
  
}

TempControllerDS18x::~TempControllerDS18x() {
}

void TempControllerDS18x::init() {
  m_oneWire = new OneWire(PIN_TEMP_SENSOR_ONEWIRE);
  m_sensor = new DallasTemperature(m_oneWire);
}

void TempControllerDS18x::update() {
  if (m_requesting) {
    m_sensor->requestTemperatures(); 
  } else {
    float temp = m_sensor->getTempCByIndex(0);
    taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupTemp + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex() + 1)), temp);
  }
  m_requesting = !m_requesting;
}
