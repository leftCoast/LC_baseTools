#ifndef mechButton_h
#define mechButton_h

#include <idlers.h>
#include <timeObj.h>

//****************************************************************************************
// Mechanical button de-bouncer.
// This can be used in one of three ways.
//
// Beginner : Just call getState() in your loop() function and it'll return true or false
// to match what the button is currently set to. Easy Peasy!
//
// Intermediate : Set a callback function and let this run in the background. When the
// button changes state, true or false, your callback function is called. Again, pretty
// simple.
//
// Pro : Inherit this as a base class and let it become the callback you always dreamed
// of. Remember that in this case, you will probably need to put in a call to hookup().
// But then, you're a pro. So I shouldn't have to tell you that.
//****************************************************************************************

class mechButton :  public idler {

  public:
            mechButton(byte inPinNum);
    virtual ~mechButton(void);

            bool    getState(void);								// Read current state.
            bool    trueFalse(void);							// Read current state. (Old, change this.)
            void    setCallback(void(*funct)(void));		// Or use a callback for changed state.
    virtual void    takeAction(void);							// Something for the Pro's to inherit.
    virtual void    idle();

    protected:
                timeObj mTimer;
                bool    beenInitialized;
                void    (*callback)(void);
                byte    pinNum;
                byte    checkNum;
                byte    setAs;
};

#endif

