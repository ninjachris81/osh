#ifndef MOTIONCONTROLLER_RCWL0516_H
#define MOTIONCONTROLLER_RCWL0516_H

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class MotionControllerRCWL0516 {
public:
  MotionControllerRCWL0516();

  void init();

  void update();

  bool getStatus();

private:
  bool m_status = false;

  
};


#endif
