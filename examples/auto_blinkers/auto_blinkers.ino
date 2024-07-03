// Auto blinker switch example.
//
// The auto blinker question comes up regularly in the Arduino forum so
// I figured an example of that would be just the ticket. This uses two
// binker objects for the blinking LEDs and three mechButton objects for
// the three buttons. A left, right and Hazard button. The first press
// of a button, say right, turns on that blinker. The second turns it
// back off. If another button is pressed, say left, then the code just
// switches from right to left. So each button is one click on, second
// click off.
//
// The buttons should be wired one side to the pin number choosen and
// the other to ground. the mechButton object will do the debounceing
// for you as well as call your callback routines when clicked. The
// blinker objects take care of the blinking. All these behind the
// scenes functions happen when you call idle() in your loop function.
//
// You can add more stuff to your loop() function if you want. But DO
// NOT USE delay(). No fear though, this stuff comes with sleep() witch
// acts on the main loop() just like delay(), but lets the background
// stuff keep running.
//
// Have fun!
// jim lee



#include <blinker.h>
#include <mechButton.h>

#define BLINK_PERIOD  1000                                 // Ms
#define BLINK_LIT     500                                  // ms
#define BLINK_L_PIN   5                                    // Pin NUM
#define BLINK_R_PIN   6                                    // Pin NUM
#define BTN_L_PIN     2                                    // Pin NUM
#define BTN_R_PIN     3                                    // Pin NUM
#define BTN_H_PIN     4                                    // Pin NUM

enum blinkComs { blinkOff, blinkLeft, blinkRight, blinkHazard };// Set up our list of states.
blinkComs   currentState;                                       // A variable to save our current state.
blinker     leftBlinker(BLINK_L_PIN, BLINK_LIT, BLINK_PERIOD);  // The left blinker object. A "fire and forget" blinker object.
blinker     rightBlinker(BLINK_R_PIN, BLINK_LIT, BLINK_PERIOD); // The right blinker object. Same as left, different pin.
mechButton  lButton(BTN_L_PIN);                                 // The left blinker button. Another "fire and forget" object.
mechButton  rButton(BTN_R_PIN);                                 // The right blinker button. Same as left, different pin.
mechButton  hButton(BTN_H_PIN);                                 // And your hazard button. Wouldn't be complete without them.


// Standard setup.
void setup() {

  currentState = blinkOff;                                 // We start with the blinkers off. So note that.
  lButton.setCallback(clickLBtn);                          // Hook the button objects to their respective callbacks.
  rButton.setCallback(clickRBtn);                          // Hooking..
  hButton.setCallback(clickHBtn);                          // Hooking..
}


// When the LEFT button is clicked, this is called..
void clickLBtn(void) {

  if (!lButton.trueFalse()) {                              // If the button has been grounded..
    if (currentState == blinkLeft) {                       // If we are already doing this mode..
      setBlinkers(blinkOff);                               // We just shut off everything.
    } else {                                               // Else, doing something else..
      setBlinkers(blinkLeft);                              // We switch to our mode.
    }
  }
}


// When the RIGHT button is clicked, this is called..
void clickRBtn(void) {

  if (!rButton.trueFalse()) {                              // If the button has been grounded..
    if (currentState == blinkRight) {                      // If we are already doing this mode..
      setBlinkers(blinkOff);                               // We just shut off everything.
    } else {                                               // Else, doing something else..
      setBlinkers(blinkRight);                             // We switch to our mode.
    }
  }
}


// When the HAZARD button is clicked, this is called..
void clickHBtn(void) {

  if (!hButton.trueFalse()) {                            // If the button has been grounded..]
    if (currentState == blinkHazard) {                  // If we are already doing this mode..
      setBlinkers(blinkOff);                           // We just shut off everything.
    } else {                                            // Else, doing something else..
      setBlinkers(blinkHazard);                        // We switch to our mode.
    }
  }
}


// Set the blinkers to a new mode. Then note what mode they are in.
void setBlinkers(blinkComs theBlinkCom) {

  switch (theBlinkCom) {                                  // If the new mode is..
    case blinkOff     :                                   // blinkOff.
      leftBlinker.setOnOff(false);                        // Left blinker off.
      rightBlinker.setOnOff(false);                       // Right blinker off.
      break;
    case blinkLeft    :                                   // blinkLeft
      leftBlinker.setOnOff(true);                         // Left blinker on.
      rightBlinker.setOnOff(false);                       // Right blinker off.
      break;
    case blinkRight   :                                   // blinkRight
      leftBlinker.setOnOff(false);                        // Left blinker off.
      rightBlinker.setOnOff(true);                        // Right blinker on.
      break;
    case blinkHazard  :                                   // blinkRight
      leftBlinker.setOnOff(false);                        // Left blinker off. (Both off to synk them up)
      rightBlinker.setOnOff(false);                       // Right blinker off.
      leftBlinker.setOnOff(true);                         // Left blinker on.
      rightBlinker.setOnOff(true);                        // Right blinker on.
      break;
  }
  currentState = theBlinkCom;                             // And note the new state of the universe.
}


// Everything is run behind the scenes so all loop()
// needs to do is call idle() to let it all run.
void loop() {
  idle();
}
