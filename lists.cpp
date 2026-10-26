#include <lists.h>
//#include <debug.h>


/*
****************************************************************************************
 linkListObj : A none too bright node with a tail.
****************************************************************************************
*/


linkListObj::linkListObj(void) { next = NULL; }
/*
 Bit of trouble here. We are single linked, so we
 have no idea who's pointing to us. Therefore we must
 Trust whomever is killing us off to take care of
 unlinking us from our list.
*/
linkListObj::~linkListObj(void) { }
/*
 We're given a pointer to one of our instances and told to link in after this guy.
 We can do that.
 Little sanity, don't link to NULL pointer.
 We point at what they are pointing at.
 They now point to us.
*/
void linkListObj::linkAfter(linkListObj* anObj) {

   if (anObj) {
      next = anObj->next;
      anObj->next = this;
   }
}
/*
 We're given a pointer to one of our instances and told to link up at the end of his
 tail. We can do that too.
 If they're handing us NULL pointers, this is not our problem.
 There's more?!
 jump over to the next one!
 We should be sitting on the last one now link in!
*/
void linkListObj::linkToEnd(linkListObj* anObj) {

   if (anObj) {
      while(anObj->next!=NULL) {
         anObj = anObj->next;
      }
   anObj->next = this;
   }
}
/*
 There are times when its nice to just ask.
*/
linkListObj* linkListObj::getNext(void) { return next; }
/*
 Lets point somewhere else.
*/
void linkListObj::setNext(linkListObj* ptr) { next = ptr; }
/*
 Call delete on everyone hooked to us.
*/
void linkListObj::deleteTail(void) {

   linkListObj*    temp;

   while (next) {
      temp = next;
      next = temp->next;
      delete(temp);
   }
}
/*
 *** If you sort, it's good to fill out both! If one is a just function of the other. ***

 Are we greater than the linkListObj that has been passed in? You fill this out if you
 plan to use the sorting method of linkList.
*/
bool linkListObj::isGreaterThan(linkListObj* compObj) { return false; }
/*
 Are we less than the linkListObj that has been passed in? You fill this out if you
 plan to use the sorting method of linkList.
*/
bool linkListObj::isLessThan(linkListObj* compObj) { return false; }
/*
****************************************************************************************
 linkList : your basic linked list. Good base for linked list things, you know.

 When we recieve an object to link up. Do we own it? Or are we just tracking other
 people's laundry? Here is what we do. They can pull out the ones they want whenever.
 When we destruct, we'll recycle the rest.
****************************************************************************************

 Create a linkList object.
 Sanity. Don't try to access a NULL pointer!
 Empty or not, it does the right thing.
 And we set our pointer to the newObj. (Its at the top)
*/
linkList::linkList(void) { theList = NULL; }


// Delete a linkList object.
linkList::~linkList(void) { dumpList(); }
/*
 Unlink the SINGLE node pointed to by theList. This one trusts you to keep track of the
 old top we are unlinking. It DOES NOT DELETE IT. Don't loose it!
 if we have something there. theList is NOT NULL.
 Save off the top.
 Move the list pointer to the next node on list.
 They may want to reuse this. So reset next to NULL.
*/
void linkList::addToTop(linkListObj* newObj) {

   if (newObj) {
      newObj->setNext(theList);
      theList = newObj;
   }
}


// Add a node to the end of our linkList object's list.
// Sanity, don't try to access a NULL pointer!
// No list huh?
// Set our pointer to the new object.
// Else there is some nodes hooked to us.
// Run along little object, go find your friends and link yourself in.
void linkList::addToEnd(linkListObj* newObj) {

   if (newObj) {
      if (theList==NULL) {
         theList = newObj;
      } else {
         newObj->linkToEnd(theList);
      }
   }
}


