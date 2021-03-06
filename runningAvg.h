#ifndef runningAvg_h
#define runningAvg_h

class runningAvg {
  
	public:
    			runningAvg(int inNumData);
	virtual	~runningAvg(void);
    
    			float addData(float inData);
    			float getAve(void);
    			float getMax(void);
    			float getMin(void);
    			float getDelta(void);
    			float getStdDev(void);
    			int	getNumValues(void);
    			float getDataItem(int index);
  
  protected:
  
    			int	maxData;     // Total amount allowed.
    			int	numValues;   // The amount we have.
    			int	index;       // Write the next value, here.
    			float	*theValues;  // The array of values.
    			float	mResult;     // Just in case they ask, we'll keep a copy.
};

#endif
