#include "runningAvg.h"
#include <stdlib.h>
#include <resizeBuff.h>

runningAvg::runningAvg(int inNumData) {
  
	theValues	= NULL;
	resizeBuff(sizeof(float)*inNumData,(byte**)&theValues);
	maxData		= inNumData;
	numValues	= 0;
	index			= 0;
	mResult		= 0;
}

 
runningAvg::~runningAvg(void) { resizeBuff(0,(byte**)&theValues); }


float runningAvg::addData(float inData) {
  
  float sum;
  
	if (numValues<maxData) {          	// Early stages while filling.
		theValues[index++] = inData;	// Never been full so index must be ok.
		numValues++;
	} else {
		if (index==maxData) {				// Meaning its pointing past the array.
			index = 0;							// Cycle around.
		}
		theValues[index++] = inData;	// And stuff the value in.
	}
	sum = 0;
	for (int i=0;i<numValues;i++) {		// We loop up to numValues but not including numValues.
		sum = sum + theValues[i];
	}
	mResult = sum/numValues;
	return mResult;
}


float runningAvg::getAve(void) { return mResult; }


float runningAvg::getMax(void) {
  
	float max = theValues[0];
  
	for (int i=1;i<numValues;i++) {
		if (theValues[i]>max) {
			max = theValues[i];
		}
	}
	return max;
}


float runningAvg::getMin(void) {
  
	float min = theValues[0];
  
	for (int i=1;i<numValues;i++) {
		if (theValues[i]<min) {
			min = theValues[i];
		}
	}
	return min;
}


float runningAvg::getDelta(void) { return getMax()-getMin(); }


float runningAvg::getStdDev(void) {

	float sum;
	
	sum = 0;
	for (int i=0;i<numValues;i++) {
		sum = sum + pow(theValues[i]-mResult,2);
	}
	sum = sum/numValues;
	return sqrt(sum);
}


int runningAvg::getNumValues(void) { return numValues; }


float runningAvg::getDataItem(int index) {

	if (index>=0 && index < numValues) {
		return theValues[index];
	}
	return 0;
}


