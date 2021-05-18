#include "resizeBuff.h"

// DON'T USE UNINITIALIZED POINTERS!! EVEN JUST SETTING TO NULL WILL BE FINE.
// Once your pointer is either set to NULL or allocated, then it can be used
// in here all you want.

bool resizeBuff(int numBytes,uint8_t** buff) {

  if(*buff) {										// If we did NOT get passed in a NULL..
    free(*buff);									// We free the memory.
    *buff = NULL;									// Set the pointer to NULL.
  }
  if (numBytes>0) {								// If we got a positive non zero value..
    *buff = (uint8_t*)malloc(numBytes);	// We attempt allocate that number of bytes.
    return *buff != NULL;						// And we return true for non NULL result (non-NULL = Success)
  }
  return true;										// In this case we were not asked to allocate anything so it was a success.
}

bool resizeBuff(int numBytes,char** buff) { return resizeBuff(numBytes,(uint8_t**)buff); }

bool resizeBuff(int numBytes,void** buff) { return resizeBuff(numBytes,(uint8_t**)buff); }

bool resizeBuff(int numBytes,float** buff) { return resizeBuff(numBytes,(uint8_t**)buff); }

//bool resizeBuff(int numBytes,byte** buff) { return resizeBuff(numBytes,(uint8_t**)buff); }