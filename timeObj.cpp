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

    if (waitTime==0) {
        config = zero;
    } else {
        startTime = micros();
        endTime = startTime + waitTime;
        if (endTime < startTime) {
            config = crossing;
        } else {
            config = normal;
        }
    }
}


void timeObj::stepTime(void) {

    if (config!=zero) {
        startTime = endTime;
        endTime = startTime + waitTime;
        if (endTime < startTime) {
            config = crossing;
        } else {
            config = normal;
        }
    }
}


bool timeObj::ding(void) {
  
  unsigned long now;
    
    now = micros();
    switch (config) {
        case zero : return true;
        case crossing :
            if (now >= startTime || now < endTime)
                return false;
            else
                return true;
        break;
        case normal :
            if (now >= startTime && now < endTime)
                return false;
            else
                return true;
        break;
    }
    return true;    // To shut up compiler and shut down a broken timer.
}


unsigned long timeObj::getTime(void) { return waitTime; }


// Fuel gauge. What fraction of time is left.
float timeObj::getFraction(void) {
	
	unsigned long remaining;
	
	if (config==zero) return 0;
	if (ding()) return 0;
	remaining = endTime - micros();
	return((remaining/1000.0)/(waitTime/1000.0));
}								



