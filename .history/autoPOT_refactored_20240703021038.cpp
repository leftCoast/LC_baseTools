#include <autoPOT.h>

// Constructor: Initializes the autoPOT object
autoPOT::autoPOT(int inPin) {
	callback    = NULL;		// Initialize callback to null
	pinNum      = inPin; 	// Store the input pin number
	value       = -1;			// Initialize value to -1 (invalid reading)
}

// Destructor: Currently empty, no specific cleanup needed
autoPOT::~autoPOT() {}

// Sets the callback function and hooks up the object
void autoPOT::setCallback(void(*funct)(int)) {
	callback = funct;		// Store the callback function
	hookup();				// Call hookup() (likely from parent class)
}

// Returns the average  shot of multiple potentiometer readings.
int autoPOT::quickAverage(int numSamples) {
	long sum = 0;
	for (int i = 0; i < numSamples; i++) {
		sum += analogRead(pinNum);			// Sum up the readings
	}
	return sum / numSamples;				// Return the average
}

// Idle function: Checks for potentiometer changes
void autoPOT::idle() {
	int newVal;
	if (callback) {
		newVal = analogRead(pinNum);			// Read the current potentiometer value
		if (newVal != value) {					// If the value has changed
			value = newVal;						// Update the stored value
			callback(value);						// Call the callback function with new value
		}
	}
}