#include "serialStr.h"
#include <resizeBuff.h>

 
serialStr::serialStr(Stream* inPort,char endChar,int numBytes) {

	port		= inPort;
	index		= 0;
	EOL		= endChar;
	bytes		= numBytes;
	overrun	= false;
	resizeBuff(numBytes,&buff);
}


serialStr::~serialStr(void) { resizeBuff(0,&buff); }


void serialStr::setCallback(void(*funct)(const char*)) { 

   callback = funct;
   hookup();
}


void serialStr::idle(void) {

	char  aChar;
   
	if (port->available()) {			// If there is a char in the waiting to be read..
		aChar = port->read();			// Grab and save the char.
		if (aChar==EOL) {             // If its a newline char..
         callback(buff);            // call it.
         overrun = false;           // If set, cler the overrun flag.
         buff[0] = '\0';            // Clear the inBuff string.
         index = 0;                 // Reset the index to start a new number string.
      } else {                      // Else, it wasn't a newline char..
         if (index<(bytes-1)) {
            buff[index++] = aChar;  // So we save the char we got into the c string.
            buff[index] = '\0';     // And pop an end of string after it.
         } else {
            overrun = true;         // Just blew past the buffer.
         }
      }
   }
}



bool serialStr::hadOverrun(void) { return overrun; }
