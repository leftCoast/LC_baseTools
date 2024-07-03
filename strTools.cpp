#include <strTools.h>



//****************************************************************************************
// upCase(), lwrCase():
//
// Pass in a c string and make all the letters either uppercase orlowercase.
//****************************************************************************************


// Pass in a string and this makes all the letters uppercase.
void upCase(char* inStr) {

	int i;

	i=0;
	while(inStr[i]) {
		inStr[i] = toupper(inStr[i]);
		i++;
	}
}

// Pass in a string and this makes all the letters lowercase.
void lwrCase(char* inStr) {

	int i;

	i=0;
	while(inStr[i]) {
		inStr[i] = tolower(inStr[i]);
		i++;
	}
}



//****************************************************************************************
// heapStr:
//
// For reallocating strings.
// Good for passing string data from one function to another. Lets you have an easy way to
// "land" the data. Typically this is used for setting the size of a global buffer to fit
// the current data. No more max sized buffers clogging up the heap.    each time you write a
// string to it it auto resizes to just fit that string.
//****************************************************************************************


// Load in this string. Allocate, or re-allocate your char* to save it.
bool heapStr(char** resultStr,const char* inStr) {

	int 	numChars;
	bool	success;

	success = false;                                       // We need to prove our success!
	if (inStr) {                                           // If we got a non-NULL string..
		numChars = strlen(inStr);                          // Count the chars in inStr.
		if (resizeBuff(numChars+1,resultStr)) {            // If we can allocated the memory..
			strcpy(*resultStr,inStr);                      // Copy input into the resulting string.
			success = true;                                // And that's a success!
		}
	} else {                                               // Else, they handed us a NULL string?
		resizeBuff(0,resultStr);                           // I guess they want the result to be NULL as well.
		success = true;                                    // In that case, I guess we were successful.
	}
	return success;                                        // And we return our success. Good or bad.
}


// When you are done with the string you were using, call this to recycle the RAM.
void freeStr(char** resultStr) { resizeBuff(0,resultStr); }



//****************************************************************************************
//  tempStr
// Very good for grabbing data that may change and holding a copy it so you can do your
// stuff without worry. Auto deallocated when it goes out of scope.
//
// DO NOT CREATE THESE INSIDE A SWITCH STATEMENT! Creating variables and classes in switch
// statements totally breaks them. You can USE them in switch statements as long as they
// are created outside of the switch statements.
//****************************************************************************************


tempStr::tempStr(const char* inStr) {

	theStr = NULL;
	if (inStr) {
		setStr(inStr);
	}
}


tempStr::~tempStr(void) { freeStr(&theStr); }

void tempStr::setStr(const char* inStr) { heapStr(&theStr,inStr); }

int tempStr::numChars(void) { return strlen(theStr); }

const char* tempStr::getStr(void) { return (const char*)theStr; }
