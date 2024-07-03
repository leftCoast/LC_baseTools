#ifndef autoPOT_h
#define autoPOT_h

// Include the idlers library for background task management
#include <idlers.h>

// Define a class named autoPOT that inherits from the idler class
class autoPOT : public idler {
public:
	// Constructor that takes an input pin number
	autoPOT(int inPin);

	// Virtual destructor for proper cleanup
	virtual ~autoPOT();

	// Set a callback function to be called when the potentiometer value changes
	void setCallback(void(*funct)(int));

	// Override the idle function from the idler class
	// This will be called repeatedly in the background
	virtual void idle();

	// Get the average reading from the potentiometer
	// Default to 10 samples if not specified
	int getAverage(int numSamples = 10);

protected:
	// Pointer to the callback function
	void(*callback)(int);

	// Store the input pin number
	int pinNum;

	// Store the current potentiometer value
	int value;
};

#endif