#include <strTools.h>
#include <textBuff.h>
#include <lilParser.h>

textBuff    ourTextBuff(200); // The text ring buffer we want to test.
lilParser   ourParser(100);   // The parser that makes UI easy to whip up.

enum cmds {    // Our list of commands.
   noCommand,  // Always start with soething like no command.
   addChar,    // And then whatever you need.
   readChar,   //
   addStr,     //
   getStrLen,
   readStr,
   count,
   flush
};


void setup() {
   
   Serial.begin(9600);                       // Fire up serial port.
   delay(3000);                              // For my Mac. Takes a bit..
   showComs();                               // Display the serial commands.
   ourParser.addCmd(addChar,"add");          // Link commands to input strings.
   ourParser.addCmd(readChar,"read");        // link.
   ourParser.addCmd(addStr,"adds");          // link.
   ourParser.addCmd(getStrLen,"strlen");     // link.
   ourParser.addCmd(readStr,"reads");        // 
   ourParser.addCmd(count,"count");          // 
   ourParser.addCmd(flush,"flush");          // 
}


void loop() {
   
   char  inChar;
   int   command;

   if (Serial.available()) {                          // If serial has some data..
      inChar = Serial.read();                         // Read out a charactor.
      Serial.print(inChar);                           // If using development machine, echo the charactor.
      command = ourParser.addChar(inChar);            // Try parsing what we have.
      switch (command) {                              // Check the results.
         case noCommand    :                 break;   // Nothing to report, move along.
         case addChar      : doAddChar();    break;   // Add a char to the buffer.
         case readChar     : doReadChar();   break;   // Read a char from the buffer.
         case addStr       : doAddStr();     break;   // Add a string to the buffer.
         case getStrLen    : doGetStrLen();  break;   // Read the num chars for the next string.
         case readStr      : doReadStr();    break;   // Read a string from the buffer.
         case count        : doCount();      break;   // Return the count of items in the buffer.
         case flush        : doFlush();      break;   // Clear out and reset to empty.
         default           : showComs();     break;   // What? Makes no sense. Show them the list.
      }
   }
}


void showComs() {
   
   Serial.println();
   Serial.println("add\t- Add a char to the buffer.");
   Serial.println("read\t- Read a char from the buffer.");
   Serial.println("adds\t- Add a string to the buffer.");
   Serial.println("strlen\t- Read the num chars from the next string.");
   Serial.println("reads\t- tRead a string from the buffer.");
   Serial.println("count\t- Read the num chars in the queue.");
   Serial.println("flush\t- Clear out and reset to empty.");
   Serial.println();
}


void doAddChar(void) {

   char* param;
   
   if (ourParser.numParams()==1) {                    // If they typed in something past the command.
      param = ourParser.getNextParam();               // Grab that something.
      if (param) {                                    // If we got something..
         if (param[0]!='\0') {                        // If the first char isn't NULL char.
            ourTextBuff.addChar(param[0]);            // Then we add the first char to ourTextBuff.
            Serial.print(param[0]);                   // And tell the user we did that.
            Serial.println(" added to text buff");    // Still telling..
            return;                                   // Success bolt!
         }                                            //
      }                                               //
   }                                                  //
   Serial.println("Nothing to add?");                 // If we're here, we failed.
}


void doReadChar(void) {

   char  aChar;

   if (!ourTextBuff.empty()) {               // If ourTextBuff isn't empty..
      aChar = ourTextBuff.readChar();        // Pull out a char.
      Serial.println(aChar);                 // Show it to the user.
      return;                                // SUccess! Bolt!
   }                                         //
   Serial.println("Buffer is empty.");       // Or else the buffer was empty.
}


void doAddStr(void) {

   if (ourParser.numParams()>0) {                           // If they typed in something past the command.
      if (ourTextBuff.addStr(ourParser.getParamBuff())) {   // Add the entire param string to ourTextBuff.
         Serial.println("String added.");                   // Tell Miss user.
         return;                                            // Success, leave the party while your having fun.
      } else {                                              // Else something went wrong.
         Serial.println("Coudn't add the string.");         // Tell Miss user.
      }                                                     // 
   } else {                                                 // 
      Serial.println("So.. No string to add?");             // Miss user didn't give us a string.
      Serial.println("You just messin' about?");            //
   }                                                        //
}


void doGetStrLen(void) {

   Serial.print("Next string's number of chars is : ");     // We are going to..
   Serial.println(ourTextBuff.rStrlen());                   // Return the num chars of the next string.
}


void doReadStr(void) {

   char* aStr;
   int   numBytes;

   aStr = NULL;                                    // Start pointers at NULL please. 
   numBytes = ourTextBuff.rStrlen();
   if (numBytes) {
      if (heapStr(&aStr,ourTextBuff.readStr())) {
         Serial.print("The string [");
         Serial.print(aStr);
         freeStr(&aStr);
         Serial.println("]");
         return;
      } else {
         Serial.println("Not enough RAM!");
         return;
      }
   }
   Serial.println("No string!");
}


void doCount(void) {

   Serial.print("Itmes in queue : ");
   Serial.println(ourTextBuff.itemCount());
}


void doFlush(void) {

   ourTextBuff.flushItems();
   Serial.println("text buff has been flushed.");
}
