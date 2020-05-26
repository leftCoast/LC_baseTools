#include "squareWave.h"


squareWave::squareWave(float periodMs,float pulseMs, bool blocking) {

	setPeriod(periodMs);
	setPulse(pulseMs);
	mBlocking	= blocking;
	mState		= sittinIdle;
}

	
// Default constructor.
squareWave::squareWave(void) {

	mNextPeriod		= 0;
	mPeriodChange	= false;
	mNextPulse		= 0;
	mPulseChange	= false;
	mBlocking		= false;
	mState			= sittinIdle;
}


// Destructor, but there's really nothing to destruct.
squareWave::~squareWave(void) {  }


// People want to know if we're running or not.
bool squareWave::running(void) { return mState != sittinIdle; }


// Set a new period duration. This takes effect on the next pulse's startup.
void squareWave::setPeriod(float ms) {

	mNextPeriod = ms;			// Save it off.
	mPeriodChange = true;	// Flag the change.
}


// Set a new pulse duration. This also takes effect on the next pulse's startup.
void squareWave::setPulse(float ms) {

	if (ms<=mNextPeriod) {				// If the new pulse is less that or equal to the period..
		mNextPulse = ms;					// Save it off.
	} else {									// Else its longer than the period..
		mNextPulse = mNextPeriod;		// Then just use the period.
	}
	mPulseChange = true;					// In any case, flag the change.
}


// Set a new pulse duration as a percent of the period. Again, takes effect on
// the next pulse's startup.
void squareWave::setPercent(float perc) {
	
	float	ms;
	
	if (perc<0) perc = 0;					// Negitive? Set to zero.
	if (perc>100) perc = 100;				// Bigger than 100%, set to 100.
	ms = mNextPeriod * (perc/100.0);		// Calculate the new millisecond value.
	mNextPulse = ms;							// Save it off.
	mPulseChange = true;						// Flag the change.
}


// Set blocking for tight timing. At the expense of everyone else. Once the pulse is fired,
// the code will block while it watches for the timer to expire. Default is no blocking.
void squareWave::setBlocking(bool onOff) {  mBlocking = onOff; }


// This is your on/off switch. Default is off. Pass in a true value to fire it up.
void squareWave::setOnOff(bool onOff) {

	if (onOff) {					// If we're turning this machine on..
		hookup();					// Call to hookup() to ensure we're in the idle queue.
		startWave();				// Call to startWave() to get all the timers running.
	} else {							// Else, we are turning the machine off..
		mState = sittinIdle;		// We're idle now.
		pulseOff();					// I'm betting they would like to know its been shut down.
	}
}
	

// This is called when the pulse begins. The user filles this out for whatever action they
// want.	
void squareWave::pulseOn(void) {  }


// This is called when the pulse ends. Again, the user filles this out for whatever action
// they want. NOTE : If you set the pulse smaller or equal to the period, this will never
// be called.
void squareWave::pulseOff(void) {  }


// This sits in a loop watching the timer then calls pluseOff() when the timer dings.
void squareWave::block(void) {

	while (!mPulse.ding());	// Loop while the timer is running.
	mState = ridingLow;		// Set the state.
	pulseOff();					// Announce that the pulse is off!
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
	}
	if (mPulseChange) {										// If there is a change in the pulse width..
		mPulse.setTime(mNextPulse,false);				// Set the new pulse width into the timer.
		mPulseChange = false;								// Clear the change flag.
	}
	if (newWave) {												// If we need to start this..										
		mPeriod.start();										// Fire off the timer.
	} else {														// Else we are just continuing to run..
		mPeriod.stepTime();									// We just step the timer to the next value. (Calculated from last value.)
	}
	mPulse.start();											// Start up the pulse timer.
	mState = ridingHi;										// After all this we are riding hi.
	pulseOn();													// Announce that the pulse is on!
	if (mBlocking) {											// If we are blocking..
		block();													// Go block.
	}
}


// Our idel routine where everything runs in the background.
void squareWave::idle(void) {

	switch (mState) {						// Have a look at our state..
		case sittinIdle	: return;	// sitting idle? return as fast as possible.
		case ridingHi		:				// Riding high? Pulse is set to high.
			if (mPulse.ding()) {			// If the pulse timer has expired..
				mState = ridingLow;		// Swap the state to riding low.
				pulseOff();					// Announce it.
			}
		break;								// Jump out.
		case ridingLow :					// Riding low? Waiting to spin out the clock.
			if (mPeriod.ding()) {		// If the period timer has expired..
				startWave();				// We restart the cycle.
			}
		break;								// Done, jump out.
	}
}
