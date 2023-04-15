#ifndef serialStr_h
#define serialStr_h

#include <idlers.h>


//****************************************************************************************
// serialStr:
// serialStr is a quick and easy way to read complete c strings from the serial port. It
// runs in the background reading bytes from the serial port as they are available. When
// it finds the EOS char, typically the newline char '\n', it calls the user's callback
// function to deal with the string that has been read in.
//
// You will need to make a call to idle() in your main loop() function. And, as always,
// don't use delay(). That will stop everything.
//****************************************************************************************

#define DEF_BUFF_BYTES	64


class serialStr :  public idler {

   public:
               serialStr(Stream* inPort=&Serial,char endChar='\n',int numBytes=DEF_BUFF_BYTES);
   virtual     ~serialStr(void);

               //void  setCallback(void(*funct)(const char*)); // Use a callback for a complete string.
               void  setCallback(void(*funct)(char*)); // Use a callback for a complete string.
   virtual     void  idle(void);
               bool  hadOverrun(void);

               Stream*	port;
               int      index;
               char     EOL;
               int      bytes;
               char*    buff;
               //void     (*callback)(const char*);
               void     (*callback)(char*);
               bool     overrun;
};

#endif
