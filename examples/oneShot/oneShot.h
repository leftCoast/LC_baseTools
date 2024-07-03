#ifndef oneShot_h
#define oneShot_h

#include <timeObj.h>
#include <idlers.h>
#include <mechButton.h>

// An example of a one-shot class.
//
// Basically what many people want to do is catch a button press then send out a
// one shot timed pulse on an output pin. This is what this class does..
//
// The input paramiters for the one shot class.
//
// oneShot(int inPin,float shotTime,int outPin=13,bool outHiLow=true);
//    inPin    -  The button need to be hooked between this pin and ground.
//                This pin will be setup ising INPUT_PULLUP.
//    shotTime -  The time in miliseconds that the output pin will be toggled.
//                Can be set to fractions of a milisecond,
//    outPin   -  The pin that will be toggled when the button is pressed.
//    outHiLow -  The state of the output pin when triggered.
//                (true) low-high, (false) high-low.
//


class oneShot :   timeObj,
                  public idler {

   public:
                  oneShot(int inPin,float shotTime,int outPin=13,bool outHiLow=true);
   virtual        ~oneShot(void);

            void  begin(void);
   virtual  void  idle(void);

   protected:
            enum   oneShotStates  { preStart, running, waitForRelease };

            oneShotStates  mOurState;
            mechButton*    mButton;
            int            mOutPin;
            bool           mOutHiLow;
};

#endif
