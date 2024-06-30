#include <timeObj.h>
#include <Arduino.h>


// Could be a little more, but this is fine. Ms times above this are NOT converted to
// micros. These longer times are run in Ms.
#define MAX_MICROS  4000000

// Our lovely constructor.
timeObj::timeObj(float inMs,bool startNow) {

  startTime = 0;                            // Just some default.
  endTime   = 0;                            // And another default.
  useMilli  = false;                        // Look! A third default.
  ourState  = preStart;                     // We are sitting on pre Start state.
  setTime(inMs,startNow);                   // This sets startTime and endTime. Maybe starts things up?
}


// And wonderful destructor..
timeObj::~timeObj(void) { }


// Used for setting the times and optionally starting the timer.
void timeObj::setTime(float inMs,bool startNow) {

	if (inMs>MAX_MICROS) {
		waitTime = round(inMs);             // Convert it to unsigned integer of milliseconds.
		useMilli = true;                    // We're using milliseconds this time round.
	} else if (inMs>0) {                    // If we have a positive time, less than MAX_MICROS.
		waitTime = round(1000*inMs);        // Convert it to unsigned integer of microseconds.
		useMilli = false;                   // We're using microseconds this time round.
	} else {                                // Else, negative time?
		waitTime = 0;                       // Whatever. Set it to zero.
		useMilli = false;                   // We're using microseconds this time round.
	}
  ourState = preStart;                      // At this point we are in preStart mode.
  if (startNow) start();                    // If they passed in true for startNow. Start now!
}


// This starts the timer, no questions about it.
void timeObj::start(void) {

	if (useMilli) {                         // If we are using milliseconds.
		startTime = millis();               // Save off the current milliseconds.
	} else {                                // Else, we're using microseconds.
		startTime = micros();               // Save off the current micros.
	}
	endTime = startTime + waitTime;         // Calculate the end time.
	ourState = running;                     // And we are running!
}


// If you have just expired your timer, this will restart your timer with the timer error
// between the two starts back calculated out. Good for doing things like PWM base frequency
// stuff.
void timeObj::stepTime(void) {

	switch (ourState) {                                          // If the state is.
		case preStart : start();    break;                       // What can we do? No previous end time to derive from.
		case expired :
			if (waitTime>0) {                                    // If we have a positive wait time.
				startTime = endTime;                             // Our start is the last end.
				endTime = startTime + waitTime;                  // Calculate the new end time.
				ourState = running;                              // And we are running again!
			} else {                                             // Else, our wait time was zero..
				ourState = preStart;                             // At this point we are in preStart mode.
			}
		break;
		case running : start();     break;                       // What can we do? Fresh start from here.
	}
}

/*
 Has the timer expired?
 Well, if it hasn't been started then no.
 If its running then lets calculate if its finished. And return that.
 If it has expired, then yes.
*/
bool timeObj::ding(void) {

	switch (ourState) {                                         // If the state is.
		case preStart : return false;                           // preStarted, not expired, return false.
		case running :                                          // Started and running our timer, return true when we expire.
			if (useMilli) {                                     // If we are using milliseconds.
				if (millis() - startTime > waitTime) {             // If our time has expired.
					ourState = expired;                         // We are now expired.
					return true;                                // Return true!
				} else {                                        // Else, we are running but our time has NOT expired.
					return false;                               // Return false!
				}
			} else if (micros() - startTime > waitTime) {       // Else, If we are using micros and our time has expired.
				ourState = expired;                             // We are now expired.
				return true;                                    // Return true!
			} else {                                            // Else, we are running but our time has NOT expired.
				return false;                                   // Return false;
			}
		case expired : return true;                             // If we are expired, return true. (Forever more. Until restarted.)
	}
	return false;                                               // Just to shut up compiler.
}

/*
 This brings your timer back to the preStart state. Ready for a start() call. Does not
 change the delay time already set in the object. Therefore its ready to start again
 when you need it. You don't need to use this call. ITs only used if you want to shut
 off the timer to be restarted at a later time.
*/
void timeObj::reset(void) { ourState = preStart; }

/*
void timeObj::printState(void) {

    switch (ourState) {
        case preStart   : Serial.println("preStart");   break;
        case running    : Serial.println("running");    break;
        case expired    : Serial.println("expired");    break;
        default         : Serial.println("No idea!");   break;
    }
    Serial.print("waitTime  :");
    if (useMilli) {                                             // If we are using milliseconds..
        Serial.print(waitTime * 1.0);
    } else {
        Serial.print(waitTime/1000.0);
    }
    Serial.println(" ms");
    Serial.print("startTime :");Serial.println(startTime);
    Serial.print("endTime   :");Serial.println(endTime);
}
*/


// You wanted to see what the waitTime was?This returns it as a float Ms.
float timeObj::getTime(void) {

	if (useMilli) return waitTime;
	else return waitTime/1000.0;
}


// Fuel gauge. What fraction of time is left. Give float value from one to zero.
float timeObj::getFraction(void) {

	unsigned long remaining;

	switch (ourState) {                                    // What are we doing now?
		case preStart : return 1;                          // It has not yet been started? Tank is full, 1.
		case running :                                     // We're running right now?
			if (useMilli) {                                // If we're using milliseconds..
				remaining = endTime - millis();            // Calculate the remaining milliseconds.
			} else {                                       // Else, we are  using microseconds..
				remaining = endTime - micros();            // Calculate the remaining micros.
			}
			return((remaining/1000.0)/(waitTime/1000.0));  // Return the normalized result. 0..1
		case expired : return 0;                           // Timer has expired? Tank is empty, 0.
	}
	return  0;                                             // Never able to get here. Shut up compiler!
}

