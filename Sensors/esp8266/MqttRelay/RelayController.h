#ifndef RELAYCONTROLLER_H
#define RELAYCONTROLLER_H

#include <AbstractIntervalTask.h>

#include "TaskIDs.h"
#include "MqttController.h"
#include <SoftwareSerial.h>

#define SHUTTER_DEFAULT_DURATION_FULL_OPEN_CLOSE 20000
#define SHUTTER_DEFAULT_DURATION_TURN_OPEN_CLOSE 2000

#define SHUTTER_DURATION_FULL_OPEN_CLOSE_SURPLUS 5000

#define RENEWAL_INTERVAL 1200

#define SHUTTER_DIRECTION_NONE 0
#define SHUTTER_DIRECTION_UP 1
#define SHUTTER_DIRECTION_DOWN 2

#define PROPERTY_STATE 0
#define PROPERTY_CLOSE_STATE 1
#define PROPERTY_TILT_STATE 2

class RelayController : public AbstractIntervalTask, public MQTTController::MQTTEventCallbackHandler {
public:
  RelayController(byte relayIndex);
  ~RelayController();

  void init();

  void lateInit(RelayController* invertController, String valueGroupState, int valueIndex);

  void update();

  void onMsgReceived(String topic, int value);

  String getTopics();

  bool switchRelay(bool state);

private:
  RelayController* m_invertController;
  byte m_relayIndex = 0;
  String m_valueGroupState;
  int m_valueIndex = 0;
  
  unsigned long m_lastSend = 0;
  unsigned long m_lastAction = 0;

  bool m_state = false;
  
  void sendState();
};


#endif
