#ifndef BRIGHTNESSCONTROLLER_GL55x_H
#define BRIGHTNESSCONTROLLER_GL55x_H

#include <AbstractIntervalTask.h>

#include "TaskIDs.h"
//#include "MqttController.h"

#define BRIGHTNESS_INTERVAL_MS 6000

class BrightnessControllerGL55x : public AbstractIntervalTask {
public:
  BrightnessControllerGL55x(String valueGroup);
  ~BrightnessControllerGL55x();

  void init();

  void update();
  
private:
  String m_valueGroup;
};


#endif
