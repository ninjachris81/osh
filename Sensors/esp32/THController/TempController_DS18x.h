#ifndef TEMPCONTROLLER_DS18X_H
#define TEMPCONTROLLER_DS18X_H

#include <AbstractIntervalTask.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "TaskIDs.h"
//#include "MqttController.h"

#define TEMP_INTERVAL_MS 10000

class TempControllerDS18x : public AbstractIntervalTask {
public:
  TempControllerDS18x(String valueGroupTemp, uint8_t pin, uint8_t index);
  ~TempControllerDS18x();

  void init();

  void update();
  
private:
  bool m_requesting = true;
  uint8_t m_pin;
  uint8_t m_index;
  OneWire *m_oneWire;
  DallasTemperature *m_sensor;
  
  String m_valueGroupTemp;

};


#endif
