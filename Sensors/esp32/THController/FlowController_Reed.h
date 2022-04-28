#ifndef FLOWCONTROLLER_REED_H
#define FLOWCONTROLLER_REED_H

#include <AbstractIntervalTask.h>

#define FLOW_UPDATE_INTERVAL_MS 5000
#define FLOW_COUNT 4

class FlowControllerReed : public AbstractIntervalTask {
public:
  FlowControllerReed(String valueGroupStatus);

  void init();

  void update();

private:
  String m_valueGroupStatus;
  uint32_t lastValues[FLOW_COUNT];

};


#endif
