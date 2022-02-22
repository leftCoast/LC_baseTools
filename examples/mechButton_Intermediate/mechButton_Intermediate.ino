// Adding a callback function example.
//
// In this example we'll setup and demo a callback. As well as read the button state in
// loop(). You don't need the button state stuff in loop() to make the callback stuff
// work. Its just there to show you two things going at once.

#include <mechButton.h>


#define BTN_PIN 2                                          // Pin we'll hook the button to. The other side hooks to ground.
#define LED_PIN 13                                         // Usual pin number for built in LED.

mechButton aButton(BTN_PIN);                               // Set button one to pin BTN_PIN.

// Your standard sketch setup()
void setup() {

  Serial.begin(9600);                                      // Fire up our serial monitor thing.
  pinMode(LED_PIN, OUTPUT);                                // Set up the LED pin for output.
  aButton.setCallback(myCallback);                         // Set up our callback. (Also calls hookup() for idling.)
}

// This is the guy that's called when the button changes state.
void myCallback(void) {

  Serial.print("Button just became ");
  if (aButton.trueFalse()) {
    Serial.println("true!");
  } else {
    Serial.println("false!");
  }
}

// Your standard sketch loop()
void loop() {

  bool buttonState;

  idle();                                                  // Let all the idlers have time to do their thing.
  buttonState = aButton.trueFalse();                       // Have a look at what the current button state is.
  digitalWrite(LED_PIN, !buttonState);                     // Since the button grounds when pushed, invert logic with !
}
