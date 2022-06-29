#ifndef MQTTCONTROLLER_H
#define MQTTCONTROLLER_H

#include <AbstractTask.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "shared/mqtt.h"
#include "ESPConfigurations.h"
#include <ArduinoJson.h>

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

  void setClientId(String clientId);
  
  void init();

  void update();

  void publishSingleValue(String path, bool value);
  void publishSingleValue(String path, int value);
  void publishSingleValue(String path, long value);
  void publishSingleValue(String path, double value);
  void publishSingleValue(String path, String value);
  JsonObject newObject();
  void publishObject(String path);
  void publishNull(String path);
  void publishWarn(String msg);  

  void registerHandler(MQTTEventCallbackHandler* handler);

  static void callback(char* topic, byte* payload, unsigned int length);
  void handleCallback(char* topic, byte* payload, unsigned int length);

private:
  WiFiClient espClient;
  PubSubClient client;
  static MQTTController* m_instance;
  String m_clientId;

  StaticJsonDocument<MQTT_JSON_MAX_LENGTH> m_doc;

  void reconnect();
  void subscribeTopics();
  void addToSubscribe(String path);

  MQTTEventCallbackHandler* m_callbackHandlers[MAX_MQTT_EVENT_CB_HANDLERS];
  uint8_t m_callbackHandlerCount = 0;

  String m_topics;


};


#endif
