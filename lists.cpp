#include "lists.h"



// *************** linkListObj ********************
// A none too bright node with a tail.

linkListObj::linkListObj(void) {  
  next = NULL; 
}


linkListObj::~linkListObj(void) {

  // Bit of trouble here. We are single linked, so we
  // have no idea who's pointing to us. Therefore we must
  // Trust whomever is killing us off to take care of
  // unlinking us from our list.
}


// We're given a pointer to one of our instances and told to link in after this guy.
// We can do that.
void linkListObj::linkAfter(linkListObj* present) {

  if (present) {              // Little sanity, don't link to NULL pointer.
    next = present->next;
    present->next = this;
  }
}


void linkListObj::linkToEnd(linkListObj* present) {

  if (present) {                      // If they're handing us NULL pointers, this is not our problem.
    while(present->next!=NULL) {      // There's more?!
      present = present->next;        // jump over to the next one!
    }                                 // We should be sitting on the last one now..
    present->next = this;             // link in!
  }
}


// There are times when its nice to just ask.
linkListObj* linkListObj::getNext(void) { return next; }


// Lets point somewhere else..
void linkListObj::setNext(linkListObj* ptr) { next = ptr; }	


// Call delete on everyone hooked to us.
void linkListObj::deleteTail(void) {

	linkListObj*	temp;
	
	while (next) {
		temp = next;
		next = temp->next;
		delete(temp);
	}
}				


// *** If you plan on sorting, its a good idea to fill out both! Even if one is a just function of the other. ***
//
// Are we greater than the linkListObj that has been passed in? You fill this out if you
// plan to use the sorting method of linkList.
bool linkListObj::isGreaterThan(linkListObj* compObj) { return false; }


// Are we less than the linkListObj that has been passed in? You fill this out if you
// plan to use the sorting method of linkList.
bool linkListObj::isLessThan(linkListObj* compObj) { return false; }



//********************* linkList *************************
// your basic linked list. Good base for linked list things, you know.

// When we recieve an object to link up. Do we own it? Or are
// we just tracking other people's laundry? Here is what we do.
// They can pull out the ones they want whenever. We dump the rest.
linkList::linkList(void) { theList = NULL; }


linkList::~linkList(void) { dumpList(); }


void linkList::addToTop(linkListObj* newObj) {

	newObj->setNext(theList);  // Empty or not, it does the right thing.
	theList = newObj;
}


void linkList::addToEnd(linkListObj* newObj) {

  if (theList==NULL) {          // No list huh?
    theList = newObj;
  }  else {
    newObj->linkToEnd(theList);  // Run along little object, go find your friends and link yourself in.
  }
}


// This one trusts you to keep track of the old top we are unlinking.
void linkList::unlinkTop(void) {
	
	if (theList) {								// if we have something there.
		theList = theList->getNext();		// unlink.
	}
}


// This does NOT delete the object, just unlinks it for you.
// Better not loose it!
void linkList::unlinkObj(linkListObj* oldObj) {

  linkListObj* temp;
  
  if (oldObj) {											// They didn't hand us a NULL pointer.
    if(theList==oldObj) {								// Were pointing at it.
      theList = oldObj->getNext();					// unlink..
    }  else {												// We ain't pointing at it..
      temp = theList;									// We're going to have to go look for it.
      while(temp->getNext()!=oldObj && temp->getNext()!=NULL) {
        temp = temp->getNext();
      }
      if (temp->getNext()==oldObj) {				// Found it!
        temp->setNext(oldObj->getNext());			// unlink..
      }
    }
  }     
}


// Calls delete on all the object of the list.
void linkList::dumpList(void) {

	linkListObj*	trace;	// Temp pointer.
	
	while(theList) {			// While we still have something in the list.
		trace = getFirst();	// Point at the top of the list.
		unlinkTop();			// Unlink the top.
		delete(trace);			// Delete the old top.
	}	
}


bool linkList::isEmpty(void) { return(theList == NULL); }


linkListObj* linkList::getFirst(void) { return theList; }


linkListObj*  linkList::getLast(void) {

	linkListObj*	trace;

	trace = theList;
	if(trace) {
		while(trace->getNext()) {
			trace = trace->getNext();
		}
	}
	return trace;
}
	
	
int linkList::getCount(void) {

		linkListObj*	trace;
		long					count;
	
		count = 0;
		trace = theList;
		while(trace) {
			count++;
			trace = trace->getNext();
		}
		return count;
	}
	
	
// And there are times it would be nice to grab one by index.
// Like an array. Returns NULL if not found.
linkListObj* linkList::getByIndex(int index) {

	linkListObj*	trace;
	
	if (index>=0) {							// Sanity, may be a Bozo calling.
		trace = theList;
		while(trace && index) {
			trace = trace->getNext();
			index--;
		}
		return trace;
	}
	return NULL;
}


int linkList::findIndex(linkListObj* present) {

	linkListObj*	trace;
	int				index;
	
	trace = theList;
	index = 0;
	while(trace && trace!=present) {
		trace = trace->getNext();
		index++;
	}
	if (trace) {
		return index;
	} else {
		return -1;
	}
}


