#ifndef runningAvg_h
#define runningAvg_h


//****************************************************************************************
// runningAvg:
//
// Running average is typically used as a data smoother. Read a data value, stuff it in
// the queue and pull out the resulting average of the last n values. Sime to use, does
// the job.
//
// So we have all this data in the queue. Sometimes we would like to know more than the
// average. How about the min and max values in this set? The spread of the data? Or how
// about the standard deviation? Well, all these other bits are actually available to you
// as well, if really you want to see them.
//****************************************************************************************

class runningAvg {
  
	public:
    			runningAvg(int inNumData);
	virtual	   ~runningAvg(void);
    
    			float addData(float inData);	     // Drop in number, receive average.
    			     
    			float getAve(void);				     // ALl the other things no one will ever use.
    			float getMax(void);
    			float getMin(void);
    			float getDelta(void);
    			float getStdDev(void);
    			int	getNumValues(void);
    			float getDataItem(int index);
  
  protected:
  
    			int		maxData;			         // Total amount allowed.
    			int		numValues;		             // The amount we have.
    			int		index;			             // Write the next value, here.
    			float*	theValues;		             // The array of values.
    			float   mResult;			         // Just in case they ask, we'll keep a copy.
};

#endif
