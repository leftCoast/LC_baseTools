#include <textBuff.h>
#include <resizeBuff.h>
#include <strTools.h>


textBuff::textBuff(int inNumBytes,bool inOverwrite) {

	
	overwrite = inOverwrite;
	buff      = NULL;
	returnStr = NULL;
	while(inNumBytes && !resizeBuff(inNumBytes,&buff)) {		// While inNumBytes>0 and resizing the buffer fails..
		inNumBytes = inNumBytes/2;										// Try for 1/2 the number of bytes?
	}
	ourIndex = new ringIndex(inNumBytes);							// Setup the bookkeeping.
}


// Destructor, clean up what we allocated.
textBuff::~textBuff(void) {

	resizeBuff(0,&buff);
	resizeBuff(0,&returnStr);
	if (ourIndex) delete(ourIndex);
}


// Add a charactor and update the state. If its full it can take two different actions.
// If overwrite is true the oldest char will be bumped off and the new char will be saved.
// If overwrite is false the no action is taken an false is returned. In all other cases
// true is returned.
bool textBuff::addChar(char inChar) {

	if (ourIndex->full() && overwrite) {	// If we're full, and overwrite is true..
		(void)ourIndex->readItem();			// Make room by dumping the oldest char.
	}													//
	if (!full()) {									// If not full..
		buff[ourIndex->addItem()] = inChar;	// Add the char.
		return true;								// return success.
	}													//
	return false;									// If we end up here, we failed.
}


// Add a c string till we got it all, or the poor thing is full. If its full and not
// overwriting, your going to loose your '\0'. Just sayin'.. Otherwise if its full and
// overwriting you will loose some of your oldest data.
bool textBuff::addStr(char* inCStr,bool andNULL) {

	int		
	i;
	bool		success;
	
	success = false;							// Well, we ain't a success yet.
	i = 0;										// Start up our counter..
	while(inCStr[i]!='\0') {				// While we are not pointing at the NULL char..
		success = addChar(inCStr[i]);		// Blindly stuff the char into the buffer.
		i++;										// Increment counter.
	}
	if (andNULL) {								// If they want the null char saved..
		success =  addChar('\0');			// We add one in. Its the little things we do for you.
	}
	return success;							// Return if they all went in.
}


// Pass back the next char on the list, unless we got nothin' then pass back a /0.
// Don't change anything.
char textBuff::peekHead(void) {

  if (empty()) return '\0';				// If empty, return a \0.
  return buff[ourIndex->peekItem()];	// Otherwise, return the char that's next to read.
}


// Pass back the nTh char on the list, unless we got nothin' then pass back a /0.
// Don't change anything.
char textBuff::peekIndex(int inIndex) {
	
	if (empty())					return '\0';	// If empty, return a '\0'.
	if (inIndex>=numChars())	return '\0';	// If we don't have that one, return a '\0'.
	return buff[ourIndex->peekItem(inIndex)];	// Otherwise, return the char we found.
}


// If not empty, read the next charactor, update the state
// and return the read charactor. Otherwize return a null
// charactor.
char textBuff::readChar(void) {

	if (!empty()) {								// If we have some chars..
		return buff[ourIndex->readItem()];	// Return the oldest char.
	}													//
	return '\0';									// If not, pass back a \0.
}


// How many chars would we read out if asked for a string? Not including the trailing NULL.
int textBuff::strlen(void) {

	int	index;
	int	result;
	
	if (empty()) return 0;							// Well, if we got none, we give none.
	index = 0;											// Pointing at the first item.
	while(1) {											// Go forever 'till were kicked out.
		result = ourIndex->peekItem(index);		// What we get when we peek at this?
		if (result==INDEX_ERR)	return index;	// We ran out.
		if (buff[result]=='\0') return index;	// We hit the end of a string!
		index++;											// Still running? Bump up index;
	}														//
	return 0;											// There is NO WAY we can get here.
}


