#include "runningAvg.h"
#include <stdlib.h>
#include <resizeBuff.h>


// Constructor, runningAvg wants to know how many data values to average over.
runningAvg::runningAvg(int inNumData) {

	theValues   = NULL;
	maxData		= 0;
	if (resizeBuff(sizeof(float)*inNumData,(byte**)&theValues)) {
		maxData     = inNumData;
	}
	numValues   = 0;
	index       = 0;
	mResult     = 0;
	
	usingUpper	= false;
	upperLimit  = 0;
	usingLower	= false;
	lowerLimit  = 0;
}


// Destructor, this recycles the data buffer.
runningAvg::~runningAvg(void) { resizeBuff(0,(byte**)&theValues); }


// The standard call. Drop in a value, pop out the average of the last n values.
float runningAvg::addData(float inData) {

	float sum;
	
	if (usingLower && inData<lowerLimit) return mResult;		// Limit fail, bail.
	if (usingUpper && inData>upperLimit) return mResult;		// Limit fail, bail.
	
	latestValue = inData;						// Limits passed, this is our latest value.
	if (numValues<maxData) {         		// Early stages while still filling.
		theValues[index++] = inData;			// Never been full so index must be ok.
		oldestValue = theValues[0];			// In this case, oldest is the first of the array.
		numValues++;								//
	} else {											// Else the array is full.
		if (index>=maxData) {					// Meaning its pointing past the array.
			index = 0;								// Cycle around.
		}												//
		theValues[index++] = inData;			// And stuff the value in.
		if (index==maxData) {					// If it's NOW pointing past the array..
			oldestValue = theValues[0];		// Then oldest is the first of the array.
		} else {										// Else..
			oldestValue = theValues[index];	// Oldest value is the next to be crunched.	
		}												//
	}													//
	sum = 0;											// Clear sum.
	for (int i=0;i<numValues;i++) {			// We loop up to numValues but not including numValues.
		sum = sum + theValues[i];
	}
	mResult = sum/numValues;
	return mResult;
}


// This returns the current average that is stored since the last data point was added.
float runningAvg::getAve(void) { return mResult; }


// Run through the data values and return the largest one.
float runningAvg::getMax(void) {

  float max = theValues[0];

  for (int i=1;i<numValues;i++) {
    if (theValues[i]>max) {
      max = theValues[i];
      }
    }
  return max;
}


// Run through the data values and return the smallest one.
float runningAvg::getMin(void) {

  float min = theValues[0];

  for (int i=1;i<numValues;i++) {
    if (theValues[i]<min) {
      min = theValues[i];
    }
  }
  return min;
}


// Runs through the data, actually two times, then gives the difference between the
// largest and the smallest. Basically an absolute value of delata.
float runningAvg::getDelta(void) { return getMax()-getMin(); }


// Only looks at the first and last data ponts. Gives back latest - oldest to give a 
// signed trend overall.
float runningAvg::getEndpointDelta(void) { return(latestValue - oldestValue); }


// Runs through the data, calculates and returns the standard deviation.
float runningAvg::getStdDev(void) {

  float sum;

  sum = 0;
  for (int i=0;i<numValues;i++) {
    sum = sum + pow(theValues[i]-mResult,2);
  }
  sum = sum/numValues;
  return sqrt(sum);
}


// Returns the actual number of data items stored in the data.
int runningAvg::getNumValues(void) { return numValues; }


// Finds the nth data value from 0..numValues-1 and returns that value. Returns zero if it
// can't find the data item.
float runningAvg::getDataItem(int index) {

  if (index>=0 && index < numValues) {
    return theValues[index];
  }
  return 0;
}


// Anything above this will be cut from the data.
void runningAvg::setUpperLimit(float limit) {
		
	upperLimit = limit;
	usingUpper = true;
}


// Turn off the upper limiting.
void runningAvg::clearUpperLimit(void) { usingUpper = false; }


// Anything below this will be cut from the data.
void runningAvg::setLowerLimit(float limit) {
	
	lowerLimit = limit;
	usingLower = true;
}


// Turn off the lower limiting.
void runningAvg::clearLowerLimit(void) { usingLower = false; }


// Set  both upper and lower limits.
void runningAvg::setLimits(float lowerLimit,float upperLimit) {

	setLowerLimit(lowerLimit);
	setUpperLimit(upperLimit);
}


// Shut down all limiting.
void runningAvg::clearLimits(void) {

	clearUpperLimit();
	clearLowerLimit();
}
