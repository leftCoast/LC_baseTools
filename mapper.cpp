#include "mapper.h"


// Basically lets have a blank mapper. We can fill it in later.
mapper::mapper(void) { setValues(0,1,0,1); }


// Create a mapper with start range, mapped range, ready to go.
mapper::mapper(double x1,double x2,double y1,double y2) { setValues(x1,x2,y1,y2); }


// Recycle a mapper.
mapper::~mapper(void) { }


// Setup all the values and do what calculations we can beforhand.
void mapper::setValues(double x1,double x2,double y1,double y2) {

  maxX = max(x1,x2);                                       // I wonder where it's piking up max()?
  minX = min(x1,x2);                                       // Or min() for that matter.
  slope = (y1-y2)/(x1-x2);                                 // Do the slope calculation.
  intercept = y1 - slope*x1;                               // And work out our y intercept.
}

// These next four are pretty much self evident. Return copies of the values we save.
double mapper::getSlope(void) { return slope; }


double mapper::getMinX(void) { return minX; }


double mapper::getMaxX(void) { return maxX; }


double mapper::getIntercept(void) { return intercept; }


// Here is the meat & potatoes working call that we live for. Map a value from x -> y.
// Return the result.
double mapper::map(double inNum) {

  if (inNum < minX)                                        // If inNum is less that our minimum..
    inNum = minX;                                          // We, I? anyway.. We set inNum to the minimum.
  else if (inNum > maxX)                                   // Else, if inNum is greater than maximum..
    inNum = maxX;                                          // Set inNum to the maximum..
  return(slope*inNum+intercept);                           // return the filtered input's calculation.
}


// Integrate over a section of the mapper's range.  x1->x2. Even though the map() function
// calls will constrain the input values, we need to pre-constrain them for doing the
// final calculation.
double mapper::integrate(double x1,double x2) {

    if (x1<minX) x1 = minX;                                // If x1 is less then our minimum, make it our minimum.
    if (x2>maxX) x2 = maxX;                                // If x2 is greater then our maximum, make it our maximum.
    return (((map(x1)+map(x2))/2) * (x2-x1));              // Return the area under our line segment. Avarage height * Dx.
}


// Integrate over the entire mapper's range.
double mapper::integrate(void) { return integrate(minX,maxX); }


/*
void mapper::printMap(void) {

  Serial.print("maxX, minX, slope, intercept : ");
  Serial.print(maxX);
  Serial.print(", ");
  Serial.print(minX);
  Serial.print(", ");
  Serial.print(slope);
  Serial.print(", ");
  Serial.println(intercept);
}
*/
