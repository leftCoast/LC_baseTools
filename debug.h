#ifndef debug_h
#define debug_h

#include "Arduino.h"
#include <RamMonitor.h>
#include <idlers.h>
#include <timeObj.h>


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


#ifdef RAM_MONITOR

class RAMMonitor :	public idler,
							public timeObj {

	public :
				RAMMonitor(float reportMs=500);
  virtual	~RAMMonitor(void);
  				
  				void begin(void);
  virtual	void reportRamStat(const char* aname, uint32_t avalue);
  virtual	void reportRam(void);
  virtual	void idle(void);
  
  				RamMonitor ram;
};

#endif //RAM_MONITOR
		
#endif