linkListObj*	linkList::findMax(linkListObj* present) {

	linkListObj*	trace;
	linkListObj*	maxNode;
	
	maxNode = present;
	trace = present;
	while(trace) {
		if (trace->isGreaterThan(maxNode)) {
			maxNode = trace;
		}
		trace = trace->getNext();
	}
	return maxNode;
}


linkListObj*	linkList::findMin(linkListObj* present) {

	linkListObj*	trace;
	linkListObj*	minNode;
	
	minNode = present;
	trace = present;
	while(trace) {
		if (trace->isLessThan(minNode)) {
			minNode = trace;
		}
		trace = trace->getNext();
	}
	return minNode;
}


// If the virtual isGreaterThan() and isLessThan() methods have been filled out this will
// sort your list for you.
void linkList::sort(bool ascending) {
	
	linkListObj* sorted;
	linkListObj*	maxMin;
	
	sorted = NULL;
	while(!isEmpty()) {
		if (ascending) {
			maxMin = findMax(theList);
		} else {
			maxMin = findMin(theList);
		}
		if (maxMin) {
			unlinkObj(maxMin);
			maxMin->setNext(sorted);
			sorted = maxMin;
		}
	}
	theList = sorted;
}
			

// ********** stack ****************
// Your basic stack. Mostly pass throughs with the usual names.


stack::stack(void) : linkList() { }

stack::~stack(void) {  }

void stack::push(linkListObj* newObj) { addToTop(newObj); }

linkListObj* stack::pop(void) {
	
	linkListObj*	topObj;
	
	topObj = getFirst();
	if (topObj) {
		unlinkTop();
	}
	return topObj;
}		

linkListObj* stack::peek(void) { return getFirst(); }



// ********** queue ****************
// Your basic queue. Mostly pass throughs with the usual names.


queue::queue(void) : linkList() { }

queue::~queue(void) { }

void queue::push(linkListObj* newObj) { addToEnd(newObj); }

linkListObj* queue::peek(void) { return getFirst(); }


linkListObj* queue::pop(void) {
	
	linkListObj*	topObj;
	
	topObj = getFirst();
	if (topObj) {
		unlinkTop();
	}
	return topObj;
}


// ********** double linked list ****************


dblLinkListObj::dblLinkListObj(void) {
    
    dllPrev = NULL;
    dllNext = NULL;
}


dblLinkListObj::~dblLinkListObj(void) { unhook(); }
    

// Given a pointer to a node, link yourself after it.
void dblLinkListObj::linkAfter(dblLinkListObj* present) {
    
    if (present) {
        dllNext = present->dllNext;
        dllPrev = present; 
        present->dllNext = this;
        if (dllNext) dllNext->dllPrev = this;
    }    
}


// Given a pointer to a node, link yourself before it.
void dblLinkListObj::linkBefore(dblLinkListObj* present) {
    
    if (present) {
        dllPrev = present->dllPrev;
        dllNext = present;
        present->dllPrev = this;
        if (dllPrev) dllPrev->dllNext = this;
    }
}


dblLinkListObj* dblLinkListObj::getFirst(void) {
    
    dblLinkListObj* trace = this;
    while(trace->dllPrev) {
        trace = trace->dllPrev;
    }
    return trace;
}


dblLinkListObj* dblLinkListObj::getLast(void) {
    
    dblLinkListObj* trace;
    
    trace = this;
    while(trace->dllNext) {
        trace = trace->dllNext;
    }
    return trace;
}


// Given a pointer to a node, link yourself after the last in the chain.
void dblLinkListObj::linkToEnd(dblLinkListObj* present) { if (present) linkAfter(present->getLast()); }


// Given a pointer to a node, link yourself before the first in the chain.
void dblLinkListObj::linkToStart(dblLinkListObj* present) { if (present) linkBefore(present->getFirst()); }


// Unlink us and, if in list, patch the hole.
void dblLinkListObj::unhook(void) {
    
    if (dllPrev) dllPrev->dllNext = dllNext;
    if (dllNext) dllNext->dllPrev = dllPrev;
    dllNext = NULL;
    dllPrev = NULL;
}


// Hand back the "nth" one of our tail. Starting at 0;
dblLinkListObj* dblLinkListObj::getTailObj(int index) {
	
	dblLinkListObj*	trace;
	int					count;
	
	trace = dllNext;
	count = 0;
	while(trace&&count<index) {
		count++;
		trace = trace->dllNext;
	}
	return trace;
}


// Delete entire tail. delete calls unhook before deleting the object.
void dblLinkListObj::dumpTail(void) { while(dllNext) delete dllNext; }

		
// Delete entire head section. delete calls unhook before deleting the object.					
void dblLinkListObj::dumpHead(void) { while(dllPrev) delete dllPrev; }
	

// Dump both head & tail, leaving ourselves. All alone..
void dblLinkListObj::dumpList(void) {

		dumpHead();
		dumpTail();
}						


// How many nodes long is our tail?
int dblLinkListObj::countTail(void) {

	dblLinkListObj*	trace;
	int					count;
	
	trace = dllNext;
	count = 0;
	while(trace) {
		count++;
		trace = trace->dllNext;
	}
	return count;
}


// How many nodes long is our head?
int dblLinkListObj::countHead(void) {

	dblLinkListObj*	trace;
	int					count;
	
	trace = dllPrev;
	count = 0;
	while(trace) {
		count++;
		trace = dllPrev;
	}
	return count;
}

