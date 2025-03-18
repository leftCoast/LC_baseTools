#ifndef strTools_h
#define strTools_h

#include <resizeBuff.h>



//****************************************************************************************
// upCase(), lwrCase():
//
// Pass in a c string and make all the letters either uppercase or lowercase.
//****************************************************************************************


// Pass in a string and this makes all the letters uppercase.
void upCase(char* inStr);


// Pass in a string and this makes all the letters lowercase.
void lwrCase(char* inStr);



//****************************************************************************************
// heapStr():
//
// In the good old days people used to do..
//
// char* aStr = "Look data!";
//
// And that would allocate room for the text and put there. Sadly it would only do it
// once. Now, wouldn't that be nice if you could do it repeatedly? Now you can!
//
// char* aStr = NULL;                                      // ALWAYS initialize at NULL for this.
//
// heapStr(&aStr,"Look data!");                            // Allocates and stuffs it in.
// heapStr(&aStr,"Look longer data!");                     // Recycles, re-allocates and writes.
// heapStr(&aStr,"Can be called as needed.");              // Get the picture?
// freeStr(&aStr);                                         // Just recycles and sets back to NULL.
//****************************************************************************************


extern bool heapStr(char** resultStr,const char* inStr);
extern void freeStr(char** resultStr);



//****************************************************************************************
// tempStr :
//
// Ok, take all these bits to their limit and make the easiest thing to use for a quick
// string buffer. The tempStr class is a stack based class. Meaning? It will store your
// string only until it goes out of scope, and then it automatically recycles the memory
// for you.
//
// tempStr myStr(readThing(pinNum));	// Copy the output of a string function.
//
// -or-
//
// tempStr myStr;								// Or an empty one. Ready to save a string.
//
// myStr.setStr(readThing(pinNum));		// You can save a string later. Or reuse.
// formatAndDisplay(myStr.getStr());	// We don't worry about what the readThing() does.
//													// We now have a local copy.
//
// return;                            	// When tempStr goes out of scope, It recycles.
//****************************************************************************************


class tempStr {

	public:
				tempStr(const char* inStr=NULL);
	virtual	~tempStr(void);

				void			setStr(const char* inStr);
				int			numChars(void);
				const char*	getStr(void);

		char*	theStr;
};


#endif