#ifndef runningAvg_h
#define runningAvg_h



//****************************************************************************************
// runningAvg:
//
// Running average is typically used as a data smoother. Read a data value, stuff it in
// the queue and pull out the resulting average of the last n values. Simple to use, does
// the job.
//
// So we have all this data in the queue. Sometimes we would like to know more than the
// average. How about the min and max values in this set? The spread of the data? Or how
// about the standard deviation? Well, all these other bits are actually available to you
// as well, if really you want to see them.
//
// 2/25/2023 : First pass at adding optional input data limiting. Basically if you have
// upper and lower limits for dropping outliers, you can enter them with the set limit
// method functions. Clear them out with the clear limit methods.
//
// Turning limiting on, off or changing the values, only changes incoming data. You will
// need to run the old data out to get accurate calculations.
//
// 4/5/2025 : Added getEndpointDelta() using the new oldest and latest values.
//
//****************************************************************************************

class runningAvg {

	public:
				runningAvg(int inNumData);
	virtual	~runningAvg(void);

				float addData(float inData);		// Drop in number, receive average.
				
				float getAve(void);					// All the other things no one will ever use.
				float getMax(void);
				float getMin(void);
				float getDelta(void);				// Delta value over all data points.
				float getEndpointDelta(void);		// Delta value reading only first and last.
				float getStdDev(void);
				int getNumValues(void);
				float getDataItem(int index);
				
				void	setUpperLimit(float limit);
				void	clearUpperLimit(void);
				void	setLowerLimit(float limit);
				void	clearLowerLimit(void);
				void setLimits(float lowerLimit,float upperLimit);
				void clearLimits(void);
	
	protected:

				int		maxData;                           // Total amount allowed.
				int		numValues;                         // The amount we have.
				int		index;                             // Write the next value, here.
				float*	theValues;                         // The array of values.
				float		oldestValue;								
				float		latestValue;
				float		mResult;                           // Just in case they ask, we'll keep a copy.
				
				bool		usingUpper;
				float		upperLimit;
				bool		usingLower;
				float		lowerLimit;   
};

#endif
