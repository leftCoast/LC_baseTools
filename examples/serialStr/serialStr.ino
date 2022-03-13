
// Tired of parsing out strings from serial data? The serialStr class should make this a
// snap! Create the object. Point it to a callback function. Make sure idle() is called in
// your main loop() and.. Vola! Complete c strings will magically arrive at your callback
// function, ready for you to process.
//
// The serialStr class is defaulted to use standard Serial as its port. Newline as the
// line ending character. A maximum buffer size of 64 characters. ALl three of these
// values can be changed by using different values in the constructor. See serialStr.h for
// more info.

#include <serialStr.h>


serialStr strReader;


void setup(void) {

	strReader.setCallback(haveStr);                         // Hook up our callback.
	Serial.begin(57600);                                    // Fire up the serial stuff.
	Serial.println(F("Enter something. I'll repeat it."));  // Tell Mrs user to start inputting numbers.
}


// This is your callback function. Complete c strings show up here, ready for you to process.
void haveStr(const char* inStr) {

	int i = 0;

	if (strReader.hadOverrun()) {                           // If we had an overrun..
		Serial.println(F("Oh no! overrun! Lost data!"));     // Tell the user.
	}
	Serial.print(F("Entered : "));                          // Show what we got..
	Serial.println(inStr);
	Serial.print(F("Reply   : "));                          // Show our reply.
	while(inStr[i]) {
		Serial.print((char)toupper(inStr[i++]));
	}
	Serial.println();
}


// idle() must be called here in the main loop(). This runs your serialStr object. And,
// don't use delay(). It stops everything. If you need to stop the main loop(), call
// sleep() instead. sleep() lets the serialStr object keep running in the background.
void loop(void) { 
	idle(); 
}
