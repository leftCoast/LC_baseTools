#include "serialStr.h"
#include <resizeBuff.h>



// Constructor, set up all the fun bits and allocate a buffer for the text.
serialStr::serialStr(Stream* inPort,char endChar,int numBytes) {

	port        = inPort;
	index       = 0;
	EOL         = endChar;
	bytes       = numBytes;
	overrun     = false;
	resizeBuff(numBytes,&buff);
}


// Destructor, recycle the buffer.
serialStr::~serialStr(void) { resizeBuff(0,&buff); }


// Take in the callback function pointer. While we're at it, do the hookup() call for
// doing idle function.
// void serialStr::setCallback(void(*funct)(const char*)) {

void serialStr::setCallback(void(*funct)(char*)) {

	callback = funct;
	hookup();
}


// All the work happens in idle(). Basically check for a char to come in, save it if we
// can. Or tell the user if its on EOT char and start over.
void serialStr::idle(void) {

	char  aChar;

	if (buff) {													// If we have a buffer to put things in..
		if (port->available()) {							// If there is a char in the waiting to be read..
			aChar = port->read();							// Grab and save the char.
			if (aChar==EOL) {									// If its a newline char..
				callback(buff);								// Call our callback with the buffer.
				overrun = false;								// If set, clear the overrun flag.
				buff[0] = '\0';								// Clear the inBuff string.
				index = 0;										// Reset the index to start a new number string.
			} else {												// Else, it wasn't a newline char..
				if (index<(bytes-1)) {						// If we have room in the buffer..
					buff[index++] = aChar;					// So we save the char we got into the c string.
					buff[index] = '\0';						// And pop an end of string after it.
				} else {											// Else, we ran out of room in the buffer!
					overrun = true;							// Just blew past the buffer.
				}
			}
		}
	}
}


// We can ask if there was an overrun. This will return true if there was. Does not clear
// the overrun. Although it probably should.
bool serialStr::hadOverrun(void) { return overrun; }
