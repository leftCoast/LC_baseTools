#ifndef multiMap_h
#define multiMap_h


#include <lists.h>
#include <mapper.h>

//****************************************************************************************
// multiMap..
//
// Sometimes your data doesn't actually fit very well on a straight line. Its..
// Non-linier. multiMap is a really fast and easy way to get "good enough" data fitting to
// a non-linier data set.
//
// Theory :
// Image you have a data set that is not a line, but kinda' a bow shape. Mapping
// from endpoint to endpoint is fine near the endpoints, but in the middle? The error is
// just too great. What you do is locate, as well as possible, the point of the largest
// error. At that point, calculate the actual correct answer. (X,Y) Now, adding that
// point into your function, breaks your data fitting into two lines. This should fit
// "better" together than your one line before. If you still have places that have too
// large of an error, repeat the process 'till the multiple line segments all fit "good
// enough". To your curve.
//
// And how to achieve this here?
// Start by creating an empty multiMap object. In fact that's all you can start with. Now
// add the end points using : addPoint(X,Y); Where x is your "inputted reading" and y is
// what it should map to. Now you have a linier mapper. Need to add more points to fit it
// better to the curve? Easy! Calcualte the points you need and add them the same way
// using addPoint(X,Y); Doesn't matter what order you add points. The code will sort them
// out for you. Once you have added enough points to make a good enough fit. You can use
// the map() method to map your results from your inputeded data.
//****************************************************************************************



//****************************************************************************************
// mapPoint : You don't interact with this object. Its used by multiMap. If you mess with
// it, it'll probably just bite you. And no one's going to say they're sorry.
//****************************************************************************************


class mapPoint :   public linkListObj {

   public :
            mapPoint(double inX, double inY);
   virtual  ~mapPoint(void);

            mapPoint*   getNext(void);
            void        createUpMappers(void);
   virtual  bool        isGreaterThan(linkListObj* compPoint); // Are we greater than the obj being passed in? Primary sorting function.
   virtual  bool        isLessThan(linkListObj* compPoint);    // Are we less than the obj being passed in? Primary sorting function.
            double      map(double inX);
            double      integrate(double x1,double x2);
   private:
            double   mX;
            double   mY;
            mapper*  mUpMapper;
};



//****************************************************************************************
// multiMap : This is the one you should be using. You can create multiMaps. Add points to
// them. Clear points from them. Map stuff using them and, actually.. Integrate curves
// using them. Its basically a list of mappers and a mapper can actually do integration so
// it was tossed in. Very handy for calculating things liike trapezoidal moves on the fly.
//****************************************************************************************


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
