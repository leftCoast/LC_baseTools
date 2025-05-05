#ifndef lists_h
#define lists_h

#include <Arduino.h>    // Do we need this here?


//****************************************************************************************
// Your basic single linked list. Good for lists and stacks. One issue is, that the list
// objects can not unlink themselves. This is because they have no idea who points at
// them. So, unlike the double linked list, a list owner must manage the list objects.
//****************************************************************************************

// This is the base for the things in the list..
class linkListObj {

  public:
				linkListObj(void);
    virtual	~linkListObj(void);

    virtual void				linkAfter(linkListObj* anObj);			// Given a pointer to a node, link yourself after it.
    virtual void				linkToEnd(linkListObj* anObj);			// Given a pointer to a node, link yourself after the last in the chain.
    virtual linkListObj*	getNext(void);									// Pass back the next pointer.
    virtual void				setNext(linkListObj* ptr);					// Point somewhere else.
    virtual void				deleteTail(void);          				// Call delete on everyone hooked to us.
    virtual bool				isGreaterThan(linkListObj* compObj);	// Are we greater than the obj being passed in? Primary sorting function.
    virtual bool				isLessThan(linkListObj* compObj);		// Are we less than the obj being passed in? Primary sorting function.

  protected :
				linkListObj*	next;
};


// This is the manager for a list.
class linkList {

  public:
                linkList(void);
    virtual ~linkList(void);

    virtual void				addToTop(linkListObj* newObj);			// Give it a node and it'll add it to the top. (Fast)
    virtual void				addToEnd(linkListObj* newObj);			// give it a node and it'll addd it to the end  (Slower)
    virtual void				unlinkTop(void);         					// Push off the first one. (Does NOT delete it.)
    virtual void				unlinkObj(linkListObj* oldObj);			// Find it and push this one off.
    virtual void				dumpList(void);          					// Call delete on everyone.
    virtual bool				isEmpty(void);									// Well, is it?
    virtual linkListObj*	getFirst(void);								// Hand back a link to the top node.
    virtual linkListObj*	getLast(void);									// Hand back a link to the list node on the list.
    virtual linkListObj*	findMax(linkListObj* anObj);				// These two will pass back links to the max & min of the list..
    virtual linkListObj*	findMin(linkListObj* anObj);				// IF you filled out the isGreaterThan() & isLessThan() methods.
    virtual void				sort(bool ascending);						// And, if you did fill them out, this'll sort the list.

            int				getCount(void);								// Count the number of nodes, hand back that number.
            linkListObj*	getByIndex(int index);						// Same as a c type array. Hand back a link to the node at index. 
            int				findIndex(linkListObj* anObj);			// returns -1 if NOT found.
            void				looseList(void);								// Someone has taken control of our list, let it go.

  protected :
            linkListObj*	theList;
};



//****************************************************************************************
// stack
// In the stack we have push, pop, peek & isEmpty.
// When popping an item, it's unlinked and handed to you. YOU have to delete it.
// Deleting the stack will auto delete everything for you.
//****************************************************************************************


class stack : public linkList {

	public:
				stack(void);
	virtual	~stack(void);

	virtual	void				push(linkListObj* newObj);
	virtual	linkListObj*	pop(void);
	virtual	linkListObj*	peek(void);
};



//****************************************************************************************
// queue
// Just like in the stack, in the queue we have push, peek, pop & isEmpty. But, when we
// add an object we don't add it to the top of the list. We add it to the end.
// When popping an item, it's unlinked and handed to you. YOU have to delete it.
// Deleting the queue will auto delete everything for you.
//****************************************************************************************


class queue : public linkList {

	public:
				queue(void);
	virtual	~queue(void);

	virtual	void				push(linkListObj* newObj);
	virtual	linkListObj*	pop(void);						
	virtual	linkListObj*	peek(void);
};



//****************************************************************************************
// Double linked list. Handy if you'd like to traverse both ways. Also handy 'cause it
// can be self managing.
//****************************************************************************************


class dblLinkListObj {

	public:
				dblLinkListObj(void);
	virtual	~dblLinkListObj(void);

			void					linkAfter(dblLinkListObj* anObj);	// Given a pointer to a node, link yourself after it.
			void					linkBefore(dblLinkListObj* anObj);	// Given a pointer to a node, link yourself before it.
			dblLinkListObj*	getFirst(void);							// Runs up the list 'till dllPrev == NULL. Returns link to that node.
			dblLinkListObj*	getLast(void);								// Runs up the list 'till dllNext == NULL. Returns link to that node.
			void					linkToEnd(dblLinkListObj* anObj);	// Given a pointer to any node, link yourself after the last in the chain.
			void					linkToStart(dblLinkListObj* anObj);	// Given a pointer to any node, link yourself before the first in the chain.
			dblLinkListObj*	getTailObj(int index);     			// Hand back the "nth" one of our tail. Starting at 0;
			void					unhook(void);      						// Unhook myself.
			void					dumpTail(void);    						// Delete entire tail.
			void					dumpHead(void);    						// Delete entire head section..
			void					dumpList(void);    						// Delete both head & tail.
			int					countTail(void);							// How many nodes long is our tail?
			int					countHead(void);     					// How many nodes long is our head?

			dblLinkListObj*	dllPrev;
			dblLinkListObj*	dllNext;
};



#endif
