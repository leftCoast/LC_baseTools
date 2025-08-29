#ifndef ringIndex_h
#define ringIndex_h

// WORK IN PROGRESS!!
// Setup so that head gets INDEX_ERR when buffer is full.
// Or not..

#define INDEX_ERR	-1


class ringIndex {

	public:
				ringIndex(int inNumItems);
	virtual	~ringIndex(void);
	
				int	addItem(void);
				int	peekItem(int index=0);
				int	readItem(void);
				bool	empty(void);
				bool	full(void);
				int	itemCount(void);
				int	maxItems(void);
				void	flushItems(void);
				
	private:
				int	increment(int inIndex);
				
				int 	numItems;
				int	head;
				int	tail;
};

#endif