#ifndef autoPOT_h
#define autoPOT_h

#include <idlers.h>


//****************************************************************************************
// autoPOT:
// autoPOT is a quick and easy way to get analog readings from the analog port. When the
// reading changes, your callback is called, giving you the new value.
//
// Create an autoPOT instance using the analog input pin number of your choice.
// autoPOT myPOT(A0);
//
// In your setup() function, attach this to your callback function.
// myPOT.setCallback(gotChange);
//
// Write your callback function.
// void gotChange(int newValue) {
//    Do stuff with the newValue
// }
//
// Make sure idle() is called in your main loop() function.
//
// That's about it.
//****************************************************************************************


class autoPOT : public idler {

	public:
				autoPOT(int inPin);
	virtual	~autoPOT(void);

				void  setCallback(void(*funct)(int));
          	void	setWindow(int plusMinus);
	virtual	void  idle(void);
          
  protected:
				void	(*callback)(int);
				int	pinNum;
				int	value;
				int	window;
};

#endif
