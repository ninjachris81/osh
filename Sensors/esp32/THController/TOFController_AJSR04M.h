#ifndef TOFCONTROLLER_AJSR04M_H
#define TOFCONTROLLER_AJSR04M_H

#include <AbstractIntervalTask.h>

#include "TaskIDs.h"
//#include "MqttController.h"

class TOFControllerAJSR04M : public AbstractIntervalTask {
public:
  TOFControllerAJSR04M(String valueGroup);

  void init();

  void update();
  
private:
  String m_valueGroup;

};


#endif
