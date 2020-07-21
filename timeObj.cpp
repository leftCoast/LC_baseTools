#include "timeObj.h"
#include <arduino.h>

// Our lovely constructor.
timeObj::timeObj(float inMs,bool startNow) {

  startTime	= 0;						// Just some default.
  endTime	= 0;						// And another default.
  ourState = preStart;					// We are sitting on pre Start state.
  setTime(inMs,startNow);        // This sets startTime and endTime. Maybe starts things up?
}


// And wonderful destructor..
timeObj::~timeObj(void) { }


// Used for setting the times and optionally starting the timer.
void timeObj::setTime(float inMs,bool startNow) {

  if (inMs>0)								// If we have a positive time..
    waitTime = round(1000*inMs);		// Convert it to unsigned integer of microseconds
  else										// Else, negitive time?
    waitTime = 0;							// Whatever. Set it to zero.
  ourState = preStart;					// At this point we are in preStart mode..
  if (startNow) start();				// If they passed in true for start now.. Start now.
}


// This starts the timer, no questions about it.
void timeObj::start(void) {

	startTime = micros();				// Save off the micros.
	endTime = startTime + waitTime;	// Calculate the end time.
	ourState = running;					// And we are running!
}


// If you have just expired your timer, this will restart your timer with the timer error
// between the two start back calculated out. Good for doing things like PWM base frequency
// stuff.
void timeObj::stepTime(void) {

	switch (ourState) {								// If the state is...
		case preStart : start();	break;		// What can we do? No previous end time to derive from.
		case expired :
			if (waitTime>0) {							// If we have a positive wait time..
				startTime = endTime;					// Our start is the last end.
				endTime = startTime + waitTime;	// Calculate the new end time.
				ourState = running;					// And we are running again!
			} else {										// Else, our wait time was zero..
				ourState = preStart;					// At this point we are in preStart mode..
			}
		break;
		case running : start();		break;		// What can we do? Fresh start from here.
	}
}


// Has the timer expired?
// Well, if it hasn't been started then no.
// If its running then lets calculate if its finished. And return that.
// If it has expired, then yes.
bool timeObj::ding(void) {

	switch (ourState) {										// If the state is...
		case preStart : return false;						// preStarted, not expired, return false.
		case running : 										// Started and running our timer, return when we expire.
			if (micros() - startTime > waitTime) {		// If our time has expired..
				ourState = expired;							// We are now expired.
				return true;									// Return true! 
			} else {												// Else, we are running but our time has NOT expired..
				return false;									// Return false;
			}
		case expired : return true;						// If we are expired, return true. (Forever more. Until restarted.)
	}									
}


/*
void timeObj::printState(void) {

	switch (ourState) {
		case preStart	: Serial.println("preStart");	break;
		case running	: Serial.println("running");	break;
		case expired	: Serial.println("expired");	break;
		default			: Serial.println("No idea!");	break;
	}
}
*/


// You wanted to see what the waitTime was?
unsigned long timeObj::getTime(void) { return waitTime; }


// Fuel gauge. What fraction of time is left. Give float value from one to zero.
float timeObj::getFraction(void) {
	
	unsigned long remaining;
	
	switch (ourState) {
		case preStart : return 1;
		case running : 
			remaining = endTime - micros();
			return((remaining/1000.0)/(waitTime/1000.0));
		case expired : return 0;
	}
}								



