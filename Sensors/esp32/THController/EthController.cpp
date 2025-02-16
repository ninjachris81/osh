#include "EthController.h"
#include "ESPConfigurations.h"
#include <LogHelper.h>
#include "DeviceController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include "shared/device.h"

#if USES_ETH

EthController::EthController() : AbstractIdleTask() {
  
}

EthController::~EthController() {
}

void EthController::init() {
  //DeviceController* deviceController = taskManager->getTask<DeviceController*>(DEVICE_CONTROLLER);
  //String hostname = String(deviceController->getDeviceId()) + String(DEVICE_FULLID_SEP) + String(deviceController->getServiceId());
  
  LOG_PRINT(F("Connecting to ETH"));
  //LOG_PRINTLN(hostname);

  //WiFi.setHostname(hostname.c_str());
  while (!ETH.begin()) {
     delay(5000);
  }
  LOG_PRINT(F("Connected to ETH, IP "));
  LOG_PRINTLN(ETH.localIP());
}

void EthController::update() {
}


Client* EthController::getClient() {
  return &myClient;
}

#endif
