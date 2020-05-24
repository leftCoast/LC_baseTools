#ifndef mapper_h
#define mapper_h

#include <Arduino.h>


// The mapper supplied by the Arduino library is only for integers.
// Well, sometimes you want to do your math in real numbers. So hang the cost
// we're doing this on in the biggest real numbers the platform can hand out.
// As it turns out, most of our time is spent talking out different com ports
// so no one notices these calculations. Or at least not often. And its really
// nice to know you're not just chopping off all the decimal places early on
// in the game.

class mapper {
	
	public:
  				mapper(void);
  				mapper(double x1,double x2,double y1,double y2);
	virtual	~mapper(void);

  				double	Map(double inNum);

  				// This stuff is for using the mapper as a liner calculator.
  				void		setValues(double x1,double x2,double y1,double y2);
  				double	getSlope(void);
  				double	getMinX(void);
  				double	getMaxX(void);
  				double	getIntercept(void);
  				//void   printMap(void);      // For debugging.
	private:
  				double minX;
  				double maxX;
  				double slope;
  				double intercept;
};

#endif

