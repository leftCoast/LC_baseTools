# LC_baseTools
## Tools to make programming Arduinos easier.

 ![alt text](https://github.com/leftCoast/Arduino/blob/master/libraries/LC_icons/icons/standard/warn32.bmp) **DO NOT GRAB  THESE FILES OUT OF THE REPOSITORY. NINE TIMES OUT OF TEN, THEY WILL NOT COMPILE FOR YOU. INSTALL THESE USING THE ADRUINO IDE LIBRARY MANAGER. AND DON'T EVEN THINK OF TRYING THE .ZIP FILES! WHY DO THEY EVEN HAVE THOSE? I JUST DON'T KNOW..**

- **blinker** - *Blinks an LED without using delay(). On any output pin. Does NOT use interrupts or hardware PWM. [Example](examples/auto_blinkers)*

- **colorObj** - *Used for everything dealing with colors. Storing, translating, passing from computer to hardware and back. Blending, linear and non-linear color mapping.*

- **idlers** - *Contains the idler class used to make objects that function in the background. Also includes the support code to make this happen automatically.*

- **lists** - *Base classes of dynamic linked lists that everything in the LC libraries are based on. Linked Lists, double linked lists, stack and queue.*

- **mapper** - *Linear mapper function. Unlike the Arduino version, this uses doubles as input and output. It also saves as much of the calculation as possible between mapping calls.*

- **mechButton** - *Class that creates a debounced button. Has three possible user levels : Beginner - Simple polling, Intermediate - Use callbacks. and Pro - Use as a base class to create wild new custom actions.* [Example](examples/mechButton_Beginner)

- **autoPOT** - *Class that creates a automatic analog pin reader. Uses a callback to alert the user when the value changes.*

- **multiMap** - *Non-linear mapping function. Starts out blank and the user adds x,y points to it before use.*

- **resizeBuff** - *Simplified memory management. Initialize your pointers to NULL then resizeBuff() can allocate and deallocate your dynamic buffer space for you. Passes back true for successful allocations, false for unsuccessful. Saves a lot of code typing. Now includes maxBuff. This is a stack based class that allocates the largest buffer it can for passing large chunks of data. Like copying one file to another. Also returns the number of data hauls that wil be necessary for the data to be transffered. Makes this kind of operation very simple.*

- **runningAvg** - *Running average data smoother. Pop in a number, and out popes the average of the last n numbers inputted. Does statistical stuff as well. [Example](examples/runningAvg)*

- **serialStr** - *Create a serialStr object and give it a callback function. Now complete c strings will magically show up from the serial port at your callback for you to process. [Example](examples/serialStr)*

- **squareWave** - *Base class for creating objects that are based on square waves. IE. blinking lights, flashing text, RC servo signals. Does NOT use interrupts or hardware PWM. Runs in background.*

- **strTools** - *A grab bag of c string tools. upCase(), lwrCase(). Pass in a c string and they will make all the letters either uppercase or lower case. heapStr(), freeStr(). Pass in the address of a* **char** *and a source c string. This will store a copy of the source to the char*. freeStr() will recycle the*  char's  *RAM. tempStr is a stack based class designed to hold local copies of passed in c strings. Automatically recycles its RAM when going out of scope.*

- **textBuff** - *Ring buffer for text. Handy for hardware that can pass in a lot of text at random times that you need to process.*

- **timeObj** - *A timer that takes a Ms input as a float. Then it can be queried to tell when this timespan has expired. Takes care of roll over issues as well. Very handy for getting away from delay(). Set a timer, and let loop() run. When it expires, do your thing.*
