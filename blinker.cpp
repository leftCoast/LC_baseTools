
#include <Arduino.h>
#include <blinker.h>

blinker::blinker(int inPin,float inOnMs, float inPeriodMs,boolean inInverse)
    : squareWave(inPeriodMs,inOnMs) {

  init = false;
  pin = inPin;
  inverse = inInverse;
}


blinker::~blinker(void) { }


// What to do when the pulse comes on..
void  blinker::pulseOn(void) {

	if (inverse) digitalWrite(pin,LOW);
	else digitalWrite(pin,HIGH);
}


// What to do when the pulse is over..
void  blinker::pulseOff(void) {

	if (inverse) digitalWrite(pin,HIGH);
	else digitalWrite(pin,LOW);
}


// This is your on/off switch. Call with a boolean tru=on false=off.
// The object is created in the "off" mode.
void blinker::setOnOff(bool onOff) {

	if (!init) {                                           // Not intialized?
		pinMode(pin, OUTPUT);                              // Now you are!
		init = true;                                       // Note it.
	}
	if(onOff!=running()) {                                 // Ignore if no change.
		squareWave::setOnOff(onOff);
	}
}


bool blinker::blinking(void) { return running(); }



