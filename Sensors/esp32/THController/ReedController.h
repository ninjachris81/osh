#ifndef REEDCONTROLLER_H
#define REEDCONTROLLER_H

#include <AbstractIntervalTask.h>

#define FLOW_UPDATE_INTERVAL_MS 5000

class ReedController : public AbstractIntervalTask {
public:
  ReedController(String valueGroupStatus);

  void init();

  void update();

private:
  String m_valueGroupStatus;

};


#endif
