#include <autoPOT.h>
unsigned long lastPrintTime = 0;
const int POT_PIN = A0;
autoPOT myPot(POT_PIN);

void potCallback(int value) {
	Serial.print("Potentiometer value changed: ");
	Serial.println(value);
}

void setup() {
	Serial.begin(9600);

	// Set the callback function
	myPot.setCallback(potCallback);

	// Print the initial average reading
	Serial.print("Initial average reading: ");
	Serial.println(myPot.quickAverage());
}

void loop() {

	// Periodically get and print a quick average
	if (millis() - lastPrintTime > 5000) {
		Serial.print("5-second average: ");
		Serial.println(myPot.quickAverage(5));
		lastPrintTime = millis();
	}
}