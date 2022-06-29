#ifndef TEMPCONTROLLER_AHTX_H
#define TEMPCONTROLLER_AHTX_H

#include <AbstractIntervalTask.h>
#include <Adafruit_AHTX0.h>

#include "TaskIDs.h"
//#include "MqttController.h"

#define TEMP_INTERVAL_MS 6000
#define TEMP_MIN -10
#define TEMP_MAX 50

class TempControllerAHTx : public AbstractIntervalTask {
public:
  TempControllerAHTx(String valueGroupTemp, String valueGroupHum);
  ~TempControllerAHTx();

  void init();

  void update();
  
private:
  Adafruit_AHTX0 aht;
  sensors_event_t humidity, temp;
  bool isInitialized = false;
  
  String m_valueGroupTemp;
  String m_valueGroupHum;

};


#endif
