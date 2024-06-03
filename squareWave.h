#ifndef squareWave_h
#define squareWave_h

#include    "timeObj.h"
#include    "idlers.h"



//****************************************************************************************
// squareWave:
// Square waves are very common in the digital world. Things that blink, blink square
// waves. Motor controllers and lamp dimmers run on square waves. So many things use this
// model that it seemed like a good idea to have a base, theoretical square wave class to
// use as a foundation of all these things we'd like to use them for.
//
// This class begins dormant. You need to explicitly call setOnOff() with a value of true
// to start it running.
//
// NOTE : If you never call setOnOff() you will never be hooked up into the idler queue.
// This in itself is not really an issue. BUT, if you inherit this and you need the idle
// loop no matter what, just call hookup() in something like a begin() method or something.
// Then everything will be fine.
//
// Using an Arduino UNO the pulse width dithers about 20 microseconds.
// Meaning : For a RC servo you get about 2% error.
//
// Using a Teensy 3.2 You get a freq dither of 8 micros & granularity of 5 micros. pulse
// width, within the granularity is around 5 micros.
// Meaning : For an RC servo? Rock solid no measurable error.
//****************************************************************************************


class squareWave : public idler {

	enum waveState { sittinIdle, ridingHi, ridingLow };

	public:
				squareWave(void);
				squareWave(float periodMs,float pulseMs, bool blocking=false);
	virtual	~squareWave(void);

				bool	running(void);
				bool	pulseHiLow(void);
	virtual	void	setPeriod(float ms);
	virtual	void	setPulse(float ms);
	virtual	void	setPercent(float perc);
	virtual	void	setBlocking(bool onOff);
	virtual	void	setOnOff(bool onOff);

	virtual	void	pulseOn(void);
	virtual	void	pulseOff(void);
	virtual	void	idle(void);

				//void  printState(void);                  // For debugging.
	protected:

				void	init(void);
	virtual	void	block(void);
	virtual	void	startWave(void);
				void	ourPulseOn(void);
				void	ourPulseOff(void);

				waveState	mState;
				bool			mSignal;
				timeObj		mPeriod;
				bool			mPeriodChange;
				float			mNextPeriod;
				timeObj		mPulse;
				bool			mPulseChange;
				float			mNextPulse;
				bool			mBlocking;
};

#endif