// Unlink the SINGLE node pointed to by theList. This one trusts you to keep track of the
// old top we are unlinking. It DOES NOT DELETE IT. Don't loose it!
// if we have something there. theList is NOT NULL.
// Save off the top.
// Move the list pointer to the next node on list.
// They may want to reuse this. So reset next to NULL.
void linkList::unlinkTop(void) {

   linkListObj* temp;

   if (theList) {
      temp = theList;
      theList = theList->getNext();
      temp->setNext(NULL);
   }
}
/*
 Unlink the SINGLE node pointed to by oldObj. This does NOT delete the object, just
 finds and unlinks it for you. Better not loose it!
 If they didn't hand us a NULL pointer. (The'll try that just to keep us on your toes.)
 If we're already pointing at it.
 Unlink. (Takes care of resetting next to NULL.)
 Else, we ain't pointing at it.
 We're going to have to go look for it.
 While the next node is not what we are looking for and we ain't run out.
 Jump to the next node.
 If the next node IS what we were looking for.
 Unlink it.
 Cap it off for possible reuse.
*/

void linkList::unlinkObj(linkListObj* oldObj) {

   linkListObj* temp;

   if (oldObj) {
      if(theList==oldObj) {
         unlinkTop();
      }  else {
         temp = theList;
         while(temp->getNext()!=oldObj && temp->getNext()!=NULL) {
            temp = temp->getNext();
         }
         if (temp->getNext()==oldObj) {
            temp->setNext(oldObj->getNext());
            oldObj->setNext(NULL);
         }
      }
   }
}
/*
 Calls delete on all the object of the list.
 While we still have something in the list.
 Point at the top of the list.
 Unlink the top.
 Delete the old top.
*/

void linkList::dumpList(void) {

   linkListObj*    trace;

   while(theList) {
      trace = getFirst();
      unlinkTop();
      delete(trace);
   }
}
/*
 We got any nodes at all?
*/
bool linkList::isEmpty(void) { return(theList == NULL); }
/*
 Pass back a pointer to our first node.
*/
linkListObj* linkList::getFirst(void) { return theList; }
/*
 Pass back a pointer to our last node.
 Point at the top of the list.
 If we don't have a NULL. (Not empty)
 While there are still nodes in our tail.
 Jump to the next node.
 In all cases, this ends up as what they were looking for.
*/
linkListObj*  linkList::getLast(void) {

   linkListObj*    trace;

   trace = theList;
   if(trace) {
      while(trace->getNext()) {
         trace = trace->getNext();
      }
   }
   return trace;
}
/*
 How many nodes we got?
 Initialize the counter.
 Point at the top of the list. Or NULL of no list.
 While we are not pointing to NULL.
 Bump up the counter
 Jump to the next node.
 return the resul. Easy peasy.
*/

int linkList::getCount(void) {

   linkListObj*    trace;
   int             count;

   count = 0;
   trace = theList;
   while(trace) {
      count++;
      trace = trace->getNext();
   }
   return count;
}
/*
 And there are times it would be nice to grab one by index. Like an array. Returns NULL
 if not found.
 Sanity, may be a Bozo calling.
 Point at the top of the list. Or NULL of no list.
 While we're not pointing at NULL and index is > zero.
 We jump to the next node.
 And count backwards.
 Either we ran out of nodes or the index when to zero. Any way trace is the correct result.
 Negatives get returned a NULL. (Was a Bozo calling?)
*/
linkListObj* linkList::getByIndex(int index) {

   linkListObj*    trace;

   if (index>=0) {
      trace = theList;
      while(trace && index) {
         trace = trace->getNext();
         index--;
      }
      return trace;
   }
   return NULL;
}

/*
 Can this node be found? If so, what is its current index in the list? (-1 means not found)
 Sanity, did they give us a valid pointer?
 Point at the top.
 Initialize the counter.
 While we're not pointing at NULL. And not pointing at the node we're looking for.
 We jump to the next node.
 And we bump up the counter.
 Loop has exited. If we are not pointing to NULL, we found it.
 Return its index.
 In all other cases, return -1 as "Not found".
*/
int linkList::findIndex(linkListObj* anObj) {

   linkListObj*    trace;
   int             index;

   if (anObj) {
      trace = theList;
      index = 0;
      while(trace && trace!=anObj) {
         trace = trace->getNext();
         index++;
      }
      if (trace) {
         return index;
      }
   }
   return -1;
}

