#ifndef MOTIONCONTROLLER_H
#define MOTIONCONTROLLER_H

#include <AbstractIntervalTask.h>
#include "Property.h"

#include "TaskIDs.h"
//#include "MqttController.h"

#include "MotionController_RCWL0516.h"
#include "MotionController_SR501.h"

#define MOTION_INTERVAL_MS 250

#define PROPERTY_MOTION_RADAR 0
#define PROPERTY_MOTION_PIR 1

class MotionController : public AbstractIntervalTask, public Property<bool>::ValueChangeListener {
public:
  MotionController(String valueGroupPir, String valueGroupRadar);

  void init();

  void update();
  
  void onPropertyValueChange(uint8_t id, bool newValue, bool oldValue);

private:
  MotionControllerRCWL0516 radarController;
  MotionControllerSR501 pirController;

  void sendValue();
  void sendValueRadar();
  void sendValuePir();

  Property<bool> m_statusRadar;
  Property<bool> m_statusPir;
  String m_valueGroupPir;
  String m_valueGroupRadar;
  unsigned long m_lastSend = 0;

};


#endif
