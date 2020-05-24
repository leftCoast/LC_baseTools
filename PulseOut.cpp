#include "PulseOut.h"


PulseOut::PulseOut(byte inPin , float inPeriod,bool inverse) 
	: timeObj(inPeriod),
	idler() {

  pin = inPin;
  pullDown = inverse;
  width = 0;
  init = false;
}


PulseOut::~PulseOut(void) { }


// Width is the width of the pulse.
void PulseOut::setWidth(float inWidth) {

  if (width!=inWidth) {
    if(width == 0) {                       // We are off, turn on!
      width = round(1000*inWidth);
      if (!init)  {                        // First time? Then initilize.
        hookup();                          // Set up idling.
        pinMode(pin, OUTPUT);              // Setup port.
        start();                           // Start the timer.
        init = true;                       // Note it.
      }
 	  if (pullDown) {				      // Is this necessary? Is it in the right place?
		digitalWrite(pin, HIGH);
	  } else {
		digitalWrite(pin, LOW);
	  }
    } 
    else
      width = round(1000*inWidth);
  } 
}


void PulseOut::idle(void) { 

  unsigned long startTime;
  unsigned long endPulse;

  if(ding()) {
    startTime = micros();
    if (pullDown) {
    	digitalWrite(pin, LOW);
    	endPulse = startTime + width;
    	stepTime();
    	while(micros() < endPulse);
    	digitalWrite(pin, HIGH);
    } else {
		digitalWrite(pin, HIGH);
	    endPulse = startTime + width;
	    stepTime();
	    while(micros() < endPulse);
	    digitalWrite(pin, LOW);
	}
  }
} 










