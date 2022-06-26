#ifndef RELAYCONTROLLER_SHUTTER_H
#define RELAYCONTROLLER_SHUTTER_H

#include <AbstractIntervalTask.h>

#include "TaskIDs.h"
#include "MqttController.h"
#include <Property.h>

#define SHUTTER_DEFAULT_DURATION_FULL_OPEN_CLOSE 20000
#define SHUTTER_DEFAULT_DURATION_TURN_OPEN_CLOSE 2000

#define SHUTTER_DURATION_FULL_OPEN_CLOSE_SURPLUS 5000

#define SHUTTER_DIRECTION_NONE 0
#define SHUTTER_DIRECTION_UP 1
#define SHUTTER_DIRECTION_DOWN 2

#define PROPERTY_STATE 0
#define PROPERTY_CLOSE_STATE 1
#define PROPERTY_TILT_STATE 2

class RelayControllerShutter : public AbstractIntervalTask, public MQTTController::MQTTEventCallbackHandler, public Property<int>::ValueChangeListener {
public:
  RelayControllerShutter(String valueGroupState, String valueGroupCloseState, String valueGroupTiltState);
  ~RelayControllerShutter();

  void init();

  void update();

  void onMsgReceived(String topic, int value);

  String getTopics();

  void onPropertyValueChange(uint8_t id, int newValue, int oldValue);

  void switchRelay(bool relayUp, bool relayDown);

private:
  void onPropertyValueChangeState(int newValue, int oldValue);
  void onPropertyValueChangeCloseState(int newValue, int oldValue);
  void onPropertyValueChangeTiltState(int newValue, int oldValue);

  String m_valueGroupState;
  String m_valueGroupCloseState;
  String m_valueGroupTiltState;
  
  unsigned long m_lastSend = 0;
  Property<int> m_state;

  unsigned long m_lastAction = 0;
  Property<int> m_closeState;
  Property<int> m_tiltState;
  
  bool m_initializing = true;

  uint8_t m_direction = SHUTTER_DIRECTION_NONE;

  uint16_t m_shutterDurationFull = SHUTTER_DEFAULT_DURATION_FULL_OPEN_CLOSE;
  uint16_t m_shutterDurationTurn = SHUTTER_DEFAULT_DURATION_TURN_OPEN_CLOSE;

  void sendState();
  void sendCloseState();
  void sendTiltState();

};


#endif
