#include "LEDController.h"
#include "TaskIDs.h"
#include "Pins.h"
#include "TaskManager.h"
#include <LogHelper.h>

LEDController::LEDController() : AbstractIntervalTask(100) {
}

void LEDController::init() {
  pinMode(PIN_LED, OUTPUT);
  setFlashFrequency(LED_FREQUENCY_INIT);
}

void LEDController::update() {
  if (currentIntervalMs > 0) {
    if (lastToggle == 0 || millis() > lastToggle + currentIntervalMs) {
      // ok, toggle
      currentState = !currentState;
      lastToggle = millis();
    }
  } else {
    currentState = false;
  }

  digitalWrite(PIN_LED, currentState ? HIGH : LOW);
}

void LEDController::setFlashFrequency(uint16_t intervalMs) {
  currentIntervalMs = intervalMs;
  lastToggle = 0;
  currentState = false;
}
