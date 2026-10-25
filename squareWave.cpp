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

   if (ms<MIN_PERIOD_MS) {                       // Sanity we only go -that- small.
      ms = MIN_PERIOD_MS;                        // There's the limit.
   }                                             //
   if (ms!=mNextPeriod) {                        // Only bother them if its different.
      mNextPeriod = ms;                          // Save it off.
      mPeriodChange = true;                      // Flag the change.
   }
}


// Set a new pulse duration. This also takes effect on the next pulse's startup.
void squareWave::setPulse(float ms) {

   if (ms<0) ms = 0;                             // Sanity, no negatives!
   if (ms!=mNextPulse) {                         // Only bother them if its different.
      mNextPulse = ms;                           // Save it off.
      mPulseChange = true;                       // In any case, flag the change.
   }
}


// Set a new pulse duration as a percent of the period. Again, takes effect on
// the next pulse's startup.
void squareWave::setPercent(float perc) {

   float   ms;

   if (perc<0) perc = 0;                         // Negitive? Set to zero.
   if (perc>100) perc = 100;                     // Bigger than 100%, set to 100.
   ms = mNextPeriod * (perc/100.0);              // Calculate the new millisecond value.
   setPulse(ms);                                 // Set it.
}


// Set blocking for tight timing. At the expense of everyone else. Once the pulse is fired,
// the code will block while it watches for the timer to expire. Default is no blocking.
void squareWave::setBlocking(bool onOff) {  mBlocking = onOff; }

/*
 * Toggle the wave on or off. Default is off. Pass true to activate.
 * WARNING: If the wave is currently low and you call this with false,
 * pulseOff() will NOT be invoked. Do not rely on that method being called.
*/
void squareWave::setOnOff(bool onOff) {
/*
 * Ensure we are registered in the idle queue before proceeding.
 * If turning on: start the wave and begin all timers.
 * If turning off: set state to idle and notify the user via ourPulseOff().
*/

   hookup();
   if (onOff) {
      startWave();
   } else {
      mState = sittinIdle;
      ourPulseOff();
   }
}


/*
 * Manually set the wave high or low, regardless of current state or timer.
 * Useful when you want direct control instead of timer-driven operation.
 * Note: This bypasses the normal pulse cycle and may disrupt timed operation.
*/

void squareWave::manualSetHiLow(bool hiLow) {

   if (hiLow) ourPulseOn();
   else ourPulseOff();
}


// We're going to track if the signal is on or off. Only broadcast changes.
void squareWave::ourPulseOn(void) {

   if (!mSignal) {
      pulseOn();
      mSignal = true;
   }
}


// This is called when the pulse begins. The user inherits and fills this out for whatever
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


/*
 * Called when a pulse cycle completes. Override in your subclass to perform
 * custom actions. NOTE: This method is never invoked if the pulse duration
 * is less than or equal to the period duration.
*/

void squareWave::pulseOff(void) {  }


// This sits in a loop watching the timer then calls pulseOff() when the timer dings.
void squareWave::block(void) {
/*
 * Wait for the timer to expire while monitoring for completion.
 * Set state to low when done. If the pulse timer fired first,
 * stop the pulse before returning.
*/


   while (!mPulse.ding() && !mPeriod.ding());
   mState = ridingLow;
   if (mPulse.ding()) {
      ourPulseOff();
   }
}

/*
 * Initialize the wave by checking for pending changes, applying any updates
 * to the period or pulse timers, and starting the appropriate timer.
 * If blocking mode is enabled, waits for the pulse to complete before returning.
 * If no pulse width is defined, transitions to the low state and waits for the period timer.
*/

void squareWave::startWave(void) {

   bool newWave;

   newWave = mPeriodChange || mState==sittinIdle;
   if (mPeriodChange) {
      mPeriod.setTime(mNextPeriod,false);
      mPeriodChange = false;
   }
   if (mPulseChange) {
      mPulse.setTime(mNextPulse,false);
      mPulseChange = false;
   }
   if (newWave) {
      mPeriod.start();
   } else {
      mPeriod.stepTime();
   }
   mPulse.start();
   if (mNextPulse) {
      mState = ridingHi;
      ourPulseOn();
      if (mBlocking) {
         block();
      }
   } else {
      mState = ridingLow;
   }
}


// Our idle routine where everything runs in the background.
void squareWave::idle(void) {

   switch (mState) {                             // Have a look at our state.
      case sittinIdle : return;                  // sitting idle? return as fast as possible.
      case ridingHi       :                      // Riding high? Pulse is set to high.
         if (mPulse.ding()) {                    // If the pulse timer has expired.
            mState = ridingLow;                  // Swap the state to riding low.
            ourPulseOff();                       // Announce it.
         }                                       //
   break;                                        // Jump out.
   case ridingLow :                              // Riding low? Waiting to spin out the clock.
         if (mPeriod.ding()) {                   // If the period timer has expired.
            startWave();                         // We restart the cycle.
         }                                       //
      break;                                     // Done, jump out.
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