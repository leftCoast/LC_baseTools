#include <lists.h>



//****************************************************************************************
// linkListObj : A none too bright node with a tail.
//****************************************************************************************


linkListObj::linkListObj(void) { next = NULL; }


/*  	Bit of trouble here. We are single linked, so we
		have no idea who's pointing to us. Therefore we must
		trust whomever is killing us off to take care of
		unlinking us from our list before calling delete.
 */
linkListObj::~linkListObj(void) { }


// We're given a pointer to one of our instances and told to link in after this guy.
// We can do that.
void linkListObj::linkAfter(linkListObj* anObj) {

	if (anObj) {							// Little sanity, don't link to NULL pointer.
		next = anObj->next;			// We point at what they are pointing at.
		anObj->next = this;			// They now point to us.
	}
}


// We're given a pointer to one of our instances and told to link up at the end of his
// tail. We can do that too.
void linkListObj::linkToEnd(linkListObj* anObj) {

	if (anObj) {									// If they're handing us NULL pointers, this is not our problem.
		while(anObj->next!=NULL) {			// There's more?!
			anObj = anObj->next;				// jump over to the next one!
		}											// We should be sitting on the last one now..
	anObj->next = this;							// link in!
	}
}


// There are times when its nice to just ask.
linkListObj* linkListObj::getNext(void) { return next; }


// Lets point somewhere else..
void linkListObj::setNext(linkListObj* ptr) { next = ptr; }


// Call delete on everyone hooked to us.
void linkListObj::deleteTail(void) {

	linkListObj*    temp;

	while (next) {
		temp = next;
		next = temp->next;
		delete(temp);
	}
}

/*
		If you plan on sorting, its a good idea to fill out both! Even if one is a just function of the other. ***

		Are we greater than the linkListObj that has been passed in? You fill this out if you
		plan to use the sorting method of linkList.
*/
bool linkListObj::isGreaterThan(linkListObj* compObj) { return false; }


// Are we less than the linkListObj that has been passed in? You fill this out if you
// plan to use the sorting method of linkList.
bool linkListObj::isLessThan(linkListObj* compObj) { return false; }


/*
=======================================================================================
 linkList : your basic linked list. Good base for linked list things, you know.

 When we receive an object to link up. Do we own it? Or are we just tracking other
 people's laundry? Here is what we do. They can pull out the ones they want whenever.
 When we destruct, we'll recycle the rest.
=======================================================================================
*/

// Create a linkList object.
linkList::linkList(void) { theList = NULL; }


// Delete a linkList object.
linkList::~linkList(void) { dumpList(); }


// Add a SINGLE node to the top of our list.
void linkList::addToTop(linkListObj* newObj) {

	if (newObj) {                                  // Sanity. Don't try to access a NULL pointer!
		newObj->setNext(theList);       				// Empty or not, it does the right thing.
		theList = newObj;                       	// And we set our pointer to the newObj. (Its at the top)
	}
}


// Add a node to the end of our linkList object's list.
void linkList::addToEnd(linkListObj* newObj) {

	if (newObj) {															// Sanity, don't try to access a NULL pointer!
		if (theList==NULL) {											// No list huh?
			theList = newObj;											// Set our pointer to the new object.
		} else {															// Else there is some nodes hooked to us..
			newObj->linkToEnd(theList);							// Run along little object, go find your friends and link yourself in.
		}
	}
}


// Unlink the SINGLE node pointed to by theList. This one trusts you to keep track of the
// old top we are unlinking. It DOES NOT DELETE IT. Don't loose it!
void linkList::unlinkTop(void) {

	linkListObj* temp;

	if (theList) {                                       // if we have something there.
		temp = theList;                                  // Save off the top, just in case.
		theList = theList->getNext();                    // unlink.
		temp->setNext(NULL);                             // They may want to reuse this. So reset next to NULL.
	}
}


