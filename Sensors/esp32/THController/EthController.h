#include "ESPConfigurations.h"

#if USES_ETH
#ifndef ETHCONTROLLER_H
#define ETHCONTROLLER_H

#include <AbstractIdleTask.h>
#include <Ethernet.h>
#include <ETH.h>

class EthController : public AbstractIdleTask {
public:
  EthController();
  ~EthController();

  void init();

  void update();

  Client* getClient();

private:
  NetworkClient myClient;

};


#endif
#endif
