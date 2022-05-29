#include "MQTTController.h"
#include "config.h"
#include "credentials.h"
#include "ESPConfigurations.h"
#include "shared/mqtt.h"
#include <LogHelper.h>
#include "LEDController.h"
#include "TaskIDs.h"
#include "TaskManager.h"

MQTTController* MQTTController::m_instance = NULL;

MQTTController::MQTTController() : AbstractTask(), m_clientId("") {
  client.setClient(espClient);
  m_instance = this;
}

MQTTController::~MQTTController() {
}

void MQTTController::setClientId(String clientId) {
  m_clientId = clientId;
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
  client.setCallback(&MQTTController::callback);
}

void MQTTController::update() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void MQTTController::reconnect() {
  if (m_clientId.length() > 0) {
    if (!client.connected()) {
       if (client.connect(m_clientId.c_str())) {
           LOG_PRINTLN(F("MQTT broker"));
           for (uint8_t i=0;i<m_callbackHandlerCount;i++) m_callbackHandlers[i]->onConnected();
           subscribeTopics();
           taskManager->getTask<LEDController*>(LED_CONTROLLER)->setFlashFrequency(LED_FREQUENCY_OK);
       } else {
           taskManager->getTask<LEDController*>(LED_CONTROLLER)->setFlashFrequency(LED_FREQUENCY_RECONNECT);
           LOG_PRINT(F("failed with state "));
           LOG_PRINTLN(client.state());
           delay(2000);
       }
    }
  } else {
    LOG_PRINTLN(F("Error: clientId not set!"));
  }
}

void MQTTController::addToSubscribe(String path) {
  if (path.length() > 0) {
    String tmp = path + (path.charAt(path.length()-1) == TOPIC_DELIMITER ? "" : String(TOPIC_DELIMITER));
    if (m_topics.indexOf(tmp)==-1) {
      m_topics += tmp;
    }
  }
}

void MQTTController::subscribeTopics() {
  uint16_t p = 0;
  uint16_t x = 0;

  for (uint8_t i=0;i<m_callbackHandlerCount;i++) {
    addToSubscribe(m_callbackHandlers[i]->getTopics());
  }
  
  LOG_PRINTLN(m_topics);

  do {
    x = m_topics.indexOf(TOPIC_DELIMITER, p);
    if (x != -1) {

      String t = m_topics.substring(p, x);

      LOG_PRINT(F("Subscribing to topic "));
      LOG_PRINTLN(t);

      client.subscribe(t.c_str());
      
      p = x+1;
    }
  } while (x != -1 && p < m_topics.length());

  
}

void MQTTController::registerHandler(MQTTEventCallbackHandler* handler) {
  m_callbackHandlers[m_callbackHandlerCount] = handler;
  m_callbackHandlerCount++;
}

void MQTTController::publish(String path, double value) {
  String valueStr= String(MQTT_ID_DOUBLE) + String(value, 2);
  client.publish(path.c_str(), valueStr.c_str());
}

void MQTTController::publish(String path, int value) {
  String valueStr= String(MQTT_ID_INTEGER) + value;
  client.publish(path.c_str(), valueStr.c_str());
}

void MQTTController::publish(String path, long value) {
  String valueStr= String(MQTT_ID_LONG) + value;
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

void MQTTController::callback(char* topic, byte* payload, unsigned int length) {
  m_instance->handleCallback(topic, payload, length);
}

void MQTTController::handleCallback(char* topic, byte* payload, unsigned int length) {
  String myTopic(topic);
  char myBuffer[length];
  for (uint8_t i=0;i<length;i++) {
    myBuffer[i] = (char)payload[i];
  }
  String myValue = String(myBuffer);

  LOG_PRINT(F("Message received "));
  LOG_PRINTLN(myTopic);

  if (myValue.length()>=MQTT_MIN_MSG_SIZE) {
    for (uint8_t i=0;i<m_callbackHandlerCount;i++) {
      if (m_callbackHandlers[i]->getTopics().indexOf(myTopic) != -1) {
        
        switch(myValue.charAt(0)) {
          case MQTT_ID_BOOL:
            m_callbackHandlers[i]->onMsgReceived(myTopic, (myValue.charAt(1)=='1'));
            break;
          case MQTT_ID_INTEGER:
            m_callbackHandlers[i]->onMsgReceived(myTopic, (int)myValue.substring(1).toInt());
            break;
          case MQTT_ID_LONG:
            m_callbackHandlers[i]->onMsgReceived(myTopic, myValue.substring(1).toInt());
            break;
          case MQTT_ID_DOUBLE:
            m_callbackHandlers[i]->onMsgReceived(myTopic, (double)myValue.substring(1).toFloat());
            break;
          case MQTT_ID_STRING:
            m_callbackHandlers[i]->onMsgReceived(myTopic, myValue.substring(1));
            break;
          case MQTT_ID_INVALID:
            m_callbackHandlers[i]->onMsgReceived(myTopic);
            break;
        }
      }
    }
  }
}