/*
 Using the superclass's isGreaterThan() method, find the largest node on our list.
 We start here as the largest.
 We start here in our search.
 While we're not pointing at NULL.
 If what we are pointing at is larger than the largest.
 Select what we are pointing at as largest.
 Jump to the next node.
 Return the resulting largest node.
*/

linkListObj* linkList::findMax(linkListObj* anObj) {

   linkListObj*   trace;
   linkListObj*   maxNode;

   maxNode = anObj;
   trace = anObj;
   while(trace) {
      if (trace->isGreaterThan(maxNode)) {
         maxNode = trace;
      }
      trace = trace->getNext();
   }
   return maxNode;
}


/*
 Using the superclass's isLessThan() method, find the smallest node on our list.
 We start here as the smallest.
 We start here in our search.
 While we're not pointing at NULL.
 If what we are pointing at is smaller than the smallest.
 Select what we are pointing at as smallest.
 Jump to the next node.
 Return the resulting smallest node.
*/

linkListObj* linkList::findMin(linkListObj* anObj) {

   linkListObj*   trace;
   linkListObj*   minNode;

   minNode = anObj;
   trace = anObj;
   while(trace) {
      if (trace->isLessThan(minNode)) {
         minNode = trace;
      }
      trace = trace->getNext();
   }
   return minNode;
}
/*
 If the superclass has filled out the isGreaterThan() and isLessThan() methods. This
 will sort your list for you.
 Initialize the new list pointer.
 While we have nodes in our list.
 If smallest to largest.
 Find the largest node in our list.
 Else, largest to smallest.
 Find the smallest node in our list.
 If we have a found node.
 Unlink it.
 Point this node to the top of the sorted list.
 Point the sorted list at this node. (We're hand linking a sorted list here)
 Point to the sorted list as ours.
*/

