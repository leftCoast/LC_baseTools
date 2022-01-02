#include <resizeBuff.h>

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

//bool resizeBuff(int numBytes,byte** buff) { return resizeBuff(numBytes,(uint8_t**)buff); } // Causes compiler issues..


// maxBuff:
// Class for slicing up huge datat streams into sizable buffers.


maxBuff::maxBuff(unsigned long numBytes,unsigned long  minBytes) {

	theBuff			= NULL;								// Pointers start at NULL.
	numBuffBytes	= numBytes;							// In a perfect world, numBytes will work.
	numPasses		= 1;									// In that same world, we'll only need one pass.
	while(!resizeBuff(numBuffBytes,&theBuff)) {	// Have a go at allocating the buffer..
		numPasses++;										// If we didn't get it, bump up number of passes.
		numBuffBytes = (numBytes/numPasses) + 1;	// Cut down the buffer size.
		if (numBuffBytes<minBytes) return;			// At some point, lets just give up.
	}															// If we didn't get it last time, we try again smaller.
}


maxBuff::~maxBuff(void) { resizeBuff(0,&theBuff); }
	
	
// heapStr():
// For reallocating strings.				
				
bool heapStr(char** resultStr,const char* inStr) {

	int	numChars;									
	bool	success;
	
	success = false;										// We need to prove our success!
	if (inStr) {											// If we got a non-NULL string..
		numChars = strlen(inStr);						// Count the chars in inStr.
		if (resizeBuff(numChars+1,resultStr)) {	// If we can allocated the memory..
			strcpy(*resultStr,inStr);					// Copy input into the resulting string.
			success = true;								// And that's a success!
		}														//
	} else {													// Else, they handed us a NULL string?
		resizeBuff(0,resultStr);						// I guess they want the result to be NULL as well.
		success = true;									// In that case, I guess we were successful.
	}															//
	return success;										// And we return our success. Good or bad.
}


void freeStr(char** resultStr) { resizeBuff(0,resultStr); }

