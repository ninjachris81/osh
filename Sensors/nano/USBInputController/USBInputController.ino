#include <Bounce2.h>

const int NUM_SWITCHES = 18; 
const int switchPins[NUM_SWITCHES] = {
  2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5
};

Bounce* switches = new Bounce[NUM_SWITCHES];
const int DEBOUNCE_INTERVAL = 50; 

// heartbeat timer
unsigned long lastHeartbeatTime = 0;
const unsigned long HEARTBEAT_INTERVAL = 10000;

void setup() {
  // Start the serial communication at the requested 9600 baud rate
  Serial.begin(9600);
  
  for (int i = 0; i < NUM_SWITCHES; i++) {
    switches[i].attach(switchPins[i], INPUT_PULLUP); 
    switches[i].interval(DEBOUNCE_INTERVAL); 
  }
}

void loop() {
  // 1. Scan all switches for instant state changes (Event-driven)
  for (int i = 0; i < NUM_SWITCHES; i++) {
    switches[i].update(); 
    
    // Check if the switch state has changed (either pressed or released)
    if (switches[i].changed()) {
      // Invert the physical signal: LOW (0) when pressed becomes 1, HIGH (1) becomes 0
      int state = !switches[i].read(); 
      
      // Call the custom method to print the state instantly
      printSwitchState(i, state);
    }
  }

  // 2. Send the status of all switches every 5 seconds (Heartbeat sync)
  if (millis() - lastHeartbeatTime >= HEARTBEAT_INTERVAL) {
    
    // Loop through all switches and print their current debounced state using the method
    for (int i = 0; i < NUM_SWITCHES; i++) {
      int state = !switches[i].read(); 
      printSwitchState(i, state);
    }
    
    lastHeartbeatTime = millis(); // Reset the timer
  }
}

void printSwitchState(int index, int state) {
  Serial.print(index);
  Serial.print(",");
  Serial.println(state);
}
