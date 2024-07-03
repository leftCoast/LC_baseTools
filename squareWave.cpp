#include "squareWave.h"

// Constructor with all the goodies.
squareWave::squareWave(float periodMs,float pulseMs, bool blocking) {

	init();
	setPeriod(periodMs);
	setPulse(pulseMs);
	mBlocking   = blocking;
}


// Default constructor.
squareWave::squareWave(void) { init(); }


// Setup all the defaults for the constructors.
void squareWave::init(void) {

	mNextPeriod     = 0;
	mPeriodChange   = false;
	mNextPulse      = 0;
	mPulseChange    = false;
	mBlocking       = false;
	mState          = sittinIdle;
	mSignal         = false;
}


// Destructor, but there's really nothing to destruct.
squareWave::~squareWave(void) {  }


// People want to know if we're running or not.
bool squareWave::running(void) { return mState != sittinIdle; }


// People want to know if the state is high or low at the moment. Here it is.
bool squareWave::pulseHiLow(void) { return mSignal; }


// Set a new period duration. This takes effect on the next pulse's startup.
void squareWave::setPeriod(float ms) {

	if (ms<0) ms = 0;				// Sanity, no negatives!
	if (ms!=mNextPeriod) {		// Only bother them if its different.
		mNextPeriod = ms;			// Save it off.
		mPeriodChange = true;	// Flag the change.
	}
}


// Set a new pulse duration. This also takes effect on the next pulse's startup.
void squareWave::setPulse(float ms) {

	if (ms<0) ms = 0;			// Sanity, no negatives!
	if (ms!=mNextPulse) {	// Only bother them if its different.
		mNextPulse = ms;		// Save it off.
		mPulseChange = true;	// In any case, flag the change.
	}
}


// Set a new pulse duration as a percent of the period. Again, takes effect on
// the next pulse's startup.
void squareWave::setPercent(float perc) {

	float   ms;

	if (perc<0) perc = 0;				// Negitive? Set to zero.
	if (perc>100) perc = 100;			// Bigger than 100%, set to 100.
	ms = mNextPeriod * (perc/100.0);	// Calculate the new millisecond value.
	setPulse(ms);							// Set it.
}


// Set blocking for tight timing. At the expense of everyone else. Once the pulse is fired,
// the code will block while it watches for the timer to expire. Default is no blocking.
void squareWave::setBlocking(bool onOff) {  mBlocking = onOff; }


// This is your on/off switch. Default is off. Pass in a true value to fire it up.
// NOTE : If the wave is currently at zero when this is called with a false. The user
// will NOT get a call to pulseOff(). So don't relay on that method to be called.
void squareWave::setOnOff(bool onOff) {

	hookup();					// Call to hookup() to ensure we're in the idle queue.
	if (onOff) {				// If we're turning this machine on..
		startWave();			// Call to startWave() to get all the timers running.
	} else {						// Else, we are turning the machine off..
		mState = sittinIdle;	// We're idle now.
		ourPulseOff();			// I'm betting they would like to know its been shut down.
	}
}


// We're going to track if the signal is on or off. Only broadcast changes.
void squareWave::ourPulseOn(void) {

	if (!mSignal) {
		pulseOn();
		mSignal = true;
	}
}


// This is called when the pulse begins. The user inherits and filles this out for whatever
// action they want.
void squareWave::pulseOn(void) {  }


// Just like the one above. We're going to track if the signal is on or off. Only
// broadcast changes.
void squareWave::ourPulseOff(void) {

	if (mSignal) {
		pulseOff();
		mSignal = false;
	}
}


// This is called when the pulse ends. Again, the user inherits and filles this out for
// whatever action they want. NOTE : If you set the pulse smaller or equal to the period,
// this will never be called.
void squareWave::pulseOff(void) {  }


// This sits in a loop watching the timer then calls pluseOff() when the timer dings.
void squareWave::block(void) {

	while (!mPulse.ding() && !mPeriod.ding());	// BLOCK here while the timer is running.
	mState = ridingLow;									// Set the state.
	if (mPulse.ding()) {									// If it was the pulse timer that fired..
		ourPulseOff();										// Shut down the pulse. ( 100% pulse is waste of blocking. But, whatever. )
	}
}


// This starts each squareWave. First it checks if there are any changes. Then, starts the
// timers for the wave. If blocking is set to true, it will also call block() and wait
// 'till the pulse is complete.
void squareWave::startWave(void) {

	bool newWave;

	newWave = mPeriodChange || mState==sittinIdle;	// Are we starting a new wave?
	if (mPeriodChange) {										// If there is a change to the period..
		mPeriod.setTime(mNextPeriod,false);				// Set the new period into the timer.
		mPeriodChange = false;								// Clear the change flag.
	}																//
	if (mPulseChange) {										// If there is a change in the pulse width..
		mPulse.setTime(mNextPulse,false);				// Set the new pulse width into the timer.
		mPulseChange = false;								// Clear the change flag.
	}																//
	if (newWave) {												// If we need to start a fresh wave..
		mPeriod.start();										// Fire off the timer.
	} else {														// Else, we are just continuing to run..
		mPeriod.stepTime();									// We just step the timer to the next value. (Calculated from last value.)
	}																//
	mPulse.start();											// Start up the pulse timer.
	if (mNextPulse) {											// If the pulse width is >0..
		mState = ridingHi;									// After all this we are riding hi.
		ourPulseOn();											// Fire up the pulse.
		if (mBlocking) {										// If we are blocking..
			block();												// Go block.
		}															//
	} else {														// Else no pulse?
		mState = ridingLow;									// Then we're just waiting to ride out the period timer.
	}
}


// Our idle routine where everything runs in the background.
void squareWave::idle(void) {

	switch (mState) {					// Have a look at our state..
		case sittinIdle : return;	// sitting idle? return as fast as possible.
		case ridingHi       :		// Riding high? Pulse is set to high.
			if (mPulse.ding()) {		// If the pulse timer has expired..
				mState = ridingLow;	// Swap the state to riding low.
				ourPulseOff();			// Announce it.
			}								//
	break;								// Jump out.
	case ridingLow :					// Riding low? Waiting to spin out the clock.
			if (mPeriod.ding()) {	// If the period timer has expired..
				startWave();			// We restart the cycle.
			}								//
		break;							// Done, jump out.
	}
}

/*
void squareWave::printState(void) {

    Serial.print("squareWave, we are : ");
    switch(mState) {
        case sittinIdle : Serial.println("Sitting idle"); break;
        case ridingHi       : Serial.println("Riding high!"); break;
        case ridingLow      : Serial.println("Riding Low."); break;
    }
    Serial.println("mPeriod timeObj");
    mPeriod.printState();
    Serial.println();
    Serial.println("mPulse timeObj");
    mPulse.printState();
    Serial.println();
}
*/