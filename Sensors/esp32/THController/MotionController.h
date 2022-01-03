#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H

#include <AbstractIntervalTask.h>
#include "Property.h"

#include "TaskIDs.h"
//#include "MqttController.h"

#include "MotionController_RCWL0516.h"
#include "MotionController_SR501.h"

#define MOTION_INTERVAL_MS 250

class MotionController : public AbstractIntervalTask, public Property<bool>::ValueChangeListener {
public:
  MotionController(String valueGroupStatus);

  void init();

  void update();
  
  void onPropertyValueChange(uint8_t id, bool newValue, bool oldValue);

private:
  MotionControllerRCWL0516 radarController;
  MotionControllerSR501 pirController;
  void sendValue();

  Property<bool> m_status;
  String m_valueGroupStatus;
  unsigned long m_lastSend = 0;

};


#endif
