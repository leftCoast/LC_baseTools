#include <ringIndex.h>

ringIndex::ringIndex(int inNumItems) {
	
	numItems = inNumItems;
	head		= 0;
	tail		= 0;
}


ringIndex::~ringIndex(void) {  }


// Write to this index, if not INDEX_ERR.	
int ringIndex::addItem(void) {
	
	int	outIndex;
	
	outIndex = INDEX_ERR;
	if (!full()) {
		outIndex = head;
		head = increment(head);
	}
	return outIndex;
}


// Read at this index, if not INDEX_ERR.
int ringIndex::readItem(void) {

	int	outIndex;
	
	outIndex = INDEX_ERR;
	if (!empty()) {
		outIndex = tail;
		tail = increment(tail);
	}
	return outIndex;
}


// Are we empty?
bool ringIndex::empty(void) { return head == tail; }


// Are we full?
bool ringIndex::full(void) {

	int	anIndex;
	
	anIndex = head;
	anIndex = increment(anIndex);
	return anIndex == tail;
}


// How many items do we have?
int ringIndex::itemCount(void) {
	
	if (empty()) return 0;
	if (full()) return maxItems();
	if (head>tail) return head - tail;
 	return numItems - tail + head;
}


// How many items can we store?
int ringIndex::maxItems(void) { return numItems-1; }


// Reset to zero zero.
void ringIndex::flushItems(void) {

	head = 0;
	tail = 0;
}


// Increment a pointer. Head or tail.
int ringIndex::increment(int inIndex) {

	inIndex++;
	if (inIndex>=numItems) {
		inIndex=0;
	}
	return inIndex;
}	
				
				