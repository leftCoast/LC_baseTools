#include <ringIndex.h>

ringIndex::ringIndex(int inNumItems) {
	
	numItems = inNumItems;
	head		= 0;
	tail		= 0;
}


ringIndex::~ringIndex(void) {  }

	
int ringIndex::addItem(void) {
	
	int	outIndex;
	
	if (!full()) {
		outIndex = tail;
		increment(tail);
	} else {
		outIndex = INDEX_ERR;
	}
	return outIndex;
}


int ringIndex::peekItem(int index) {

	int	outIndex;
	
	if (empty())			return INDEX_ERR;
	if (index>=numItems) return INDEX_ERR;
	outIndex = head;
	while(index) {
		increment(outIndex);
		index--;
	}
	return outIndex;	
}


int ringIndex::readItem(void) {

	int	outIndex;
	
	if (!empty()) {
		outIndex = head;
		increment(head);
	} else {
		outIndex = INDEX_ERR;
	}
	return outIndex;
}


bool ringIndex::empty(void) { return head == tail; }


bool ringIndex::full(void) {

	int	anIndex;
	
	anIndex = head;
	increment(anIndex);
	return anIndex == tail;
}


int ringIndex::itemCount(void) {
	
	if (empty()) return 0;
	if (full()) return numItems;
	if (tail>head) return tail - head;
 	return numItems - (head - tail);
}


int ringIndex::maxItems(void) { return numItems; }


void ringIndex::flushItems(void) { head = tail; }


int ringIndex::increment(int inIndex) {

			inIndex++;
			if (inIndex>=numItems) inIndex=0;
			return inIndex;
}	
				
				