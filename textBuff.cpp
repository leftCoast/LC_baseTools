#include <textBuff.h>
#include <resizeBuff.h>
#include <strTools.h>


textBuff::textBuff(int inNumBytes,bool inOverwrite)
	: ringIndex(inNumBytes) {

	
	overwrite = inOverwrite;
	buff      = NULL;
	returnStr = NULL;
	if (!resizeBuff(inNumBytes,&buff)) {
		numItems = 0;
	}
}


// Destructor, clean up what we allocated.
textBuff::~textBuff(void) {

	resizeBuff(0,&buff);
	resizeBuff(0,&returnStr);
}


// Add a charactor and update the state. If its full it can take two different actions.
// If overwrite is true the oldest char will be bumped off and the new char will be saved.
// If overwrite is false the no action is taken an false is returned. In all other cases
// true is returned.
bool textBuff::addChar(char inChar) {

	if (full() && overwrite) {		// If we're full, and overwrite is true..
		readItem();						// Make room by dumping the oldest char.
	}										//
	if (!full()) {						// If not full..
		buff[addItem()] = inChar;	// Add the char.
		return true;					// return success.
	}										//
	return false;						// If we end up here, we failed.
}


// If not empty, read the next charactor, update the state
// and return the read charactor. Otherwize return a null
// charactor.
char textBuff::readChar(void) {

	if (!empty()) {					// If we have some chars..
		return buff[readItem()];	// Return the oldest char.
	}										//
	return '\0';						// If not, pass back a \0.
}


// Add a c string till we got it all, or the poor thing is full. If its full and not
// overwriting, your going to loose your '\0'. Just sayin'.. Otherwise if its full and
// overwriting you will loose some of your oldest data.
bool textBuff::addStr(const char* inCStr,bool andNULL) {

	int		i;
	bool		success;
	
	success = false;							// Well, we ain't a success yet.
	i = 0;										// Start up our counter..
	while(inCStr[i]!='\0') {				// While we are not pointing at the NULL char..
		success = addChar(inCStr[i]);		// Blindly stuff the char into the buffer.
		i++;										// Increment counter.
	}												//
	if (andNULL) {								// If they want the null char saved..
		success =  addChar('\0');			// We add one in. Its the little things we do for you.
	}												//
	return success;							// Return if they all went in.
}


// How many chars would we read out if asked for a string? Not including the trailing NULL.
int textBuff::rStrlen(void) {

	int	trace;
	int	count;
	
	count = 0;													// Zero counter.
	if (!empty()) {											// If not empty.
		trace = tail;											// Pointing at the first item.
		while((trace!=head)&&(buff[trace]!='\0')) {	// Go 'till we're done.
			trace = increment(trace);						// Bump up trace.
			count++;												// Bump up count.
		}															//
	}
	return count;												// Return results.
}


// Hand back a c string of.. Either the first full string found.
// Or.. All of the text with a '\0' appended to it. If empty, it
// returns Just a NULL'.
char*	 textBuff::readStr(void) {

	int	numChars;
	int	i;
	
	numChars = rStrlen();								// Read how many chars we have, no NULLs.
	if (numChars) {										// If we have at least one char..
		if (resizeBuff(numChars+1,&returnStr)) {	// Make room!
			for (i=0;i<numChars;i++) {					// If rStrlen() don't lie..
				returnStr[i] = readChar();				// Stuff in the chars.
			}													//
			if (buff[tail]=='\0') {						// If the next one is NULL char..
				returnStr[i] = readChar();				// pop it out and use it.
			} else {											// Otherwise..
				returnStr[i] = '\0';						// Stuff in our own NULL char.
			}													//
			return returnStr;								// Pass out the string.
		}														//
	}															//
	return NULL;											// No string? Pass back NULL.
}

