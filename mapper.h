#ifndef mapper_h
#define mapper_h

#include <Arduino.h>

/*
  @file mapper.h

  @brief This file defines the `mapper` class, which provides linear mapping
  and interpolation functionality for double-precision floating-point values.

  The standard Arduino `map()` function only operates on integers, which
  can lead to precision loss. This class addresses that by performing
  calculations using doubles, maintaining accuracy for real-number applications.

  Additionally, the `mapper` class offers:
   - Integration capabilities for applications like trapezoidal motion profiles.
   - Convenient access to linear equation parameters (slope, intercept, etc.).
 */

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

    private:
                double minX;
                double maxX;
                double slope;
                double intercept;
};

#endif
