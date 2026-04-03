#ifndef OTACONTROLLER_H
#define OTACONTROLLER_H

#include <AbstractIntervalTask.h>
#include <ArduinoOTA.h>

#define OTA_INTERVAL_MS 1000

class OTAController : public AbstractIntervalTask {
public:
  OTAController();
  ~OTAController();

  void init();

  void update();

};


#endif
