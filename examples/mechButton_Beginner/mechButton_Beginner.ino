#include <mechButton.h>

#define BUTTON_PIN 2                                       // Pin we'll hook the button to. The other side hooks to ground.
#define LED_PIN 13                                         // Usual pin number for built in LED.

mechButton button1(BUTTON_PIN);                            // Set button1 to pin 2.

// Your standard sketch setup()
void setup() {

  pinMode(LED_PIN, OUTPUT);                                // Set up our built in LED for flashing.
}

// Your standard sketch loop()
void loop() {

  bool buttonState;

  buttonState = button1.trueFalse();                       // Have a look at what the current button state is.
  digitalWrite(LED_PIN, !buttonState);                     // Since the button grounds when pushed, invert logic with !
}
