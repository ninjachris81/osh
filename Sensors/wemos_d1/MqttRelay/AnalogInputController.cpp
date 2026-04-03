#include "AnalogInputController.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "Pins.h"
#include "TaskManager.h"
#include <LogHelper.h>

AnalogInputController::AnalogInputController(String valueGroupState, int valueIndex) : AbstractIntervalTask(6000), m_valueGroupState(valueGroupState), m_valueIndex(valueIndex)
{
}

void AnalogInputController::init() {
  pinMode(PIN_ANALOG_INPUT, INPUT);
}

void AnalogInputController::update() {
  m_currentValue = analogRead(PIN_ANALOG_INPUT);
  sendState();
}

void AnalogInputController::sendState() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupState + String(MQTT_PATH_SEP) + String(m_valueIndex)), m_currentValue);
}
