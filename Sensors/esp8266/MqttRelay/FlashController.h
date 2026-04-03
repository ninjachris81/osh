#ifndef FLASHCONTROLLER_H
#define FLASHCONTROLLER_H

#include <AbstractTask.h>

#include "TaskIDs.h"

#define EEPROM_SIZE 1
#define EEPROM_ADDRESS 0

class FlashController : public AbstractTask {
public:
  FlashController();

  void init();

  void update();

  void setIndex(uint8_t index);

  uint8_t getIndex();

private:
  uint8_t m_index = 0;

  bool isValidNumber(String str);
};


#endif
