#ifndef blinker_h
#define blinker_h

#include <squareWave.h>

// Some defaults in case the user just doesn't care..
#define defPin 13
#define defOnMs 50
#define defPeriodMs 400

class blinker : public squareWave {

public:
            blinker(int inPin=defPin,float inOnMs=defOnMs, float inPeriodMs=defPeriodMs,bool inInverse=false);
    virtual ~blinker(void);

    virtual void    setOnOff(bool onOff);                  // Start or stop the blinking..
            bool    blinking();                            // We blinking or what?
    virtual void    pulseOn(void);
    virtual void    pulseOff(void);

    protected:

        bool    init;
        int      pin;
        bool    inverse;
};

#endif
