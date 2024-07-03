#include "oneShot.h"


// Our constructor. All thie bits we can adjust at creation time.
oneShot::oneShot(int inPin,float shotTime,int outPin,bool outHiLow)
   : timeObj(shotTime,false),                     // Set up our pulse timer.
   idler() {                                      // Set up our idler class things.

   mButton        = new mechButton(inPin);        // Setup our button debouncer.
   mOutPin        = outPin;                       // Save our output pin number.
   mOutHiLow      = outHiLow;                     // Save our desired triggered state.
   mOurState      = waitForRelease;               // Set our initial state.
}


// The only thing we allocate is the mechButton.
// We release it here.
oneShot::~oneShot(void) { if (mButton) delete(mButton); }


// Those last little items we need to do before hitting the road..
void oneShot::begin(void) {

   pinMode(mOutPin,OUTPUT);                                // Setup our output pin.
   digitalWrite(mOutPin,!mOutHiLow);                       // Make sure its not in the triggered state.
   hookup();                                               // Hook into the idler queue.
}



// What we do al day..
void oneShot::idle(void) {

   switch(mOurState) {
      case preStart  :                                     // We are sitting, waiting for a button press.
         if (!mButton->trueFalse()) {                      // If we see the button get a press..
            start();                                       // We start our timer.
            digitalWrite(mOutPin,mOutHiLow);               // Kick the digital port into the saved (triggered) state.
            mOurState = running;                           // And our state is now running.
         }
      break;
      case running   :                                     // We have an active pulse going. Waiting for the timer to expire.
         if (ding()) {                                     // If the timer has expired..
            digitalWrite(mOutPin,!mOutHiLow);              // Toggle the output pin back to its rest state.
            mOurState = waitForRelease;                    // And our state is now waitForRelease.
         }
      break;
      case waitForRelease :                                // We are waiting to see when the button has been released.
         if (mButton->trueFalse()) {                       // If the button has been let up..
            mOurState = preStart;                          // We go back to preStart state.
         }
      break;
   }
}
