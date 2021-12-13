#ifndef MQTTCONTROLLER_H
#define MQTTCONTROLLER_H

#include <AbstractTask.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "shared/mqtt.h"
#include "ESPConfigurations.h"

#define BUILD_PATH(subpath) MQTT_BASE_PATH + String(MQTT_PATH_SEP) + subpath

#define MAX_MQTT_EVENT_CB_HANDLERS 8

#define TOPIC_DELIMITER '|'

class MQTTController : public AbstractTask {
public:
  MQTTController();
  ~MQTTController();

  class MQTTEventCallbackHandler {
    public:
      //virtual int getID() = 0;

      virtual void onConnected() {};

      virtual String getTopics() = 0;
      
      virtual void onMsgReceived(String topic, String value) {};
      virtual void onMsgReceived(String topic, bool value) {};
      virtual void onMsgReceived(String topic, int value) {};
      virtual void onMsgReceived(String topic, long value) {};
      virtual void onMsgReceived(String topic, double value) {};
      virtual void onMsgReceived(String topic) {};      //invalid
  };

  
  void init();

  void update();

  void publish(String path, bool value);
  void publish(String path, int value);
  void publish(String path, long value);
  void publish(String path, double value);
  void publish(String path, String value);
  void publish(String path);

  void registerHandler(MQTTEventCallbackHandler* handler);

  static void callback(char* topic, byte* payload, unsigned int length);
  void handleCallback(char* topic, byte* payload, unsigned int length);

private:
  WiFiClient espClient;
  PubSubClient client;
  static MQTTController* m_instance;

  void reconnect();
  void subscribeTopics();
  void addToSubscribe(String path);

  MQTTEventCallbackHandler* m_callbackHandlers[MAX_MQTT_EVENT_CB_HANDLERS];
  uint8_t m_callbackHandlerCount = 0;

  String m_topics;


};


#endif
