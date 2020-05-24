#include "runningAvg.h"
#include <stdlib.h>

runningAvg::runningAvg(int inNumData) {
  
  theValues = (float*) malloc(sizeof(float)*inNumData);
  maxData = inNumData;
  numValues = 0;
  index = 0;
  result = 0;
}

 
runningAvg::~runningAvg(void) {
  
  free(theValues);
  theValues = NULL;
}


float runningAvg::addData(float inData) {
  
  float sum;
  
  if (numValues<maxData) {          // Early stages while filling.
    theValues[index++] = inData;    // Never been full so index must be ok.
    numValues++;
  } else {
    if (index==maxData) {           // Meaning its pointing past the array.
      index = 0;                    // Cycle around.
    }
    theValues[index++] = inData;    // And stuff the value in.
  }
  sum = 0;
  for (int i=0;i<numValues;i++) {   // We loop up to numValues but not including numValues.
    sum = sum + theValues[i];
  }
  result = sum/numValues;
  return result;
}


float runningAvg::getAve(void) { return result; }


float runningAvg::getMax(void) {
  
  float result = theValues[0];
  
  for (int i=1;i<maxData;i++) {
    if (theValues[i]>result) {
      result = theValues[i];
    }
  }
  return result;
}


float runningAvg::getMin(void) {
  
  float result = theValues[0];
  
  for (int i=1;i<maxData;i++) {
    if (theValues[i]<result) {
      result = theValues[i];
    }
  }
  return result;
}


float runningAvg::getDelta(void) { return getMax()-getMin(); }
