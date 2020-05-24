#ifndef PulseOut_h
#define PulseOut_h

#include <Arduino.h>
#include "timeObj.h"
#include "idlers.h"

// ONLY USE THIS FOR TIGHT PULSE TIMING
// IT BLOCKS WHEN THE PULSE IS HIGH.

class PulseOut : public timeObj, public idler {
   
	public:
	
				PulseOut(byte inPin , float inPeriod,bool inverse=false);	// inPeriod in ms
	virtual	~PulseOut(void);
            
            void setWidth(float inWidth);            							// inWidth in ms
	virtual	void idle(void);
   
   private:
   
      		bool				init;
      		byte				pin;
      		unsigned long	width;
	  			bool				pullDown;
};
   
#endif
