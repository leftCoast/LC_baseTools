#include "textBuff.h"
#include "resizeBuff.h"


// *****************************************************
//                      textBuff
// *****************************************************


textBuff::textBuff(int inNumBytes) {

  head    = 0;
  tail    = 0;
  isFull  = false;
  buff    = NULL;
  while(inNumBytes && !resizeBuff(inNumBytes,&buff)) {  // While inNumBytes>0 and resizing the bufer fails..
    inNumBytes = inNumBytes/2;                          // Try for 1/2 the number of bytes?
  }
  numBytes = inNumBytes;                                // Note how many bytes we ended up with.
}


textBuff::~textBuff(void) { resizeBuff(0,&buff); }


// If  not full, add a charactor and update the state.
bool textBuff::addChar(char inChar) {

  if (!full()) {
    buff[tail] = inChar;
    inc(&tail);
    isFull = tail==head;
    return true;
  }
  return false;
}


// Pass back the next char on the list, unless we got nothin' then pass back a /0.
// Don't change anything.
char textBuff::peekHead(void) {

  if (empty()) return '\0';
  return buff[head];
}
    

    
// If not empty, read the next charactor, update the state
// and return the read charactor. Otherwize return a null
// charactor.
char textBuff::readChar(void) {

  char  theChar;

  if (!empty()) {
    theChar = buff[head];
    inc(&head);
    isFull = false;
    return theChar;
  } else {
    return '\0';
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


// Inctment on index. Hop over to zero if we go past the end.
void textBuff::inc(int* index) {

  *index = *index + 1;
  if (*index>=numBytes) {
    *index = 0;
  }
}