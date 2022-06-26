#ifndef WIFICONTROLLER_H
#define WIFICONTROLLER_H

#include <AbstractIdleTask.h>

class WifiController : public AbstractIdleTask {
public:
  WifiController();
  ~WifiController();

  void init();

  void update();

};


#endif
