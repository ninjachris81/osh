#include "MQTTController.h"
#include "config.h"
#include "ESPConfigurations.h"
#include "shared/mqtt.h"
#include <LogHelper.h>
#include "LEDController.h"
#include "DeviceController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include "shared/device.h"
#include "FlashController.h"

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
  //connecting to a mqtt broker
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(&MQTTController::callback);

  DeviceController *deviceController = taskManager->getTask<DeviceController*>(DEVICE_CONTROLLER);
  m_clientId = String(deviceController->getDeviceId()) + String(DEVICE_FULLID_SEP) + String(deviceController->getServiceId());
  LOG_PRINT(F("Using MQTT ClientId "));
  LOG_PRINTLN(m_clientId);
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

void MQTTController::publishSingleValue(String path, double value) {
  m_doc.clear();
  m_doc[MQTT_SINGLE_VALUE_ATTR] = value;
  m_doc[MQTT_SENDER_DEVICE_ID_ATTR] = m_clientId;
  String output;
  serializeJson(m_doc, output);
  client.publish(path.c_str(), output.c_str());
}

void MQTTController::publishSingleValue(String path, int value) {
  m_doc.clear();
  m_doc[MQTT_SINGLE_VALUE_ATTR] = value;
  m_doc[MQTT_SENDER_DEVICE_ID_ATTR] = m_clientId;
  String output;
  serializeJson(m_doc, output);
  client.publish(path.c_str(), output.c_str());
}

void MQTTController::publishSingleValue(String path, long value) {
  m_doc.clear();
  m_doc[MQTT_SINGLE_VALUE_ATTR] = value;
  m_doc[MQTT_SENDER_DEVICE_ID_ATTR] = m_clientId;
  String output;
  serializeJson(m_doc, output);
  client.publish(path.c_str(), output.c_str());
}

void MQTTController::publishSingleValue(String path, bool value) {
  m_doc.clear();
  m_doc[MQTT_SINGLE_VALUE_ATTR] = value;
  m_doc[MQTT_SENDER_DEVICE_ID_ATTR] = m_clientId;
  String output;
  serializeJson(m_doc, output);
  client.publish(path.c_str(), output.c_str());
}

void MQTTController::publishSingleValue(String path, String value) {
  m_doc.clear();
  m_doc[MQTT_SINGLE_VALUE_ATTR] = value;
  m_doc[MQTT_SENDER_DEVICE_ID_ATTR] = m_clientId;
  String output;
  serializeJson(m_doc, output);
  client.publish(path.c_str(), output.c_str());
}

void MQTTController::publishNull(String path) {
  client.publish(path.c_str(), "");
}

JsonObject MQTTController::newObject() {
  m_doc.clear();
  return m_doc.to<JsonObject>();
}

void MQTTController::publishObject(String path) {
  String output;
  serializeJson(m_doc, output);
  client.publish(path.c_str(), output.c_str());
}

void MQTTController::publishWarn(String msg) {
  publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_SW + String(MQTT_PATH_SEP) + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex())), msg);
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

  LOG_PRINT(F("Message length "));
  LOG_PRINTLN(length);
  LOG_PRINTLN(myTopic);
  LOG_PRINTLN(myValue);

  if (myValue.length()<=MQTT_JSON_MAX_LENGTH) {
    for (uint8_t i=0;i<m_callbackHandlerCount;i++) {
      if (m_callbackHandlers[i]->getTopics().indexOf(myTopic) != -1) {

        DeserializationError error = deserializeJson(m_doc, myValue);
        if (!error) {
          serializeJsonPretty(m_doc, Serial);
          
          if (m_doc.containsKey(MQTT_ACTOR_CMD_ATTR)) {
            if (m_doc[MQTT_ACTOR_CMD_ATTR].is<int>()) {
              LOG_PRINTLN(F("int"));
              m_callbackHandlers[i]->onMsgReceived(myTopic, m_doc[MQTT_ACTOR_CMD_ATTR].as<int>());
            } else if (m_doc[MQTT_ACTOR_CMD_ATTR].is<signed long>()) {
              LOG_PRINTLN(F("long"));
              m_callbackHandlers[i]->onMsgReceived(myTopic, m_doc[MQTT_ACTOR_CMD_ATTR].as<signed long>());
            } else if (m_doc[MQTT_ACTOR_CMD_ATTR].is<double>()) {
              LOG_PRINTLN(F("double"));
              m_callbackHandlers[i]->onMsgReceived(myTopic, m_doc[MQTT_ACTOR_CMD_ATTR].as<double>());
            } else if (m_doc[MQTT_ACTOR_CMD_ATTR].is<bool>()) {
              LOG_PRINTLN(F("bool"));
              m_callbackHandlers[i]->onMsgReceived(myTopic, m_doc[MQTT_ACTOR_CMD_ATTR].as<bool>());
            } else {
              LOG_PRINTLN(F("string"));
              m_callbackHandlers[i]->onMsgReceived(myTopic, String(m_doc[MQTT_ACTOR_CMD_ATTR].as<const char*>()));
            }
          } else {
            LOG_PRINTLN(F("missing value attribute"));
          }
        } else {
          LOG_PRINT(F("Message parse error "));
          LOG_PRINTLN(error.f_str());
        }
      }
    }
  } else {
    LOG_PRINT(F("Message too big "));
    LOG_PRINTLN(myValue.length());
  }
}
