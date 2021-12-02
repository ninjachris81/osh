#ifndef MQTTCONTROLLER_H
#define MQTTCONTROLLER_H

#include <AbstractIdleTask.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "shared/mqtt.h"
#include "ESPConfigurations.h"

#define BUILD_PATH(subpath) MQTT_BASE_PATH + String(MQTT_PATH_SEP) + subpath

class MQTTController : public AbstractIdleTask {
public:
  MQTTController();
  ~MQTTController();
  
  void init();

  void update();

  void publish(String path, double value);
  void publish(String path, String value);

private:
  WiFiClient espClient;
  PubSubClient client;


};


#endif
