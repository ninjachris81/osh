#include "MQTTController.h"
#include "config.h"
#include "credentials.h"
#include "ESPConfigurations.h"
#include "shared/device.h"
#include <LogHelper.h>

MQTTController::MQTTController() : AbstractIdleTask() {
  client.setClient(espClient);  
}

MQTTController::~MQTTController() {
}

void MQTTController::init() {

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     LOG_PRINTLN(F("Connecting to WiFi.."));
  }
  LOG_PRINTLN(F("Connected to the WiFi network"));
  
  //connecting to a mqtt broker
  client.setServer(MQTT_SERVER, MQTT_PORT);
  while (!client.connected()) {
     String client_id = String(DEVICE_ID) + String(DEVICE_FULLID_SEP) + String(SERVICE_ID);
     if (client.connect(client_id.c_str())) {
         LOG_PRINTLN(F("Mqtt broker connected"));
     } else {
         LOG_PRINT(F("failed with state "));
         LOG_PRINTLN(client.state());
         delay(2000);
     }
  }
}

void MQTTController::update() {
}

void MQTTController::publish(String path, double value) {
  String valueStr= String(MQTT_ID_DOUBLE) + String(value, 2);
  client.publish(path.c_str(), valueStr.c_str());
}

void MQTTController::publish(String path, bool value) {
  String valueStr= String(MQTT_ID_BOOL) + (value ? String("1") : String("0"));
  client.publish(path.c_str(), valueStr.c_str());
}

void MQTTController::publish(String path, String value) {
  value=String(MQTT_ID_STRING) + value;
  client.publish(path.c_str(), value.c_str());
}

void MQTTController::publish(String path) {
  client.publish(path.c_str(), "");
}