void linkList::sort(bool ascending) {

   linkListObj*   sorted;
   linkListObj*   maxMin;

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
/*
 Someone has taken control of our list. Just let it go.
*/
void linkList::looseList(void) { theList = NULL; }
/*
****************************************************************************************
 stack : Your basic stack. Mostly pass throughs with the usual names.
****************************************************************************************
*/

/*
 Create a stack.
*/
stack::stack(void) : linkList() { }
/*
 Delete a stack.
*/
stack::~stack(void) {  }
/*
 Push this node into the stack.
*/
void stack::push(linkListObj* newObj) { addToTop(newObj); }
/*
 Remove and hand back the top of the stack. (YOU have to worry about deleting it.)
*/
linkListObj* stack::pop(void) {

   linkListObj*    topObj;

   topObj = getFirst();
   if (topObj) {
      unlinkTop();
   }
   return topObj;
}
/*
 Hand back the top of the stack without Removing it.
*/
linkListObj* stack::peek(void) { return getFirst(); }
/*
****************************************************************************************
 queue : Your basic queue. Again, mostly pass throughs with the usual names.
****************************************************************************************

 Create a queue.
*/
queue::queue(void) : linkList() { }
/*
 Delete a queue.
*/
queue::~queue(void) { }

/*
 Push this node into the end of the queue.
*/
void queue::push(linkListObj* newObj) { addToEnd(newObj); }
/*
 Hand back the head of the queue without unlinking it.
*/
linkListObj* queue::peek(void) { return getFirst(); }
/*
 Remove and hand back the head of the queue. (YOU have to worry about deleting it)
 Get a pointer to the top.
 If the top object is not NULL.
 Free the top from the list, re-attach the rest of the list.
 Return our result. NULL for empty list.
*/
linkListObj* queue::pop(void) {

   linkListObj*   topObj;

   topObj = getFirst();
   if (topObj) {
      unlinkTop();
   }
   return topObj;
}
/*
****************************************************************************************
 dblLinkListObj : This is the base object that "knows" how to link into chains with
 others like itself.
****************************************************************************************
*/

/*
 Create a double link list node.
*/
dblLinkListObj::dblLinkListObj(void) {

      dllPrev = NULL;
      dllNext = NULL;
}
/*
 Delete a double link list node.
*/
dblLinkListObj::~dblLinkListObj(void) { unhook(); }


/*
 Given a pointer to a node, link yourself after it.
 Sanity, If they didn't give us a NULL.
 Our next pointer gets their next pointer.
 Our next pointer gets their next pointer.
 Our previous pointer now points back to their node.
 Their next pointer now points to us.
 If our next pointer is NOT NULL. Point what its pointing to's next pointer, at us. (whew, hard to say)
*/

void dblLinkListObj::linkAfter(dblLinkListObj* anObj) {

   if (anObj) {
      dllNext = anObj->dllNext;
      dllPrev = anObj;
      anObj->dllNext = this;
      if (dllNext) dllNext->dllPrev = this;
   }
}

/*
 Given a pointer to a node, link yourself before it.
 Sanity, If they didn't give us a NULL.
 Our previous pointer now points to what their previous pointer points to.
 Our next pointer now points at them, err, their node.
 Their previous pointer now points to us.
 If our next previous is NOT NULL. Point what its pointing to's previous pointer, at us.
*/
void dblLinkListObj::linkBefore(dblLinkListObj* anObj) {

   if (anObj) {
      dllPrev = anObj->dllPrev;
      dllNext = anObj;
      anObj->dllPrev = this;
      if (dllPrev) dllPrev->dllNext = this;
   }
}
/*
 We are possibly in a list of nodes, find and pass back the head of the list.
 Point a trace pointer at us.
 While trace's previous pointer is not NULL.
 Jump to the previous node on the list.
 Return the result.
*/

dblLinkListObj* dblLinkListObj::getFirst(void) {

   dblLinkListObj*   trace;

   trace = this;
   while(trace->dllPrev) {
      trace = trace->dllPrev;
   }
   return trace;
}
/*
 We are possibly in a list of nodes, find and pass back the tail end of the list.
 Point a trace pointer at us.
 While trace's next pointer is not NULL.
 Jump to the next node on the list.
 Return the result.
*/

dblLinkListObj* dblLinkListObj::getLast(void) {

   dblLinkListObj*   trace;

   trace = this;
   while(trace->dllNext) {
      trace = trace->dllNext;
   }
   return trace;
}

/*
 Given a pointer to a node, link yourself after the last in the chain.
*/
void dblLinkListObj::linkToEnd(dblLinkListObj* anObj) { if (anObj) linkAfter(anObj->getLast()); }
/*
 Given a pointer to a node, link yourself before the first in the chain.
*/
void dblLinkListObj::linkToStart(dblLinkListObj* anObj) { if (anObj) linkBefore(anObj->getFirst()); }
/*
 Unlink us and, if in list, patch the hole.
 If our previous pointer is not NULL. Point our previous node's next pointer, to what
 our next pointer is pointing at.
 If our next pointer is not NULL. Point our next node's previous pointer, to what our
 previous pointer is pointing at.
 Ok, list is patched. Now we pull out. Our next gets NULL
 And our previous gets NULL.
*/
void dblLinkListObj::unhook(void) {

   if (dllPrev) dllPrev->dllNext = dllNext;
   if (dllNext) dllNext->dllPrev = dllPrev;
   dllNext = NULL;
   dllPrev = NULL;
}
/*
 Hand back the "nth" one of our tail. Starting at 0. (0 is first of tail, not us.)
 If there is no "nth" pass back NULL.
 Trace pointer gets our tail.
 Initialize counter.
 While trace is not NULL and the counter is less than the index we're looking for.
 Bump up the counter.
 Jump to the next node, or NULL if there isn't one.
 Pass back the result.
*/
dblLinkListObj* dblLinkListObj::getTailObj(int index) {

   dblLinkListObj*   trace;
   int               count;

   trace = dllNext;
   count = 0;
   while(trace&&count<index) {
      count++;
      trace = trace->dllNext;
   }
   return trace;
}

/*
 Delete entire tail. delete calls unhook before deleting the object.
*/
void dblLinkListObj::dumpTail(void) { while(dllNext) delete dllNext; }

/*
 Delete entire head section. delete calls unhook before deleting the object.
*/
void dblLinkListObj::dumpHead(void) { while(dllPrev) delete dllPrev; }

/*
 Dump both head & tail, leaving ourselves. All alone.
*/
void dblLinkListObj::dumpList(void) {

   dumpHead();
   dumpTail();
}

/*
 How many nodes long is our tail? (Not counting us)
 Trace pointer gets our tail.
 Initialize counter.
 While trace is not NULL.
 Bump up the counter.
 Jump to the next node, or NULL if there isn't one.
 Pass back the result.
*/
int dblLinkListObj::countTail(void) {

   dblLinkListObj*   trace;
   int               count;

   trace = dllNext;
   count = 0;
   while(trace) {
      count++;
      trace = trace->dllNext;
   }
   return count;
}

/*
 How many nodes long is our head? (Again, not counting us)
 Trace pointer gets our head.
 Initialize counter.
 While trace is not NULL.
 Bump up the counter.
 Jump to the previous node, or NULL if there isn't one.
 Pass back the result.
*/
int dblLinkListObj::countHead(void) {

   dblLinkListObj*   trace;
   int               count;

   trace = dllPrev;
   count = 0;
   while(trace) {
      count++;
      trace = dllPrev;
   }
   return count;
}
/*
 *** If you plan on sorting, its a good idea to fill out both! ***
//
// Are we greater than the dblLinkListObj that has been passed in? You fill this out if
// you plan to use the sorting method of dblLinkListObj.

 Are we greater than the obj being passed in?
*/
bool dblLinkListObj::isGreaterThan(dblLinkListObj* compObj) { return false; }
/*
 Are we less than the obj being passed in?
*/
bool dblLinkListObj::isLessThan(dblLinkListObj* compObj) {  return false;  }

/*
 ** IF ** you filled out the isGreaterThan() & isLessThan() methods.
*/
dblLinkListObj* dblLinkListObj::findMinMax(bool findMax) {

   dblLinkListObj*   trace;
   dblLinkListObj*   minMax;

   trace      = dllNext;
   minMax   = trace;
   while(trace) {
      trace = trace->dllNext;
      if (trace) {
         if (findMax) {
            if (trace->isGreaterThan(minMax)) {
               minMax = trace;
            }
         } else {
            if (trace->isLessThan(minMax)) {
               minMax = trace;
            }
         }
      }
   }
   return minMax;
}

/*
 And, if you did fill them out, this'll sort OUR TAIL. Meaning the original node is NOT
 sorted. If you want to sort them all, you are going to need a header node attached to
 the start the sort on.

 Yes, it is recursive. Don't like that? It's virtual. Override it and do a better one.
 If we have items to sort.
 Ascending?
 Then we want the smallest.
 else?
 We want the biggest.
 Sanity, it happens.
 If not already in order.
 Pull it out of the list.
 Link it after us.
 Something is going wrong.
 Just bail.
*/

void dblLinkListObj::sortTail(bool ascending) {


   dblLinkListObj*   minMax;

   if (countTail()>1) {
      if (ascending) {
         minMax = findMinMax(false);
      } else {
         minMax = findMinMax(true);
      }
      if (minMax) {
         if (minMax!=dllNext) {
            minMax->unhook();
            minMax->linkAfter(this);
         }
         minMax->sortTail(ascending);
      } else {
         return;
      }
   }
}




 
