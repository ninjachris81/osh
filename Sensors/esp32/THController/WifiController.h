#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H

#include <AbstractIdleTask.h>
#include <WiFi.h>

class WifiController : public AbstractIdleTask {
public:
  WifiController();
  ~WifiController();

  void init();

  void update();

  Client* getClient();

private:
  WiFiClient myClient;
};


#endif
