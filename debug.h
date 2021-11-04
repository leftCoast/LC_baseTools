#ifndef debug_h
#define debug_h

#include "Arduino.h"


class debug {

  public :
                debug(void);
  virtual       ~debug(void);
  
				void  trace(char* message,bool hold=true);
				void  trace(char* message,int inNum,bool hold=true);
				void  trace(char* message,char* inStr,bool hold=true);
};

extern debug db;
#define ST db.trace(__func__,false);

#endif