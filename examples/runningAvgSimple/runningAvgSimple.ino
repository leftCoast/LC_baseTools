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


runningAvg  smoother(5);                // Our smoother. You can change the number of datapoints it will act on.

void setup(void) {
	Serial.begin(9600);                   // Fire up the serial stuff.
	pinMode(A0, INPUT);
}

void loop(void) {
	int data = analogRead(A0);            // Read the pin, or enter the new data to avg.
	float ave = smoother.addData(data);   // The Average that the smoother will return to us.
	Serial.println(ave);
}
