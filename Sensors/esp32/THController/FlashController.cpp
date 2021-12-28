#include "FlashController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include <LogHelper.h>
#include <EEPROM.h>

FlashController::FlashController() : AbstractTask() {
}

void FlashController::init() {
  EEPROM.begin(EEPROM_SIZE);
  m_index = EEPROM.read(EEPROM_ADDRESS);

  LOG_PRINT(F("Using index "));
  LOG_PRINTLN(m_index);
}

void FlashController::update() {
  if (Serial.available() > 0) {
    String incomingData = Serial.readString();

    if (incomingData.length() <= 3 && isValidNumber(incomingData)) {
      int index = incomingData.toInt();

      if (index >=0 && index<256) {
        setIndex((uint8_t) index);
      }
  
    } else {
      LOG_PRINTLN(F("Invalid input - must be number"));
    }
  }
}

void FlashController::setIndex(uint8_t index) {
  LOG_PRINT("FLASHING INDEX ");
  LOG_PRINTLN(index);

  m_index = index;
  EEPROM.write(EEPROM_ADDRESS, m_index);
  EEPROM.commit();

  LOG_PRINTLN(F("Rebooting in 2 sec"));
  Serial.flush();
  delay(2000);
  
  ESP.restart();
}

uint8_t FlashController::getIndex() {
  return m_index;
}

bool FlashController::isValidNumber(String str){
  for(byte i=0;i<str.length();i++) {
    if(isDigit(str.charAt(i))) return true;
  }
  return false;
}
