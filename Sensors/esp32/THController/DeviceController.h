#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <AbstractIntervalTask.h>
//#include "MqttController.h"

class DeviceController : public AbstractIntervalTask {
public:
  DeviceController(String deviceIdPrefix, String serviceIdPrefix);
  ~DeviceController();
  
  void init();

  void update();

  String getDeviceId();

  String getServiceId();

private:
  String m_deviceIdPrefix;
  String m_serviceIdPrefix;

};


#endif
