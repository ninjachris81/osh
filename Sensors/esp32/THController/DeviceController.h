#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <AbstractIntervalTask.h>
//#include "MqttController.h"

class DeviceController : public AbstractIntervalTask {
public:
  DeviceController(String id, String serviceId);
  ~DeviceController();
  
  void init();

  void update();

private:
  String m_id;
  String m_serviceId;

};


#endif
