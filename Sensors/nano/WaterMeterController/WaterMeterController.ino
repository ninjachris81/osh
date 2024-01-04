#include <DebounceEvent.h>

#define PIN_1 9
#define PIN_2 10
#define PIN_3 11
#define PIN_4 12

#define WARMUP_PHASE_MS 500

unsigned long lastHeartbeat = 0;

void callback(uint8_t pin, uint8_t event, uint8_t count, uint16_t length) {
  if (event == EVENT_PRESSED && millis() > WARMUP_PHASE_MS) {
    String s = "{\"e\":1,\"id\":" + String(pin) + ",\"ts\":" + String(millis()) + "}";
    Serial.println(s);
  }
}

DebounceEvent input1 = DebounceEvent(PIN_1, callback, BUTTON_PUSHBUTTON | BUTTON_SET_PULLUP);
DebounceEvent input2 = DebounceEvent(PIN_2, callback, BUTTON_PUSHBUTTON | BUTTON_SET_PULLUP);
DebounceEvent input3 = DebounceEvent(PIN_3, callback, BUTTON_PUSHBUTTON | BUTTON_SET_PULLUP);
DebounceEvent input4 = DebounceEvent(PIN_4, callback, BUTTON_PUSHBUTTON | BUTTON_SET_PULLUP);

void precheckConnection(uint8_t pin) {
  if (digitalRead(pin) == HIGH) {
    Serial.println("{\"e\":99,\"id\":" + String(pin) + "}");
  }
}



void setup() {
  Serial.begin(115200);
  
  precheckConnection(PIN_1);
  precheckConnection(PIN_2);
  precheckConnection(PIN_3);
  precheckConnection(PIN_4);
}

void loop() {
  input1.loop();
  input2.loop();
  input3.loop();
  input4.loop();

  if (millis() - lastHeartbeat > 10000) {
    Serial.println(F("{\"e\":0}"));
    lastHeartbeat = millis();
  }
}
