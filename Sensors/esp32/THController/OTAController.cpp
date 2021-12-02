#include "OTAController.h"
#include <LogHelper.h>

OTAController::OTAController() : AbstractIntervalTask(OTA_INTERVAL_MS) {
  
}

OTAController::~OTAController() {
}

void OTAController::init() {

    ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      LOG_PRINT(F("Start updating "));
      LOG_PRINTLN(type);
    })
    .onEnd([]() {
      LOG_PRINTLN(F("Update finished"));
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      //Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      if (error == OTA_AUTH_ERROR) LOG_PRINTLN(F("Auth Failed"));
      else if (error == OTA_BEGIN_ERROR) LOG_PRINTLN(F("Begin Failed"));
      else if (error == OTA_CONNECT_ERROR) LOG_PRINTLN(F("Connect Failed"));
      else if (error == OTA_RECEIVE_ERROR) LOG_PRINTLN(F("Receive Failed"));
      else if (error == OTA_END_ERROR) LOG_PRINTLN(F("End Failed"));
    });

  ArduinoOTA.begin();

}

void OTAController::update() {
  ArduinoOTA.handle();
}
