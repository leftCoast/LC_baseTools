#include "debug.h"
#include <resizeBuff.h>


debug::debug(void) { }
debug::~debug(void) { }

void debug::trace(char* message,bool hold) {

  Serial.print(message);
  Serial.flush();
  if (hold) {
    while(!Serial.available());
    Serial.read();
  }
  Serial.println(); 
}


void debug::trace(char* message,char* inStr,bool hold) {

	Serial.print(message);
	trace(inStr,hold);
}

	
void debug::trace(char* message,int inNum,bool hold) {

  char* buff;
  int   numChars;
  
  buff = NULL;
  numChars = strlen(message);
  if (resizeBuff(numChars+10,&buff)) {
    strcpy(buff,message);
    snprintf(&(buff[numChars]),9,"%d",inNum);
    trace(buff,hold);
    resizeBuff(0,&buff);
  } else {
    Serial.println(F("NO RAM!!"));
  }
}


debug db;

#ifdef RAM_MONITOR

// ******************************************
// *************** RAMMonitor ***************
// ******************************************


RAMMonitor::RAMMonitor(float reportMs)
	: idler(),
	timeObj(reportMs) {  }


RAMMonitor::~RAMMonitor(void) {  }

  
void RAMMonitor::begin(void) {

	ram.initialize();
	hookup();
}


void  RAMMonitor::reportRamStat(const char* aname, uint32_t avalue) {

  Serial.print(aname);
  Serial.print(": ");
  Serial.print((avalue + 512) / 1024);
  Serial.print(" Kb (");
  Serial.print((((float) avalue) / ram.total()) * 100, 1);
  Serial.println("%)");
}


void  RAMMonitor::reportRam(void) {
  
	bool lowmem;
	bool crash;

	Serial.println("==== memory report ====");

	reportRamStat("free", ram.adj_free());
	reportRamStat("stack", ram.stack_total());
	reportRamStat("heap", ram.heap_total());

	lowmem = ram.warning_lowmem();
	crash = ram.warning_crash();
	if(lowmem || crash) {
		Serial.println();
		if(crash)
			Serial.println("**warning: stack and heap crash possible");
		else if(lowmem)
			Serial.println("**warning: unallocated memory running low");
	}
	Serial.println();
}


void RAMMonitor::idle(void) {

	if(ding()) {
		start();
		reportRam();
	}  
	ram.run();
}

#endif //RAM_MONITOR
