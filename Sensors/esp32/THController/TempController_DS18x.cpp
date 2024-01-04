#include "TempController_DS18x.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "FlashController.h"

TempControllerDS18x::TempControllerDS18x(String valueGroupTemp, uint8_t pin, uint8_t index) : AbstractIntervalTask(TEMP_INTERVAL_MS), m_valueGroupTemp(valueGroupTemp), m_pin(pin), m_index(index) {
  
}

TempControllerDS18x::~TempControllerDS18x() {
}

void TempControllerDS18x::init() {
  m_oneWire = new OneWire(m_pin);
  m_sensor = new DallasTemperature(m_oneWire);
}

void TempControllerDS18x::update() {
  if (m_requesting) {
    m_sensor->requestTemperatures(); 
  } else {
    float temp = m_sensor->getTempCByIndex(0);
    taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupTemp + String(MQTT_PATH_SEP) + String(m_index)), temp);
  }
  m_requesting = !m_requesting;
}
