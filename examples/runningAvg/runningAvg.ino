#include <runningAvg.h>

/*
	Running average.

	This class was originally developed as a super simple to use data smoother. You decide, when creating
	it, how many data points you would like to smooth your data over. Then each time you add a data point
	it returns the running average of the last n points that were added. Simple to use, easy to understand.

	Then, of course, this opened up new horizons for things like; What was the max and min data points we
	saw in this set? So that was added.

	Then it was.. Well, what about sound? Sound is all about the delta between max and min. Delta was added.

	Then.. Yes, I also added standard deviation. What the heck? Everything else is in the pot. Might as
	well go for it all.

	Still, true to its roots, it only calculates the average when a datapoint is entered. All the rest
	are only calculated if/when the user actually asks for them. But they are there, ready to leap into
	action, if desired.

	So this example lets you add data points using the serial monitor and it'll print out all the stuff
	it can calculate with this data.

	Enjoy!

	-jim lee

*/


runningAvg  smoother(5);                                   // Our smoother. You can change the number of datapoints it will act on.
char        inBuff[80];                                    // A char buffer (c string) to hold your typings.
int         charIndex;                                     // An index to be used in storing charactors into our char buffer.


// Standard setup stuff..
void setup(void) {

	Serial.begin(9600);                                    // Fire up the serial stuff.
	inBuff[0] = '\0';                                       // Clear the c string.
	charIndex = 0;                                          // The next char we read in goes here.
	Serial.println(F("Enter numbers"));                     // Tell Mrs user to start inputting numbers.
}


// Standard loop stuff..
void loop(void) {

	char  aChar;                                            // A char to catch your typings in.
	float aValue;                                           // The float version of the number you typed.
	float ave;                                              // The Average that the smoother will return to us.

	if (Serial.available()) {                               // If there is a char in the waiting to be read..
		aChar = Serial.read();                               // Grab and save the char.
		if (aChar=='\n') {                                   // If its a newline char.. (Make sure the serial monitor is set to newline.)
			aValue = atof(inBuff);                            // Decode what we have read in so far as a float value. (Decimal number)
			ave = smoother.addData(aValue);                   // Pop this number into our smoother. (Running average object.) Out pops the average.
			Serial.println();                                 // From here down its just grabing info from the
			Serial.print(F("Entered    : "));                 // SMoother and displaying it on the serial monitor.
			Serial.println(inBuff);
			Serial.print(F("Data       : "));
			for(int i=0;i<smoother.getNumValues();i++) {
				Serial.print(smoother.getDataItem(i));
				Serial.print(" ");
			}
			Serial.println();
			Serial.print(F("Average   : "));
			Serial.println(ave,4);
			Serial.print(F("Min       : "));
			Serial.println(smoother.getMin(),4);
			Serial.print(F("Max       : "));
			Serial.println(smoother.getMax(),4);
			Serial.print(F("Delta     : "));
			Serial.println(smoother.getDelta());
			Serial.print(F("Deviation : "));
			Serial.println(smoother.getStdDev());
			Serial.println(F("--------------"));
			inBuff[0] = '\0';                                 // Clear the inBuff string.
			charIndex = 0;                                    // Reset the charIndex to start a new number string.
		} else {                                             // Else, it wasn't a newline char..
			inBuff[charIndex++] = aChar;                      // So we save the char we got into the c string.
			inBuff[charIndex] = '\0';                         // And pop an end of string after it.
		}
	}
}
