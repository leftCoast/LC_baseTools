#include "resizeBuff.h"

// DON'T USE UNINITIALIZED POINTERS!! EVEN JUST SETTING TO NULL WILL BE FINE.
// Once your pointer is either set to NULL or allocated, then it can be used
// in here all you want.

bool resizeBuff(int numBytes,uint8_t** buff) {

  if(*buff) {
    free(*buff);
    *buff = NULL;
  }
  if (numBytes) {
    *buff = (uint8_t*)malloc(numBytes);
    return *buff != NULL;
  }
  return true;
}

bool resizeBuff(int numBytes,char** buff) { return resizeBuff(numBytes,(uint8_t**)buff); }

bool resizeBuff(int numBytes,void** buff) { return resizeBuff(numBytes,(uint8_t**)buff); }

//bool resizeBuff(int numBytes,byte** buff) { return resizeBuff(numBytes,(uint8_t**)buff); }