// Hand back a c string of.. Either the first full string found.
// Or.. All of the text with a '\0' appended to it. If empty, it
// returns Just a c string consisting of '\0'.
char*	 textBuff::readStr(void) {

	int	count;
	int	strIndex;
	
	resizeBuff(1,&returnStr);													// Setup for failure, 1 char.
	returnStr[0] = '\0';															// And that one char gets..
	if (!empty()) {																// If we HAVE data..
		count = strlen();															// read how many chars we have, no NULLs.
		if (count) {																// If we have at least one char..
			if (resizeBuff(count+1,&returnStr)) {							// Make room!
				strIndex = 0;														// Starting at the zero char.
				while(count) {														// While we have chars to read.
					returnStr[strIndex] = buff[ourIndex->readItem()];	// read a char, stuff it in our returnStr.
					strIndex++;														// Bump up our string index.
					count--;															// Knock a char off our list.
				}																		//
				returnStr[strIndex] = '\0';									// Pop a NULL in the last place.
			}																			//
		}																				//
	}																					//
	return returnStr;																// Pass out the string.
}


// Return the numnber of charactors THAT CAN BE stored in this buffer.
int textBuff::buffSize(void) { return  ourIndex->maxItems(); }


// Return the numnber of charactors THAT ARE stored in the buffer.
int textBuff::numChars(void) { return ourIndex->itemCount(); }


// Return whethere the buffer is empty or not.
bool textBuff::empty(void) { return ourIndex->empty(); }


// Return if the buffer is full or not.
bool textBuff::full(void) { return ourIndex->full();  }


// Just clear the data NOT release RAM.
void  textBuff::clear(void) { ourIndex->flushItems(); }




