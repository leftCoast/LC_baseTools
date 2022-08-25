#include <blinker.h>

blinker blinkingLed(13, 200, 1000);   


// You can make as many blinker objects as you want. This one we are naming "blinkingLed",
// you then need 3 settings for this to work.
//
// blinkingLed(ledPin, timeOn, timeBetweneBlinks);
//
// The first is the pin you want to blink, then the amount of time u want it on for. The
// last setting is the time from the start of one blink to the start of the next.
//
// EXAMPLE::::: nameOfblinker(PIN, ON_TIME, TIME_FOR_BLINKS);


void setup() {
  
  blinkingLed.setOnOff(true);    // If this is set to "true", the blinker will run, if "false"it will stop.
}

void loop() {
  idle();                        // idle() allows time for all the background things to run.
}
