
#include <arduino.h>
#include "blinker.h"

blinker::blinker(int inPin,float inOnMs, float inPeriodMs,boolean inInverse) :
timeObj(inPeriodMs) {


  init = false;
  running = false;
  lightOn = false;
  pin = inPin;
  setInverse(inInverse);
  onTimer = new timeObj(inOnMs);
}


blinker::~blinker(void) { delete(onTimer); }


void blinker::setInverse(boolean inInverse) { inverse = inInverse; }


void blinker::setLight(bool onOff) {
    
    if(onOff) { // light on!
        if (inverse) digitalWrite(pin,LOW);
        else digitalWrite(pin,HIGH);
    } else { // light off!
        if (inverse) digitalWrite(pin,HIGH);
        else digitalWrite(pin,LOW);
    }
    lightOn = onOff;
}


// This is your on/off switch. Call with a boolean tru=on false=off.
// The object is created in the "off" mode.
void blinker::setBlink(bool onOff) {

	if (!init) {					// Not intialized?
		hookup();					// Set up idling.
		pinMode(pin, OUTPUT);	// Now you are!
		init = true;				// Note it.
	}
	if((onOff!=running)) {		// ignore if no change
		if (onOff) {				// Start blinking..    
			start();					// Starting NOW!
			setLight(true);		// light on!
			onTimer->start();		// set the time on timer.
			running = true;		// Set state.
			} 
		else {						// Stop blinking..
			setLight(false);		// light off.
			running = false;		// set state.
		}
	}
}


bool blinker::blinking(void) { return running; }


void blinker::idle(void) {

  if (running) {
    if(lightOn) {                     // light is on.
      if (onTimer->ding()) {          // If time to turn it off..
        setLight(false);              // turn off.
      }
    } 
    else {                           // light's off
      if (ding()) {                  // If time to turn it on!
        setLight(true);              // on it goes.
        onTimer->start();            // set the time on timer.
        stepTime();                  // Reset timer for next on cycle.
      }
    }
  }
}


void blinker::setTimes(float inOnMs, float inPeriodMs) {

  onTimer->setTime(inOnMs);
  timeObj::setTime(inPeriodMs);
}



