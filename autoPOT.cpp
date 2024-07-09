#include <autoPOT.h>


autoPOT::autoPOT(int inPin) {
  
	callback	= NULL;  // Bacause it ain't
	pinNum	= inPin;	// Because they said.
	value		= -1;		// Because it can't.
	window	= 0;		// Because not now.	
}


// Nothing to do here.
autoPOT::~autoPOT(void) {  }


// User tells us what to call when we see a change.
void autoPOT::setCallback(void(*funct)(int)) {

  callback = funct;
  hookup();
}


// Sets a +/- window where changed in value from the analog port are ignored. Get a value
// beyond this 'window" and the change is announced in the callback.
void autoPOT::setWindow(int plusMinus) { window = abs(plusMinus); }


// What we do in the background.
void autoPOT::idle(void) {

  int newVal;
  
  if (callback) {													// If we have a callback ready?
    newVal = analogRead(pinNum);								// Read the analog port.
    if (newVal>value+window||newVal<value-window) {	// If it falls outside our window..
      value = newVal;											// Save off the new value.
      callback(value);											// Call our callback with the value.
    }
  }
}
