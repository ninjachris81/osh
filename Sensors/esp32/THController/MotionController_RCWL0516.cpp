#include "MotionController_RCWL0516.h"

#include "Pins.h"

MotionControllerRCWL0516::MotionControllerRCWL0516() {
}

void MotionControllerRCWL0516::init() {
  pinMode(PIN_RCWL_SENSOR, INPUT);
}

void MotionControllerRCWL0516::update() {
  m_status = digitalRead(PIN_RCWL_SENSOR)==HIGH;
}

bool MotionControllerRCWL0516::getStatus() {
  return m_status;
}
