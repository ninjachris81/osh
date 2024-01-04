#ifndef TOFCONTROLLER_CJVL53_H
#define TOFCONTROLLER_CJVL53_H

#include <AbstractIntervalTask.h>
#include "Adafruit_VL53L0X.h"

#include "TaskIDs.h"
//#include "MqttController.h"

#define TOF_INTERVAL_MS 2000

class TOFControllerCJVL53 : public AbstractIntervalTask {
public:
  TOFControllerCJVL53(String valueGroup);

  void init();

  void update();
  
private:
  Adafruit_VL53L0X m_lox;
  bool isInitialized = false;
  
  String m_valueGroup;

};


#endif
