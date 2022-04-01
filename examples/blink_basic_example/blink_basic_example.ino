#include <blinker.h>

blinker blinkingLed(13, 200, 1000);   

// You can make as many blinker objects as you want. This one we are naming "blinkingLed", you then need 3 settings for this to work.
// BlinkingLed(ledPin, timeOn, timeBetweneBlinks); the first is the pin u want to blink, then the amount of time u want it on for.
// The last setting is the time inbetweene blinks. 
// EXAMPLE::::: nameOfblinker(PIN, ON_TIME, TIME_FOR_BLINKS);

void setup() {
  blinkingLed.setOnOff(true);    // If this is set to "true", the blinker will run, if "false"it will stop.

}

void loop() {
  idle();                        // Call idle() to let it all run. Only once.
}
