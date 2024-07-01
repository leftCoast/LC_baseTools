#include <mechButton.h>

#define NUM_CHECKS  4				// Number of conflicting checks in a row that tells us to change.


// Constructor, we just need a pin number to make this go.
mechButton::mechButton(byte inPinNum)
	: idler() {

	mTimer.setTime(1);
	callback                = NULL;
	pinNum                  = inPinNum;
	checkNum                = 0;
	beenInitialized         = false;
}


// Destructor. We didn't allocate anything so nothing to do here.
mechButton::~mechButton(void) {  }


// truFalse() is the old version of getState().
bool mechButton::trueFalse(void) { return getState(); }


// getState() is the method that returns the state of the button and tracks the amount of
// conflicting states are seen.
bool mechButton::getState(void) {

	if (!beenInitialized) {											// If not ready to run.
		pinMode(pinNum,INPUT_PULLUP);								// Set up our pin.
		setAs = digitalRead(pinNum);								// The first thing we see is our initial state.
		beenInitialized = true;										// Note we are open for business.
		mTimer.start();												// And don't bug us again for this much time.
	} else {																// Else, we are already up and running.
		if (mTimer.ding()) {											// If the timer has expired..
			if (setAs == digitalRead(pinNum)) {					// If we get another reading like the saved state.
				checkNum = 0;											// Reset to zero conflicting readings.
			} else {														// Else, its a conflicting reading.
				checkNum++;												// Bump up checkNum.
				if (checkNum>=NUM_CHECKS) {						// If we have enough conflicting readings.
					setAs = !setAs;									// Flip our state.
					checkNum = 0;										// Reset to zero conflicting readings.
					if (callback) {									// If we have a callback.
						callback();										// call it.
					} else {												// Else, no callback..
						takeAction();									// Do whatever action is required.
					}
				}
			}
			mTimer.start();											// Don't bug us, restarting the timer.
		}
	}
	return setAs;														// In all cases, return how we are set.
}

/*
 Define a void function, for example : void myCallback(void){...}
 Then, just call this method with your callback's name.
 myButton.setCallback(myCallback);
 Simple as that.
*/
void mechButton::setCallback(void (*funct)(void)) {

	callback = funct;
	hookup();
}

/*
 If one would like to inherit this and have a call to fill out for action.. This is it!
 Doesn't actually do anything in the base class.
*/
void mechButton::takeAction(void) { }

/*
 If hookup() has been called, we auto-call getState(). This is expecting that a
 callback has been set to deal with state change on the switch. Otherwise this will do
 basically nothing. As the return value of getState() is being ignored.
*/
void mechButton::idle(void) { getState(); }

