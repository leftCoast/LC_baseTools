#ifndef multiMap_h
#define multiMap_h


#include <lists.h>
#include <mapper.h>

/*=====================================================================================
 multiMap : Maps input values to output values using piecewise linear interpolation.

 This class allows you to represent non-linear relationships between data points
 by defining a series of line segments connecting them.

 Usage:
 1. Create an empty multiMap object.
 2. Add data points using the `addPoint(x, y)` method,
	 where `x` is the input value and `y` is the corresponding output value.
 3. Use the `map(inputValue)` method to obtain the interpolated output value
	 for a given input.

 Example:

	multiMap myMap;
	myMap.addPoint(0.0, 0.0); // First point
	myMap.addPoint(1.0, 0.5);
	myMap.addPoint(2.0, 1.0); // Last point

	double output = myMap.map(1.5); // output will be 0.75

 Note: The order of points added does not matter; the code sorts them internally.
========================================================================================*/


/*========================================================================================
 mapPoint : You don't interact with this object. Its used by multiMap. If you mess with
 it, it'll probably just bite you. And no one's going to say they're sorry.
========================================================================================*/


class mapPoint :   public linkListObj {

	public :
				mapPoint(double inX, double inY);
	virtual  ~mapPoint(void);

				mapPoint*   getNext(void);
				void        createUpMappers(void);
	virtual  bool        isGreaterThan(linkListObj* compPoint)		// Are we greater than the obj being passed in? Primary sorting function.
	virtual  bool        isLessThan(linkListObj* compPoint);			// Are we less than the obj being passed in? Primary sorting function.
				double      map(double inX);
				double      integrate(double x1,double x2);
	private:
				double   mX;
				double   mY;
				mapper*  mUpMapper;
};



/*============================================================================================
 multiMap : This is the one you should be using. You can create multiMaps. Add points to
 them. Clear points from them. Map stuff using them and, actually.. Integrate curves
 using them. Its basically a list of mappers and a mapper can actually do integration so
 it was tossed in. Very handy for calculating things like trapezoidal moves on the fly.
=================================================================================================*/


class multiMap :  public linkList {

	public:

				multiMap(void);
	virtual  ~multiMap(void);

				void        addPoint(double x, double y);
				void        clearMap(void);
				double      map(double inVal);
				double      Map(double inVal);
				double      integrate(double x1,double x2);

	private:
				mapPoint*   getFirst();
				bool        setUp(void);

				bool  mReady;
};

#endif