#include "blinker.h"

// So everyone wants newbies to write blink without delay. This is good
// because delay() is bad. Well, here's the simple way to do it..

// Allocate a global blinker object.
blinker aBLinker;

void setup() {

	// Fire it up.
	aBLinker.setOnOff(true);
}


void loop() {

	// blinker is an idler. Calling idle() once in loop lets ALL idlers run.
	idle();
}
