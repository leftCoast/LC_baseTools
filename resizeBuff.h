#ifndef resizeBuff_h
#define resizeBuff_h

#include "Arduino.h"


/*

Ok, what is this resizeBuff thing?

Forever I found myself writing..

if (buff) {
	free(buff);
	buff = NULL;
}
buff = malloc(newSize);
if (buff) {
	do stuff..
}

Over and over. Then one day I wrote my first version
of a "stretchy buffer" and that got me thinking.. Is
there a way to generalize this idea? 

Hence : resizeBuff()

As long as your buffer starts life alocated or with
a NULL. You can use this quick call to resize it as
much as you like. And, it returns a boolean true or
false as to if it was able to do it or not. Keeps you
from writing into unallocated RAM as it were.

NOTE: Resizing still means you loose whatever data was originally in it.

Now its just..

if (resizeBuff(newSize,&buffPtr)) {		// Notice?
	do stuff..									// Address of the pointer there..
}													// Eww! So tricky!


NOTE : Why a pointer to uint8_t?
Originally this was setup at char* because it started with c strings. Then
It started being used for binary data blocks. Then binary data blocks crossing
over serial to other processors.. Word size stuff bit me in the.. Foot. uint8_t 
forced buffer sizes to match up.

*/


extern bool resizeBuff(int numBytes,uint8_t** buff);
extern bool resizeBuff(int numBytes,char** buff);
extern bool resizeBuff(int numBytes,void** buff);
//extern bool resizeBuff(int numBytes,byte** buff);


// class maxBuff:
// Lets say you need to write to something with, possibly, more data than you can allocate
// at one time? What to do? This class will start at your maximum desired buffer size and
// try allocating it. If that fails, it tries for half that size. Then 1/3 the size, 1/4..
// Until either it succeeds in allocating a buffer, or, hits the buffer minimum size and
// gives up.
//
// On success : 
// theBuff is the pointer to your allocated buffer.
// numBuffBytes is the size in bytes of that buffer.
// numPasses is the number of passes it will take to write/read your desired data.
//
// On failure :
// theBuff will equal NULL.
//
// NOTE : This should be allocated as a local variable. Then on exit, it will recycle the
// buffer. Pretty slick huh?

#define BYTE_CUTOFF 20

class maxBuff {

	public:
				maxBuff(unsigned long numBytes,unsigned long  minBytes=BYTE_CUTOFF);
	virtual	~maxBuff(void);
	
				void*				theBuff;
				unsigned long	numBuffBytes;
				int				numPasses;
	};

#endif
