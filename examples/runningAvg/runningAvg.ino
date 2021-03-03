#include <runningAvg.h>

// A quick example of the runningAvg class. 

#define NUM_BYTES 20             // We'll have typed in numbers. We'll need a place to store what's being typed in.

runningAvg  theSmoother(10);     // Create a runningAvg object. In this case a 10 item data smoother.
char        inBuff[NUM_BYTES];   // A c string to hold the typed in numbers.
int         index = 0;           // Where in that c string we'll store the next incoming char.
   
void setup(void) { Serial.begin(9600); }


void loop(void) {

   char  aChar;
   float aNumber;
   float ave;
   
   if (Serial.available()) {                       // If we have an incoming char to read..
      aChar = Serial.read();                       // Grab it.
      if (aChar=='\n') {                           // If its a newline char. (Make sure the serial monitor is set to newline.)
         aNumber = atof(inBuff);                   // We decode what you typed in as a float. (Decimal number)
         index = 0;                                // Reset the index for the next number to be typed.
         ave = theSmoother.addData(aNumber);       // Pop this number into our smoother. (Running average object.) Out pops the average.
         Serial.println("----------------");       // From here on down we do our output stuff.
         Serial.print("Adding : ");                // Bla bla
         Serial.println(aNumber);                  // bla
         Serial.print("Ave = ");                   // bla..
         Serial.println(ave);                      //
         Serial.print("min = ");                   // You get the picture.
         Serial.println(theSmoother.getMin());     //
         Serial.print("max = ");                   // 
         Serial.println(theSmoother.getMax());
         Serial.print("delta = ");
         Serial.println(theSmoother.getDelta());
      } else if (index<NUM_BYTES-1) {              // Else, we just have a typed in char. And, we're not at the end of our string buffer.
         inBuff[index++] = aChar;                  // Add in the char we got & bump up the index for the next char.      
         inBuff[index] = '\0';                     // Pop in a trailing NULL to terminate the string here.
      }
   }
}
