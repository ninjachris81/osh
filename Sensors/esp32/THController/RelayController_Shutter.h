#ifndef RELAYCONTROLLER_SHUTTER_H
#define RELAYCONTROLLER_SHUTTER_H

#include <AbstractIntervalTask.h>

#include "TaskIDs.h"
#include "MqttController.h"
#include <Property.h>

#define SHUTTER_DURATION_MS 20000

class RelayControllerShutter : public AbstractIntervalTask, public MQTTController::MQTTEventCallbackHandler, public Property<int>::ValueChangeListener {
public:
  RelayControllerShutter(String valueGroup);
  ~RelayControllerShutter();

  void init();

  void update();

  void onMsgReceived(String topic, int value);

  String getTopics();

  void onPropertyValueChange(uint8_t id, int newValue, int oldValue);

  void switchRelay(bool relayUp, bool relayDown);

private:
  String m_valueGroup;
  unsigned long m_lastSend = 0;
  Property<int> m_state;

  unsigned long m_lastAction = 0;

  void sendValue();

};


#endif
