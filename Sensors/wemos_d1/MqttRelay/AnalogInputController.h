#ifndef ANALOG_INPUT_CONTROLLER_H
#define ANALOG_INPUT_CONTROLLER_H

#include <AbstractIntervalTask.h>

#include "TaskIDs.h"

#define LED_FREQUENCY_OK 0
#define LED_FREQUENCY_INIT 1000
#define LED_FREQUENCY_RECONNECT 500
#define LED_FREQUENCY_MOTION 100

class AnalogInputController : public AbstractIntervalTask {
public:
  AnalogInputController(String valueGroupState, int valueIndex);

  void init();

  void update();

private:
  String m_valueGroupState;
  int m_valueIndex = 0;
  
  int m_currentValue = -1;
  void sendState();

};


#endif