// Unlink the SINGLE node pointed to by oldObj. This does NOT delete the object, just
// finds and unlinks it for you. Better not loose it!
void linkList::unlinkObj(linkListObj* oldObj) {

	linkListObj* temp;

	if (oldObj) {                                                          // If they didn't hand us a NULL pointer. (The'll try that just to keep us on your toes.)
		if(theList==oldObj) {                                              // If we're already pointing at it.
			unlinkTop();                                                   // Unlink. (Takes care of resetting next to NULL.)
		}  else {                                                          // Else, we ain't pointing at it..
			temp = theList;                                                // We're going to have to go look for it.
			while(temp->getNext()!=oldObj && temp->getNext()!=NULL) {      // While the next node is not what we are looking for and we ain't run out.
					temp = temp->getNext();                                    // Jump to the next node.
			}                                                                                                                   //
			if (temp->getNext()==oldObj) {                                 // If the next node IS what we were looking for.
					temp->setNext(oldObj->getNext());                          // Unlink it.
					oldObj->setNext(NULL);                                     // Cap it off for possible reuse.
			}
		}
	}
}


// Calls delete on all the object of the list.
void linkList::dumpList(void) {

	linkListObj*    trace;

	while(theList) {            // While we still have something in the list.
		trace = getFirst();     // Point at the top of the list.
		unlinkTop();            // Unlink the top.
		delete(trace);          // Delete the old top.
	}
}


// We got any nodes at all?
bool linkList::isEmpty(void) { return(theList == NULL); }


// Pass back a pointer to our first node.
linkListObj* linkList::getFirst(void) { return theList; }


// Pass back a pointer to our last node.
linkListObj*  linkList::getLast(void) {

	linkListObj*    trace;

	trace = theList;                        // Point at the top of the list.
	if(trace) {                             // If we don't have a NULL.. (Not empty)
		while(trace->getNext()) {           // While there are still nodes in our tail.
			trace = trace->getNext();       // Jump to the next node.
		}                                   //
	}                                       //
	return trace;                           // In all cases, this ends up as what they were looking for.
}


// How many nodes we got?
int linkList::getCount(void) {

	linkListObj*    trace;
	int             count;

	count = 0;                          // Initialize the counter.
	trace = theList;                    // Point at the top of the list. Or NULL of no list..
	while(trace) {                      // While we are not pointing to NULL..
		count++;                        // Bump up the counter
		trace = trace->getNext();       // Jump to the next node.
	}                                   //
	return count;                       // return the resul. Easy peasy.
}


// And there are times it would be nice to grab one by index. Like an array. Returns NULL
// if not found.
linkListObj* linkList::getByIndex(int index) {

	linkListObj*    trace;

	if (index>=0) {                     // Sanity, may be a Bozo calling.
		trace = theList;                // Point at the top of the list. Or NULL of no list..
		while(trace && index) {         // While we're not pointing at NULL and index is > zero..
			trace = trace->getNext();   // We jump to the next node.
			index--;                    // And count backwards.
		}                               //
		return trace;                   // Either we ran out of nodes or the index when to zero. Any way trace is the correct result.
	}                                   //
	return NULL;                        // Negatives get returned a NILL. (Was a Bozo calling?)
}


// Can this node be found? If so, what is its current index in the list? (-1 means not found)
int linkList::findIndex(linkListObj* anObj) {

	linkListObj*    trace;
	int             index;

	if (anObj) {                                // Sanity, did they give us a valid pointer?
		trace = theList;                        // Point at the top.
		index = 0;                              // Initialize the counter.
		while(trace && trace!=anObj) {          // While we're not pointing at NULL. And not pointing at the node we're looking for..
			trace = trace->getNext();           // We jump to the next node.
			index++;                            // And we bump up the counter.
		}                                       //
		if (trace) {                            // Loop has exited. If we are not pointing to NULL, we found it.
			return index;                       // Return its index.
		}                                       //
	}                                           //
	return -1;                                  // In all other cases, return -1 as "Not found".
}


// Using the superclass's isGreaterThan() method, find the largest node on our list.
linkListObj* linkList::findMax(linkListObj* anObj) {

	linkListObj*    trace;
	linkListObj*    maxNode;

	maxNode = anObj;                                    // We start here as the largest.
	trace = anObj;                                      // We start here in our search.
	while(trace) {                                      // While we're not pointing at NULL..
		if (trace->isGreaterThan(maxNode)) {            // If what we are pointing at is larger than the largest..
			maxNode = trace;                            // Select what we are pointing at as largest.
		}                                               //
		trace = trace->getNext();                       // Jump to the next node.
	}                                                   //
	return maxNode;                                     // Return the resulting largest node.
}


