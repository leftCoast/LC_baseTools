#ifndef resizeBuff_h
#define resizeBuff_h

#include "Arduino.h"



//****************************************************************************************
//                   TOOLS FOR THOSE THAT DON'T FEAR DYNAMIC MEMORY
//               SO, IF YOU CAN'T STAND THE HEAT, GET OUT OF THE KITCHEN!
//****************************************************************************************


/*=============================================================================
 resizeBuff :

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

 Over and over. Then one day I wrote my first version of a "stretchy buffer" and that
 got me thinking.. Is there a way to generalize this idea?

 Hence : resizeBuff()

 As long as your buffer starts life allocated, or with a NULL. You can use this quick
 call to resize it as much as you like. And, it returns a boolean true or false as to if
 it was able to do it or not. Keeps you from writing into unallocated RAM as it were.

 NOTE: Resizing still means you loose whatever data was originally in it.

 Now its just..

 if (resizeBuff(newSize,&buffPtr)) {                     // Notice?
  do stuff..                                             // Address of the pointer there..
 }                                                       // Eww! So tricky!


 NOTE : Why a pointer to uint8_t?
 Originally this was setup at char* because it started with c strings. Then It started
 being used for binary data blocks. Then binary data blocks crossing over serial to
 other processors.. Word size stuff bit me in the.. Foot. uint8_t forced buffer sizes to
 match up.
==============================================================================*/

extern bool resizeBuff(int numBytes,uint8_t** buff);
extern bool resizeBuff(int numBytes,char** buff);
extern bool resizeBuff(int numBytes,void** buff);



/*=========================================================================================
 maxBuff :

 Lets say you need to write to something with, possibly, more data than you can allocate
 at one time? What to do? I ran into this issue when I found myself needing to transfer
 data from one file to another. The data could be WAY larger than the available RAM.
 And, as always, I was in a terrific hurry. So doing it byte by byte was not going to
 cut it. Hence, maxBuff.

 This class will start at your maximum desired buffer size and try allocating it. If
 that fails, it tries for half that size. Then 1/3 the size, 1/4.. Until either it
 succeeds in allocating a buffer, or, hits the buffer minimum size and gives up.

 On success :
 theBuff is the pointer to your allocated buffer.
 numBuffBytes is the size in bytes of that buffer.
 numPasses is the number of passes it will take to write/read your desired data.
 Meaning? This is how many time to call it in a for loop.

 On failure :
 theBuff will equal NULL.

 NOTE : This should be allocated as a local variable. Then on exit, it will recycle the
 buffer. Pretty slick huh?


 Here is an example from my code library of this in use, so you can see how it works.
 This is my file version of strcat(). Copies one file to the end of another.

 fcat() : The file version of strcat(). The dest file must be open for writing. The src
 file must be, at least, open for reading. (Writing is ok too) The dest file index is
 left pointing to the end of the file. The src file index is not changed.
 void fcat(File dest,File src) {

  unsigned long   filePos;
  maxBuff cpyBuff(src.size());
  unsigned long   numBytes;
  unsigned long   remaingBytes;

  dest.seek(dest.size());                                // Point at end of the dest file.
  filePos = src.position();                              // Lets save the file pos for miss user.
  src.seek(0);                                           // Point at first byte of the src file.
  remaingBytes = src.size();                             // Get the remaining bytes to copy.
  for (int i=0;i<cpyBuff.numPasses;i++) {                // For every pass through..
      numBytes = min(cpyBuff.numBuffBytes,remaingBytes); // Use buffer size or remaining bytes.
      src.read(cpyBuff.theBuff,numBytes);                // Fill the buffer.
      dest.write((char*)(cpyBuff.theBuff),numBytes);     // Write out the buffer.
      remaingBytes = remaingBytes - numBytes;            // Recalculate the remaining bytes.
  }                                                      //
  src.seek(filePos);                                     // Put it back like we found it.
 }

======================================================================================*/


#define BYTE_CUTOFF 20

class maxBuff {

    public:
                maxBuff(unsigned long numBytes,unsigned long  minBytes=BYTE_CUTOFF);
    virtual ~maxBuff(void);

                void*               theBuff;
                unsigned long   numBuffBytes;
                int             numPasses;
    };

#endif
