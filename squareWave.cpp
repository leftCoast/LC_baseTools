#include "squareWave.h"


squareWave::squareWave(float periodMs,float pulseMs, bool blocking) {

	mNextPeriod		= periodMs;
	mPeriodChange	= true;
	mNextPulse		= pulseMs;
	mPulseChange	= true;
	mBlocking		= blocking;
	mRunning			= false;
}

	
// Default constructor.
squareWave::squareWave(void) {

	mNextPeriod		= 0;
	mPeriodChange	= false;
	mNextPulse		= 0;
	mPulseChange	= false;
	mBlocking		= false;
	mRunning			= false;
}


// Destructor, but there's really nothing to destruct.
squareWave::~squareWave(void) {  }


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

	if (onOff) {		// If we're turning this machine on..
		hookup();		// Call to hookup() to ensure we're in the idle queue.
		startWave();	// Call to startWave() to get all the timers running.
	} else {				// Else, we are turning the machine off..
		pulseOff();		// I'm betting they would like to know its been shut down.
	}
	mRunning = onOff;	// In any case, save the state we're in.
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
	pulseOff();					// Announce that the pulse is off!
}


// This starts each squareWave. First it checks if there are any changes. Then, starts the
// timers for the wave. If blocking is set to true, it will also call block() and wait
// 'till the pulse is complete.
void squareWave::startWave(void) {

	if (mPeriodChange) {								// If there is a change to the period..
		mPeriod.setTime(mNextPeriod,true);		// Set the new period into the timer. Then fire it off.
		mPeriodChange = false;						// Clear the change flag.
	} else {												// Else, no change..
		mPeriod.stepTime();							// We just step the timer to the next value. (Calculated from last value.)
	}
	if (mPulseChange) {								// If there is a change in the pulse width..
		mPulse.setTime(mNextPulse,true);			// Set the new pulse width into the timer. Then fire it off.
		mPulseChange = false;						// Clear the change flag.
	} else {												// Else, no change..
		mPulse.start();								// Start up the pulse timer.
	}
	pulseOn();											// Announce that the pulse is on!
	if (mBlocking) {									// If we are blocking..
		block();											// Go block.
	}
}


// Our idel routine where everything runs in the background.
void squareWave::idle(void) {

	if (mRunning) {
		if (mPeriod.ding()) {
			startWave();
		} else if (mPulse.ding()) {
			pulseOff();
		}
	}
}