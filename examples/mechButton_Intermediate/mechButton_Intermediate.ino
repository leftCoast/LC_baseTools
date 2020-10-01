#include <mechButton.h>
#include <idlers.h>

#define BUTTON_PIN1  2     // Pin we'll hook the button to. The other side hooks to ground.
#define LED_PIN      13    // Usual pin number for built in LED.


mechButton button1(2);  // Set button one to pin 2.


// Your standard sketch setup()
void setup() {
   
   Serial.begin(57600);						// Fire up our serial monitor thing.
   pinMode(LED_PIN,OUTPUT);				// Set up the LED pin for output.
   button1.setCallback(myCallback);		// Set up our callback. (Also calls hookup() for idling.)
}


// This is the guy that's called when the button changes state.
void myCallback(void) {

   Serial.print("Button just became ");
   if (button1.trueFalse()) {
      Serial.println("true!");
   } else {
      Serial.println("false!");
   }
}


// Your standard sketch loop()
void loop() {
   
   bool	buttonState;
   
   idle();											// Let all the idlers have time to do their thing.
   buttonState = button1.trueFalse();		// Have a look at what the current button state is.
   digitalWrite(LED_PIN,!buttonState);		// Since the button grounds when pushed, invert logic with !
}
