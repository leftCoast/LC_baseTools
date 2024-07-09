#include <idlers.h>
#include <timeObj.h>

// The global idler object list."
idlers theIdlers;


// The flag that says we are in the idle loop. So we don't get all reentrant on things.
bool idling = false;


// Our call that goes into loop(); to run the idlers.
void idle(void) {
  idling = true;
  theIdlers.idle();
  idling = false;
}


// In your main loop, call this for an effective delay. Keeps the idler's idling while you
// wait. Just drops out if called in idle time.
void sleep(float ms) {

  timeObj sleepTimer(ms);
  if (!idling) {
    while(!sleepTimer.ding()) idle();
  }
}


// *******************************
// idler, base object to give things the ability to run behind the scenes.
// *******************************

idler::idler(void) {
  hookedIn = false;
}


// Before we die, we need to tell our master to let us go.
idler::~idler(void) { theIdlers.unlinkObj(this); }


// You can't call this in the contstructor. Love to, but can't. So call this the first
// time you add data or turn your idler on.
//
// But, why not call this in constructor?
// Because hookup() relies on the idler global. We have no control over the global calls
// to constructors. So we need to wait 'till the global party is over, to be sure our
// world is in place, before we can be called. Don't create the animals before the planet
// has cooled down. Its just common sense.
//
// Now, if you make an object that will NEVER be defined as a global? Then maybe..
void idler::hookup(void) {
  if (!hookedIn) {
    theIdlers.addToTop(this);
    hookedIn = true;
  }
}


// idle(). We don't do anything here, but whomever inherits us will.
void idler::idle(void) { }



// *******************************
// idlers, management for the list of idlers.
// Is declared as a global and runs in th background.
// *******************************


idlers::idlers(void) : linkList() {  }


idlers::~idlers(void) { }


// Run down the list and call the idle() method on each one.
void idlers::idle(void) {

  idler* trace;

  trace = (idler*) theList;
  while(trace!=NULL) {
    trace->idle();
    trace = (idler*)trace->getNext();
  }
}


