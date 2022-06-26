#include "FlowController_Reed.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include "Pins.h"
#include "MQTTController.h"
#include "FlashController.h"

volatile uint32_t lastValue1 = 0;
volatile uint32_t lastValue2 = 0;
volatile uint32_t lastValue3 = 0;
volatile uint32_t lastValue4 = 0;

volatile uint16_t counterValue1 = 0;
volatile uint16_t counterValue2 = 0;
volatile uint16_t counterValue3 = 0;
volatile uint16_t counterValue4 = 0;

void ICACHE_RAM_ATTR valueISR1() {
  counterValue1++;
}

void ICACHE_RAM_ATTR valueISR2() {
  counterValue2++;
}

void ICACHE_RAM_ATTR valueISR3() {
  counterValue3++;
}

void ICACHE_RAM_ATTR valueISR4() {
  counterValue4++;
}

FlowControllerReed::FlowControllerReed(String valueGroupStatus) : AbstractIntervalTask(FLOW_UPDATE_INTERVAL_MS), m_valueGroupStatus(valueGroupStatus) {
}

void FlowControllerReed::init() {
  pinMode(PIN_FLOW_REED_SENSOR_1, INPUT);
  pinMode(PIN_FLOW_REED_SENSOR_2, INPUT);
  pinMode(PIN_FLOW_REED_SENSOR_3, INPUT);
  pinMode(PIN_FLOW_REED_SENSOR_4, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(PIN_FLOW_REED_SENSOR_1), valueISR1, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_FLOW_REED_SENSOR_2), valueISR2, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_FLOW_REED_SENSOR_3), valueISR3, FALLING);
  attachInterrupt(digitalPinToInterrupt(PIN_FLOW_REED_SENSOR_4), valueISR4, FALLING);
}

void FlowControllerReed::update() {
  cli();
  uint16_t localCounterValue1 = counterValue1;
  uint16_t localCounterValue2 = counterValue2;
  uint16_t localCounterValue3 = counterValue3;
  uint16_t localCounterValue4 = counterValue4;
  counterValue1 = 0;
  counterValue2 = 0;
  counterValue3 = 0;
  counterValue4 = 0;
  sei();


  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupStatus + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), localCounterValue1);
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupStatus + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex()+1)), localCounterValue2);
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupStatus + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex()+2)), localCounterValue3);
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_VA + String(MQTT_PATH_SEP) + m_valueGroupStatus + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex()+3)), localCounterValue4);
}
