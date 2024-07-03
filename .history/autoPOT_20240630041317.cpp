#include <autoPOT.h>


autoPOT::autoPOT(int inPin) {

  callback = NULL;  // Because it ain't.
  pinNum = inPin;   // Because they said.
  value  = -1;      // Because it can't.
}


// Nothing to do here this is a virtual destructor.
autoPOT::~autoPOT(void) {  }


// User tells us what to call when we see a change.
void autoPOT::setCallback(void(*funct)(int)) {

  callback = funct;
  hookup();
}


// What we do in the background.
void autoPOT::idle(void) {

  int newVal;
  if (callback) {
    newVal = analogRead(pinNum);
    if (newVal!=value) {
      value = newVal;
      callback(value);					// Call our callback with the buffer.
    }
  }
}
