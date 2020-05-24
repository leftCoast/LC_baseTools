#ifndef mechButton_h
#define mechButton_h

#include <Arduino.h>

#define NUM_CHECKS  20

// Hook your mechanical push button between a digital pin
// and ground. Pass the pin number into one of these.
// In your loop(), you can call clicked(); (over & over)
// If the button's been clicked and it sees a good solid click, 
// it gives back "true".
//
// This takes care of initialization, filtering & debounce
// for you.


class mechButton {
  
  public:
				mechButton(byte inPinNum);
	virtual	~mechButton(void);
	
    			bool	clicked(void);

	protected:
    			bool  beenInitialized;
    			byte  pinNum;
    			byte  checkNum;
    			byte  setAs;
};

#endif

