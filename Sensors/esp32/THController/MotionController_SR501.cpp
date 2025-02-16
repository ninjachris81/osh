#include "MotionController_SR501.h"

#include "Pins.h"

MotionControllerSR501::MotionControllerSR501() {
}

void MotionControllerSR501::init() {
  pinMode(PIN_PIR_SENSOR, INPUT);
}

void MotionControllerSR501::update() {
  m_countsSec++;
  if (digitalRead(PIN_PIR_SENSOR) == HIGH) {
    m_highCountsSec++;
  }

  if (m_countsSec >= 10) {
    //LOG_PRINTLN(m_highCountsSec);
    //LOG_PRINTLN(m_status.getValue());

    m_status = m_highCountsSec > 5;
    m_countsSec = 0;
    m_highCountsSec = 0;
  }

}

bool MotionControllerSR501::getStatus() {
  return m_status;
}
