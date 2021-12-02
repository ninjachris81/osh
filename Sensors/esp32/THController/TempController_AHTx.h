#ifndef TEMPCONTROLLER_AHTX_H
#define TEMPCONTROLLER_AHTX_H

#include <AbstractIntervalTask.h>
#include <Adafruit_AHTX0.h>

#include "TaskIDs.h"
//#include "MqttController.h"

#define TEMP_INTERVAL_MS 6000

class TempControllerAHTx : public AbstractIntervalTask {
public:
  TempControllerAHTx(String valueGroupTemp, String valueIdTemp, String valueGroupHum, String valueIdHum);
  ~TempControllerAHTx();

  void init();

  void update();
  
private:
  Adafruit_AHTX0 aht;
  sensors_event_t humidity, temp;
  
  String m_valueGroupTemp;
  String m_valueIdTemp;
  
  String m_valueGroupHum;
  String m_valueIdHum;

};


#endif
