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

Then..

if (buff) {
	do stuff..
}
Over and over. Then one day I wrote my first version
of a "stretchy buffer" and that got me thinking.. Is
there a way to generalize this idea? 

Hence : resizeBuff()

As long as your buffer starts life alocated or with
a NULL. You can use this quick call to resize it as
much as you like. And, it returns a boolean true   or
false as to if it was able to do it or not. Keeps you
from writing into unallocated RAM as it were.

Now its just..

if (resizeBuff(newSize,&buffPtr)) {		// Notice?
	do stuff..									// Address of the pointer there..
}													// Eww! So tricky!

And it always works.

NOTE : Why a pointer to uint8_t?
Originally this was setup at char* because it started with c strings. Then
It started being used for binary data blocks. Then binary data blocks crossing
over serial to other processors.. Word size stuff bit me in the.. Foot. uint8_t 
forced buffer sizes to match up.

*/


bool resizeBuff(int numBytes,uint8_t** buff);
bool resizeBuff(int numBytes,char** buff);
bool resizeBuff(int numBytes,void** buff);
bool resizeBuff(int numBytes,byte** buff);
#endif
