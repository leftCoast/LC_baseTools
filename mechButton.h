#ifndef mechButton_h
#define mechButton_h

#include <idlers.h>
#include <timeObj.h>

/*
 Mechanical button "de-bouncer". Provides three usage methods:

 1. Basic: Call `trueFalse()` in your `loop()` for the current debounced button state.
 2. Intermediate: Set a callback function using `setCallback()`.  Your function will
    be called when the debounced button state changes.
 3. Advanced: Inherit from this class and override `takeAction()`. Your implementation
    will be executed when the button state changes. Remember to call `hookup()` if needed.
*/
class mechButton :  public idler {

  public:
            mechButton(byte inPinNum);
    virtual ~mechButton(void);

            bool    getState(void);				// Read current state.
            bool    trueFalse(void);				// Read current state. (Old, change this.)
            void    setCallback(void(*funct)(void));		// Or use a callback for changed state.
    virtual void    takeAction(void);				// Something for the Pro's to inherit.
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