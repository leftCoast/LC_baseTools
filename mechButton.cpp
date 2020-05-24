#include "mechButton.h"


mechButton::mechButton(byte inPinNum) {
  pinNum = inPinNum;
  beenInitialized = false;
  checkNum = 0;
}


mechButton::~mechButton(void) {  }


bool mechButton::clicked(void) {

  if (beenInitialized) {                  // Ready to go? Lets look!
    if (setAs == digitalRead(pinNum)) {   // If we get another like the last.
      if (checkNum<NUM_CHECKS) {          // If we don't have enough checks.
        checkNum++;                       // We add another to the checkNum.
      }
    } else {                              // The reading didn't match the last one?
      setAs = !setAs;                     // Swap the setAs to the new reading.
      checkNum = 0;                       // Restart our count.
    }
  } else {																// Oh, not been initialized.
    pinMode(pinNum, INPUT_PULLUP);        // Do it.
    setAs = digitalRead(pinNum);          // What's the first thing we see? true or false?
    beenInitialized = true;               // Note it.
    return false;                         // Anyway, false to you.
  }
  if (!setAs && checkNum==NUM_CHECKS) {   // Only intereted in the Zero case with enough checks.
    return true;
  } else {
    return false;
  }
}