/*
textBuff::textBuff(int inNumBytes,bool inOverwrite) {

	head      = 0;
	tail      = 0;
	isFull    = false;
	overwrite = inOverwrite;
	buff      = NULL;
	returnStr = NULL;
	while(inNumBytes && !resizeBuff(inNumBytes,&buff)) {		// While inNumBytes>0 and resizing the buffer fails..
		inNumBytes = inNumBytes/2;										// Try for 1/2 the number of bytes?
	}
	numBytes = inNumBytes;                                   // Note how many bytes we ended up with.
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


	if (overwrite && full()) {		// If we're full and overwrite is true..
		(void)readChar();				// Make room by dumping the oldest char.
	}
	if (!full()) {						// If not full..
		buff[tail] = inChar;			// Save off the incoming char.
		inc(&tail);						// Increment the tail pointer.
		isFull = tail==head;			// Check and note if we are full.
		return true;					// Return a success.
	}
	return false;						// Couldn't save the new char, return a failure.
}


// Add a c string till we got it all, or the poor thing is full. If its full and not
// overwriting, your going to loose your '\0'. Just sayin'.. Otherwise if its full and
// overwriting you will loose some of your oldest data.
bool textBuff::addStr(char* inCStr,bool andNULL) {

	int		
	i;
	bool		success;
	
	success = false;							// Well, we ain't a success yet.
	i = 0;										// Start up our counter..
	while(inCStr[i]!='\0') {				// While we are not pointing at the NULL char..
		success = addChar(inCStr[i]);		// Blindly stuff the char into the buffer.
		i++;										// Increment counter.
	}
	if (andNULL) {								// If they want the null char saved..
		success =  addChar('\0');			// We add one in. Its the little things we do for you.
	}
	return success;							// Return if they all went in.
}


// Pass back the next char on the list, unless we got nothin' then pass back a /0.
// Don't change anything.
char textBuff::peekHead(void) {

  if (empty()) return '\0';	// If empty, return a \0.
  return buff[head];				// Otherwise, return the char that's next to read.
}


// Pass back the nTh char on the list, unless we got nothin' then pass back a /0.
// Don't change anything.
char textBuff::peekIndex(int index) {

	int absIndex;
	
	if (empty()) return '\0';					// If empty, return a '\0'.
	if (index>numChars()) return '\0';		// If we don't have that one, return a '\0'.
	absIndex = head + index;					// Take a shot at the absolute index 
	if (absIndex>=numBytes) {					// If we are past the buffer size..
		absIndex = absIndex - numBytes;		// Subtract the buffer size from the absolute.
	}													//
  	return buff[absIndex];						// Otherwise, return the char that's next to read.
}


// If not empty, read the next charactor, update the state
// and return the read charactor. Otherwize return a null
// charactor.
char textBuff::readChar(void) {

  char  theChar;

  if (!empty()) {				// If we have some chars..
    theChar = buff[head];	// Save off the oldest char.
    inc(&head);				// Do the indexing update.
    isFull = false;			// In any case we are no longer full.
    return theChar;			// Return the oldest char.
  } else {						// Else, we were empty..
    return '\0';				// Pass back a \0.
  }
}


// Hand back a c string of.. Either the first full string found.
// Or.. All of the text with a '\0' appended to it. If empty, it
// returns Just a c string consisting of '\0'.
char*	 textBuff::readStr(void) {

	int	i;
	
	resizeBuff(1,&returnStr);										// Resize the buff for empty string.
	returnStr[0] = '\0';												// Copy in the \0.
	if (!empty() && resizeBuff(strlen()+1,&returnStr)) {	// If there are bytes AND we can allocate enough..
		i = -1;															// Starting at -1.
		do {																// Repeat..
			i++;															// Bump up the index. (Now starting at zero)
			returnStr[i] = readChar();								// Read a char into our returnStr.
		} while(returnStr[i]!='\0'&&!empty());					// If we DIDN'T read a null and STILL have chars..
		if (returnStr[i]!='\0') {									// If we didn't get a NULL char.
			i++;															// Bump up the index.
			returnStr[i] = '\0';										// Pop a '\0' after the last char.
		}																	//
	}																		//
	return returnStr;													// Send it on it's way.
}


// Return the numnber of charactors THAT CAN BE stored in this buffer.
int textBuff::buffSize(void) { return numBytes; }


// Return the numnber of charactors THAT ARE stored in the buffer.
int textBuff::numChars(void) {

  if (empty()) {								// If its empty..
    return 0;									// Well, that would be zero.
  } else if (full()) {						// If its full..
    return numBytes;							// Return the number of bytes we store.
  } else if (head<tail) {					// Head less that tail.
    return tail - head;						// Data is between them, return the difference.
  } else {										// And lastly.. Head is greater than tail..
    return numBytes - (head - tail);	// Kinda' opposite. Data is between them on the other side.
  }
}


// How many chars would we read out if asked for a string? Not including the trailing NULL.
int textBuff::strlen(void) {

	int count;
	int max;
	int strIdx;
	
	if (empty()) return 0;							// Well if we got none we give none.
	strIdx = head;										// Copied from readChar().
	max = numChars();									// store the number of chars we have.
	count = 0;											// And starting at zero chars to read.
	while(buff[strIdx]!='\0'&&count<max) {		// If we're not pointing at null, and not at the limit of data..
		count++;											// Bump up the char count.
		inc(&strIdx);									// Increment the local index.
	}														//
	return count;										// And when complete, we return count.
}


// Return whethere the buffer is empty or not.
bool textBuff::empty(void) { return ((head==tail)&&!isFull); }


// Return if the buffer is full or not.
bool textBuff::full(void) { return isFull; }


// Just clear the data NOT release RAM.
void  textBuff::clear(void) {

  head = 0;
  tail = 0;
  isFull = false;		// In any case we are no longer full. (Missed that in the original)
}


// Increment an index. Hop over to zero if we go past the end.
void textBuff::inc(int* index) {

  *index = *index + 1;		// Bump up this index.
  if (*index>=numBytes) {	// If this index went off the end..
    *index = 0;				// Set it to zero.
  }
}
*/
