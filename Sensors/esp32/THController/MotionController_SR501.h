#ifndef MOTIONCONTROLLER_SR501_H
#define MOTIONCONTROLLER_SR501_H

#include <AbstractIntervalTask.h>
#include "BehaviorProperty.h"

#include "TaskIDs.h"
//#include "MqttController.h"

#define MOTION_INTERVAL_MS 100

class MotionControllerSR501 : public AbstractIntervalTask, public Property<bool>::ValueChangeListener {
public:
  MotionControllerSR501(String valueGroupStatus);
  ~MotionControllerSR501();

  void init();

  void update();
  
  void onPropertyValueChange(uint8_t id, bool newValue, bool oldValue);

private:
  void sendValue();

  Property<bool> m_status;
  String m_valueGroupStatus;
  unsigned long m_lastSend = 0;

  uint8_t m_countsSec = 0;
  uint8_t m_highCountsSec = 0;

};


#endif
