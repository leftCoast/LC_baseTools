#include "mapper.h"

mapper::mapper(void) { setValues(0,1,0,1); }


mapper::mapper(double x1,double x2,double y1,double y2) {

  setValues(x1,x2,y1,y2);
}


mapper::~mapper(void) {  }


void mapper::setValues(double x1,double x2,double y1,double y2) {
  maxX = max(x1,x2);
  minX = min(x1,x2);
  slope = (y1-y2)/(x1-x2);
  intercept = y1 - slope*x1;
}


double mapper::getSlope(void) { 
  return slope; 
}


double mapper::getMinX(void) { 
  return minX; 
}


double mapper::getMaxX(void) { 
  return maxX; 
}


double mapper::getIntercept(void) { 
  return intercept; 
}

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

double mapper::Map(double inNum) {

  if (inNum < minX)
    inNum = minX;
  else if (inNum > maxX)
    inNum = maxX;
  return(slope*inNum+intercept);
}
