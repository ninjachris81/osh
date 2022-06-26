#include "WifiController.h"
#include "ESPConfigurations.h"
#include <LogHelper.h>
#include "DeviceController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <WiFi.h>
#include "shared/device.h"
#include "credentials.h"

WifiController::WifiController() : AbstractIdleTask() {
  
}

WifiController::~WifiController() {
}

void WifiController::init() {
  DeviceController* deviceController = taskManager->getTask<DeviceController*>(DEVICE_CONTROLLER);
  String hostname = String(deviceController->getDeviceId()) + String(DEVICE_FULLID_SEP) + String(deviceController->getServiceId());
  
  LOG_PRINT(F("Connecting to WiFi as host "));
  LOG_PRINTLN(hostname);

  WiFi.setHostname(hostname.c_str());
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     LOG_PRINTLN(F("Connecting to WiFi.."));
  }
  LOG_PRINT(F("Connected to WiFi, IP "));
  LOG_PRINTLN(WiFi.localIP());

}

void WifiController::update() {
}
