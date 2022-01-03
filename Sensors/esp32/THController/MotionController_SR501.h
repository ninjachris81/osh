#ifndef MOTIONCONTROLLER_SR501_H
#define MOTIONCONTROLLER_SR501_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


class MotionControllerSR501 {
public:
  MotionControllerSR501();

  void init();

  void update();

  bool getStatus();
  
private:
  bool m_status = false;
  uint8_t m_countsSec = 0;
  uint8_t m_highCountsSec = 0;

};


#endif
