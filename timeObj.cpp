#include "timeObj.h"
#include <arduino.h>


timeObj::timeObj(float inMs) {

  startTime = 0;
  endTime = 0;
  setTime(inMs);        // This sets startTime and endTime. Best go here?
}


timeObj::~timeObj(void) { }


void timeObj::setTime(float inMs,bool startNow) {

  if (inMs>0)
    waitTime = round(1000*inMs);
  else
    waitTime = 0;
  if (startNow) start();
}


void timeObj::start(void) {

	startTime = micros();
	endTime = startTime + waitTime;
}


void timeObj::stepTime(void) {

	if (waitTime>0) {
		startTime = endTime;
		endTime = startTime + waitTime;
	}
}


bool timeObj::ding(void) { return micros() - startTime > waitTime; }


unsigned long timeObj::getTime(void) { return waitTime; }


// Fuel gauge. What fraction of time is left. Will this work with overruns? Dunno'. Deal
// with that when we run into it.
float timeObj::getFraction(void) {
	
	unsigned long remaining;
	
	if (ding()) return 0;
	remaining = endTime - micros();
	return((remaining/1000.0)/(waitTime/1000.0));
}								



