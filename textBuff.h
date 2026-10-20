#ifndef textBuff_h
#define textBuff_h

#include <Arduino.h>
#include <ringIndex.h>


//****************************************************************************************
// textBuff:
// Lets say you have something that streams out text and you need a place to store the
// stream before you can process it. This happens when hardware dumps data and you have no
// control over when and how much. This gives a place to stream all that text. Then you
// can read it back and deal with it at your leisure. You can even read it out as its
// being streamed in. Now that's pretty handy!
//****************************************************************************************


class textBuff : public ringIndex {

	public:
		textBuff(int inNumBytes,bool inOverwrite=false);
		~textBuff(void);
	
	virtual	bool  addChar(char inChar);									// Add a char.
	virtual	char  readChar(void);											// Read out the next char. (removes it)
				bool  addStr(const char* inCStr,bool andNULL=true);	// Add a c string. (With or without the nul terminator.)
				int	rStrlen(void);												// strlen() for the next string to read. Not counting the '\0'.
				char*	readStr(void);												// Read out a c string. (removes it)

	private:
		char*	buff;
		char*	returnStr;
		bool	overwrite;    
};

#endif