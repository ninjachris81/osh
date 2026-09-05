#ifndef TEMPCONTROLLER_DS18X_H
#define TEMPCONTROLLER_DS18X_H

#include <AbstractIntervalTask.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "TaskIDs.h"
//#include "MqttController.h"

#define INVALID_TEMP -127

class TempControllerDS18x : public AbstractIntervalTask {
public:
  TempControllerDS18x(String valueGroupTemp);
  ~TempControllerDS18x();

  void init();

  void update();
  
private:
  bool m_requesting = true;
  OneWire *m_oneWire;
  DallasTemperature *m_sensor;
  DeviceAddress m_tempDeviceAddress;
  
  String m_valueGroupTemp;

};


#endif
