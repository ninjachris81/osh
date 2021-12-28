#ifndef SOUNDCONTROLLER_PIEZO_H
#define SOUNDCONTROLLER_PIEZO_H

#include <AbstractIntervalTask.h>

#include "TaskIDs.h"
#include "MqttController.h"
#include <Property.h>

#define SOUND_INTERVAL_MS 100

#define TONE_PWM_CHANNEL 0

class SoundControllerPiezo : public AbstractIntervalTask, public MQTTController::MQTTEventCallbackHandler, public Property<int>::ValueChangeListener {
public:
  SoundControllerPiezo(String valueGroup);
  ~SoundControllerPiezo();

  void init();

  void update();

  void onMsgReceived(String topic, int value);

  String getTopics();

  void onPropertyValueChange(uint8_t id, int newValue, int oldValue);
  
private:
  String m_valueGroup;

  Property<int> m_state;
};


#endif
