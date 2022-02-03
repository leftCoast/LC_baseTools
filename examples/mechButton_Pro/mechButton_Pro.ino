#include <mechButton.h>
#include <idlers.h>

#define BUTTON_PIN1  2     // Pin we'll hook the button to. The other side hooks to ground.
#define LED_PIN      13    // Usual pin number for built in LED.




// ***********************************************************
//                proButton class definition
//
//    Inherit from mechButton and create an class that does
//    your custom bidding.
// ***********************************************************


class proButton   : public mechButton {
   
   public:
                  proButton(int inPin);
   virtual        ~proButton(void);

            void  begin(void);
   virtual  void  takeAction(void);
            void  blank(int numBlanks);
            void  line(int numLines);
};



// ***********************************************************
//                proButton class code
// ***********************************************************


// Constructor, not much going on. Just passing the pin number in.
proButton::proButton(int inPin)
   :mechButton(inPin) {  }


// Destructor, nothing allocated so nothing to do.
proButton::~proButton(void) {  }


// begin, Needed somewhere to place the hookup() call. begin is tradional.
void proButton::begin(void) { hookup(); }


// blank, print some blanks.
void proButton::blank(int numBlanks) {

   for (int i=0;i<numBlanks;i++) {
      Serial.print(' ');
   }
}


// line, give us some blank lines
void proButton::line(int numLines) {

   for (int i=0;i<numLines;i++) {
      Serial.println();
   }
}


// takeAction, this is what's called when there is no callback set.
void proButton::takeAction(void) {

   if (setAs) {
      blank(36);
      Serial.println(F("Live long and prosper."));
   } else {
      line(4);
      blank(10);Serial.println(F("                                     ---------------------------==="));
      blank(10);Serial.println(F("            __                      ( |                          =="));
      blank(10);Serial.println(F("         /------\\                    ---------------------------="));
      blank(10);Serial.println(F("------------------------------           |  |"));
      blank(10);Serial.println(F("\\____________________________/]          |  |"));
      blank(10);Serial.println(F("         --------       \\     \\          |  |"));
      blank(10);Serial.println(F("                         \\     \\         |  |"));
      blank(10);Serial.println(F("                          \\ --------_____|  |__"));
      blank(10);Serial.println(F("                         | |              --  /"));
      blank(10);Serial.println(F("                        -||                  ||"));
      blank(10);Serial.println(F("                         | |__________/------== "));
      line(2);
   }
}



// ***********************************************************
//                   Sketch starts here..
// ***********************************************************


proButton button1(BUTTON_PIN1);  // Set button1 to pin 2.


// Your standard sketch setup()
void setup() {
   
   Serial.begin(57600);				// Fire up our serial monitor thing.
   pinMode(LED_PIN,OUTPUT);		// Set up the LED pin for output.
   button1.begin();					// Fire up the button. (Calls hookup() for idling.)
}


// Your standard sketch loop()
void loop() {
   
   bool	buttonState;
   
   idle();											// Let all the idlers have time to do their thing.
   buttonState = button1.trueFalse();		// Have a look at what the current button state is.
   digitalWrite(LED_PIN,!buttonState);		// Since the button grounds when pushed, invert logic with !
}
