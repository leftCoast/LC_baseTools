#ifndef autoPOT_h
#define autoPOT_h

#include <idlers.h>

/*
This header file defines the autoPOT class, which is designed to manage a potentiometer in an Arduino project.

Key features:
- Inherits from the idler class for background task management
- Provides a constructor to initialize with an input pin number
- Includes a virtual destructor for proper cleanup
- Allows setting a callback function for potentiometer value changes
- Overrides the idle function for continuous background monitoring
- Offers a quickAverage function to get the average potentiometer reading

Protected members:
- callback: Pointer to the function called when the value changes
- pinNum: Stores the input pin number
- value: Holds the current potentiometer value

This class simplifies potentiometer management by handling background monitoring
and providing callback functionality for value changes.
*/

class autoPOT : public idler {

	public:
				autoPOT(int inPin);
		virtual ~autoPOT();
				void setCallback(void(*funct)(int));
				int quickAverage(int numSamples = 10);
		virtual void idle();
		
	protected:
				void(*callback)(int);
				int pinNum;
				int value;
};

#endif