// Using the superclass's isLessThan() method, find the smallest node on our list.
linkListObj* linkList::findMin(linkListObj* anObj) {

	linkListObj*    trace;
	linkListObj*    minNode;

	minNode = anObj;                                // We start here as the smallest.
	trace = anObj;                                  // We start here in our search.
	while(trace) {                                  // While we're not pointing at NULL.
		if (trace->isLessThan(minNode)) {           // If what we are pointing at is smaller than the smallest.
			minNode = trace;                        // Select what we are pointing at as smallest.
		}                                           //
		trace = trace->getNext();                   // Jump to the next node.
	}                                               //
	return minNode;                                 // Return the resulting smallest node.
}


// If the superclass has filled out the isGreaterThan() and isLessThan() methods. This
// will sort your list for you.
void linkList::sort(bool ascending) {

	linkListObj*    sorted;
	linkListObj*    maxMin;

	sorted = NULL;                          // Initialize the new list pointer.
	while(!isEmpty()) {                     // While we have nodes in our list.
		if (ascending) {                    // If smallest to largest.
			maxMin = findMax(theList);      // Find the largest node in our list.
		} else {                            // Else, largest to smallest.
			maxMin = findMin(theList);      // Find the smallest node in our list.
		}                                   //
		if (maxMin) {                       // If we have a found node.
			unlinkObj(maxMin);              // Unlink it.
			maxMin->setNext(sorted);        // Point this node to the top of the sorted list.
			sorted = maxMin;                // Point the sorted list at this node. (We're hand linking a sorted list here)
		}                                   //
	}                                       //
	theList = sorted;                       // Point to the sorted list as ours.
}


// Someone has taken control of our list. Just let it go.
void linkList::looseList(void) { theList = NULL; }



/*=============================================================================
 stack : Your basic stack. Mostly pass through with the usual names.
===============================================================================*/


// Create a stack.
stack::stack(void) : linkList() { }


// Delete a stack.
stack::~stack(void) {  }


// Push this node into the stack.
void stack::push(linkListObj* newObj) { addToTop(newObj); }


// Remove and hand back the top of the stack. (YOU have to worry about deleting it.)
linkListObj* stack::pop(void) {

	linkListObj*    topObj;

	topObj = getFirst();
	if (topObj) {
		unlinkTop();
	}
	return topObj;
}


// Hand back the top of the stack without Removing it.
linkListObj* stack::peek(void) { return getFirst(); }



/*================================================================================
		  queue : Your basic queue. Again, mostly pass through with the usual names.
==================================================================================*/


// Create a queue.
queue::queue(void) : linkList() { }


// Delete a queue.
queue::~queue(void) { }


// Push this node into the end of the queue.
void queue::push(linkListObj* newObj) { addToEnd(newObj); }


// Hand back the head of the queue without unlinking it.
linkListObj* queue::peek(void) { return getFirst(); }


// Remove and hand back the head of the queue. (YOU have to worry about deleting it)
linkListObj* queue::pop(void) {

	linkListObj*    topObj;
	topObj = getFirst();
	if (topObj) {
		unlinkTop();
	}
	return topObj;
}



/*=================================================================================
	  dblLinkListObj : This is the base object that "knows" how to link into chains with
	  others like itself.
==================================================================================*/


// Create a double link list node.
dblLinkListObj::dblLinkListObj(void) {

		  dllPrev = NULL;
		  dllNext = NULL;
}


// Delete a double link list node.
dblLinkListObj::~dblLinkListObj(void) { unhook(); }


// Given a pointer to a node, link yourself after it.
void dblLinkListObj::linkAfter(dblLinkListObj* anObj) {

	if (anObj) {                                        // Sanity, If they didn't give us a NULL.
		dllNext = anObj->dllNext;                       // Our next pointer gets their next pointer.
		dllPrev = anObj;                                // Our previous pointer now points back to their node.
		anObj->dllNext = this;                          // Their next pointer now points to us.
		if (dllNext) dllNext->dllPrev = this;           // If our next pointer is NOT NULL. Point what its pointing to's next pointer, at us. (whew, hard to say)
	}
}


