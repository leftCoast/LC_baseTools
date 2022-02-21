#include "oneShot.h"


// An example of a one-shot class.
// Press a button blink an LED one time.
// Have a look at oneShot.h file for more info.


// Create our one shot object. We wire the button
// to pin #2 and a pulse of 250 Ms. Leaving the
// rest of the paramiters as defaults.
oneShot ourOneShot(2,250); 


// Standard Arduino setup()
void setup(void) {
   
   ourOneShot.begin();  // We need to call its begin() method to start it.
}


// Standard Arduino loop()
void loop(void) { 
   
   idle();              // idle() allows time for all the background things to run.
}
