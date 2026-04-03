#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <AbstractIntervalTask.h>

#include "TaskIDs.h"

#define LED_FREQUENCY_OK 0
#define LED_FREQUENCY_INIT 1000
#define LED_FREQUENCY_RECONNECT 500
#define LED_FREQUENCY_MOTION 100

class LEDController : public AbstractIntervalTask {
public:
  LEDController();

  void init();

  void update();

  void setFlashFrequency(uint16_t intervalMs);

private:
  uint16_t currentIntervalMs = 0;
  unsigned long lastToggle = 0;
  bool currentState = false;

};


#endif
