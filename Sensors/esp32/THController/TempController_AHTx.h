#ifndef TEMPCONTROLLER_AHTX_H
#define TEMPCONTROLLER_AHTX_H

#include <AbstractIntervalTask.h>
#include <Adafruit_AHTX0.h>

#include "TaskIDs.h"
//#include "MqttController.h"

#define TEMP_INTERVAL_MS 2000

class TempControllerAHTx : public AbstractIntervalTask {
public:
  TempControllerAHTx();
  ~TempControllerAHTx();

  void init();

  void update();
  
private:
  Adafruit_AHTX0 aht;
  sensors_event_t humidity, temp;

};


#endif