// Given a pointer to a node, link yourself before it.
void dblLinkListObj::linkBefore(dblLinkListObj* anObj) {

	if (anObj) {                                        // Sanity, If they didn't give us a NULL.
		dllPrev = anObj->dllPrev;                       // Our previous pointer now points to what their previous pointer points to.
		dllNext = anObj;                                // Our next pointer now points at them, err, their node.
		anObj->dllPrev = this;                          // Their previous pointer now points to us.
		if (dllPrev) dllPrev->dllNext = this;           // If our next previous is NOT NULL. Point what its pointing to's previous pointer, at us.
	}
}


// We are possibly in a list of nodes, find and pass back the head of the list.
dblLinkListObj* dblLinkListObj::getFirst(void) {

	dblLinkListObj* trace;

	trace = this;                   // Point a trace pointer at us.
	while(trace->dllPrev) {         // While trace's previous pointer is not NULL.
		trace = trace->dllPrev;     // Jump to the previous node on the list.
	}                               //
	return trace;                   // Return the result.
}


// We are possibly in a list of nodes, find and pass back the tail end of the list.
dblLinkListObj* dblLinkListObj::getLast(void) {

	dblLinkListObj* trace;

	trace = this;                   // Point a trace pointer at us.
	while(trace->dllNext) {         // While trace's next pointer is not NULL.
		trace = trace->dllNext;     // Jump to the next node on the list.
	}                               //
	return trace;                   // Return the result.
}


// Given a pointer to a node, link yourself after the last in the chain.
void dblLinkListObj::linkToEnd(dblLinkListObj* anObj) { if (anObj) linkAfter(anObj->getLast()); }


// Given a pointer to a node, link yourself before the first in the chain.
void dblLinkListObj::linkToStart(dblLinkListObj* anObj) { if (anObj) linkBefore(anObj->getFirst()); }


// Unlink us and, if in list, patch the hole.
void dblLinkListObj::unhook(void) {

	if (dllPrev) dllPrev->dllNext = dllNext;        // If our previous pointer is not NULL.. Point our previous nodes next pointer, to what our next pointer is point at.
	if (dllNext) dllNext->dllPrev = dllPrev;        // If our next pointer is not NULL.. Point our next nodes previous pointer, to what our previous pointer is point at.
	dllNext = NULL;                                 // Ok, list is patched. Now we pull out. Our next gets NULL
	dllPrev = NULL;                                 // And our previous gets NULL.
}


// Hand back the "nth" one of our tail. Starting at 0. (0 is first of tail, not us.)
// If there is no "nth" pass back NULL.
dblLinkListObj* dblLinkListObj::getTailObj(int index) {

	dblLinkListObj* trace;
	int                 count;

	trace = dllNext;                    // Trace pointer gets our tail.
	count = 0;                          // Initialize counter.
	while(trace&&count<index) {         // While trace is not NULL and the counter is less than the index we're looking for.
		count++;                        // Bump up the counter.
		trace = trace->dllNext;         // Jump to the next node, or NULL if there isn't one.
	}                                   //
	return trace;                       // Pass back the result.
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


// How many nodes long is our tail? (Not counting us)
int dblLinkListObj::countTail(void) {

	dblLinkListObj* trace;
	int                 count;

	trace = dllNext;                // Trace pointer gets our tail.
	count = 0;                      // Initialize counter.
	while(trace) {                  // While trace is not NULL.
		count++;                    // Bump up the counter.
		trace = trace->dllNext;     // Jump to the next node, or NULL if there isn't one.
	}                               //
	return count;                   // Pass back the result.
}


// How many nodes long is our head? (Again, not counting us)
int dblLinkListObj::countHead(void) {

	dblLinkListObj* trace;
	int                 count;

	trace = dllPrev;            // Trace pointer gets our head.
	count = 0;                  // Initialize counter.
	while(trace) {              // While trace is not NULL.
		count++;                // Bump up the counter.
		trace = dllPrev;        // Jump to the previous node, or NULL if there isn't one.
	}                           //
	return count;               // Pass back the result.
}