#ifndef timeObj_h
#define timeObj_h



/*==================================================================================================
 Insanely handy for doing things in the background. Set the timer and wait 'till it goes
 "ding". Great for blinking LEDs, updating readings, etc.
							*** Takes care of roll over issues ***

 NOTE: Once the timer expires, every call to ding() will return true until its been
 reset or restarted.
==================================================================================================*/


class timeObj {

	 public:
					 timeObj(float inMs=10,bool startNow=true);
	 virtual ~timeObj(void);

					 void    setTime(float inMs,bool startNow=true)		// Change the time duration for next start..
	 virtual void    start(void);												// Start the timer "now".
	 virtual void    stepTime(void);											// Restart the timer from last end time.
					 bool    ding(void);											// Timer has expired.
					 float   getTime(void);										// How long does this go for?
					 float   getFraction(void);								// Fuel gauge. What fraction of time is left.
					 void    reset(void);										// Reset to the preStart state.
				//void  printState(void);										// Debugging.

	 private :
					 enum    timeObjStates   { preStart, running, expired };

					 bool            useMilli;
					 timeObjStates   ourState;
					 unsigned long   waitTime;
					 unsigned long   startTime;
					 unsigned long   endTime;
};

#endif

