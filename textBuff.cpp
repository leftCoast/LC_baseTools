#include <textBuff.h>
#include <resizeBuff.h>



textBuff::textBuff(int inNumBytes,bool inOverwrite) {

  head		= 0;
  tail		= 0;
  isFull		= false;
  overwrite	= inOverwrite;
  buff		= NULL;
  while(inNumBytes && !resizeBuff(inNumBytes,&buff)) {  // While inNumBytes>0 and resizing the bufer fails..
    inNumBytes = inNumBytes/2;                          // Try for 1/2 the number of bytes?
  }
  numBytes = inNumBytes;                                // Note how many bytes we ended up with.
}


textBuff::~textBuff(void) { resizeBuff(0,&buff); }


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

	int	i;						
	bool	success;
	
	success = false;							// Well, we ain't a success yet.
	i = 0;										// Start up our counter..
	while(inCStr[i]!='\0') {				// While we are not potinting at the NULL char..
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
    

    
// If not empty, read the next charactor, update the state
// and return the read charactor. Otherwize return a null
// charactor.
char textBuff::readChar(void) {

  char  theChar;

  if (!empty()) {					// If we have some chars..
    theChar = buff[head];		// Save off the oldest char.
    inc(&head);					// Do the indexing update.
    isFull = false;				// In any case we are no longer full.
    return theChar;				// Return the oldest char.
  } else {							// Else, we were empty..
    return '\0';					// Pass back a \0.
  }
}


// Return the numnber of charactors THAT CAN BE stored in this buffer.
int textBuff::buffSize(void) {return numBytes; }


// Return the numnber of charactors stored in the buffer.
int textBuff::numChars(void) {

  if (empty()) {                      // If its empty..
    return 0;                         // Well, that would be zero.
  } else if (full()) {                // If its full..
    return numBytes;                  // Return the number of bytes we store.
  } else if (head<tail) {             // Head less that tail.
    return tail - head;               // Data is between them, return the difference.
  } else {                            // And lastly.. Head is greater than tail..
    return numBytes - (head - tail);  // Kinda' opposite. Data is between them on the other side. 
  }
}


// Return whethere the buffer is empty or not.
bool textBuff::empty(void) { return ((head==tail)&&!isFull); }


// Return if the buffer is full or not.
bool textBuff::full(void) { return isFull; }


// Just clear the data NOT release RAM.
void  textBuff::clear(void) {

  head = 0;
  tail = 0;
}


// Inctment an index. Hop over to zero if we go past the end.
void textBuff::inc(int* index) {

  *index = *index + 1;			// Bump up this index.
  if (*index>=numBytes) {		// If this index went off the end..
    *index = 0;					// Set it to zero.
  }
}