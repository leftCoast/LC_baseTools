#include "timeObj.h"

// So, everyone wants newbies to write blink without delay. This is good,
// because delay() is bad. Well, here's a simple way to do it..


timeObj  aTimer;                                           // Allocate a global timer.
int      LEDPin = 13;                                      // The LED we want to blink.
bool     LEDOn = false;                                    // We'll save the state of the LED here.


void setup() {

  pinMode(LEDPin, OUTPUT);                               // Initialize the digital pin as an output.
  aTimer.setTime(500);                                   // Set the timer for 500 ms. (1/2 second)
  aTimer.start();                                        // Fire up the timer.
}


void loop() {

  if (aTimer.ding()) {                                  // If the timer has expired..
    if(LEDOn) {                                         // If the LED is on..
      digitalWrite(LEDPin, LOW);                        // Turn the LED off.
      LEDOn = false;                                    // Make a NOTE of it.
    } else {                                            // Else, the LED was off..
      digitalWrite(LEDPin, HIGH);                       // Turn the LED on.
      LEDOn = true;                                     // Make a note of it.
  }
    aTimer.start();                                     // Restart the timer.
  }
}
