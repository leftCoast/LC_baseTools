#ifndef mapper_h
#define mapper_h

#include <Arduino.h>

//****************************************************************************************
// The mapper supplied by the Arduino library is only for integers. Well, sometimes you
// want to do your math in real numbers. So, hang the cost, we're doing this on in the
// biggest real numbers the platform can hand out.
// As it turns out, most of our time is spent talking out different com ports so no one
// notices these calculations. Or at least not often. And its really nice to know you're
// not just chopping off all the decimal places early on in the game.
//
// 6/15/2020 : Added integration. Wanted it for doing trapezoidal moves.
// 6/19/2020 : Backed out the multiMap changes. So for now? We'll see.
// 11/4/2021 : Looks to me like they are back in. It's run for a year. Maybe it's ok.
// 1/14/2022 : Doing some check over and comment cleanup for the next LC_baseTools release.
//****************************************************************************************

class mapper {

    public:
                mapper(void);
                mapper(double x1,double x2,double y1,double y2);
    virtual    ~mapper(void);

                double  map(double inNum);

                // This stuff is for using the mapper as a liner calculator.
                void    setValues(double x1,double x2,double y1,double y2);

                double  getSlope(void);
                double  getMinX(void);
                double  getMaxX(void);
                double  getIntercept(void);

                double  integrate(double x1,double x2);
                double  integrate(void);

                //void   printMap(void);                   // For debugging.
    private:
                double minX;
                double maxX;
                double slope;
                double intercept;
};

#endif
