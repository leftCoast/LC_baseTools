#ifndef ringIndex_h
#define ringIndex_h

// This does the math and accounting of a ring buffer (Queue) of items. Basically you
// inherit this and use it's call to calculate the indexes (head and tail) of where to
// store items and where to read them from.
//
// Example : Lets say you create a ring buffer of text. To store a char in this buffer,
// you use addItem(). First you can check if your buffer is full, and if not?
//
// buffer[addItem()] = aChar;
//
// addItem() returns the index into your buffer to store the char. Then updates the
// indexes for the next call. readItem() works the same way.

#define INDEX_ERR	-1


class ringIndex {

	public:
				ringIndex(int inNumItems);
	virtual	~ringIndex(void);
	
	virtual	int	addItem(void);				// Write to this index, if not INDEX_ERR.
	virtual	int	readItem(void);			// Read at this index, if not INDEX_ERR.
	virtual	bool	empty(void);				// Are we empty?
	virtual	bool	full(void);					// Are we full?
	virtual	int	itemCount(void);			// How many items do we have?
	virtual	int	maxItems(void);			// How many items can we store?
	virtual	void	flushItems(void);			// Reset to zero items.
				
	protected:
	
	virtual	int	increment(int inIndex);	// Increment a pointer. Head or tail, temp?
			
				int 	numItems;
				int	head;
				int	tail;
};

#endif