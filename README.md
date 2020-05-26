## LC_baseTools
Tools to make programming Arduinos easier.

# blinker
blinks an LED without using delay(). Or any output pin for that matter. Does NOT use interrupts or harware PWM.

# colorObj
Used for everything dealing with colors. Storing, translating, passing from computer to hardware and back. Blending, Liner and non-liner color mapping.

# debug
Grab bag of debugging tools. Includes ST (Stack trace). Put ST at the start of a function. Then, that function's name prints on the serial monitor when exicuted.

# idlers
Contains the idler class used to make objects that function in the background. Also includes the support code to make this happen automatically.

# lists
Base classes of dynamic linked lists that everything in the LC libraries is basied on. linkList, double linkList, stack and queue.

# mapper
Liner mapper function. Unlike the Arduino version, this uses doubles as input and output and samve as much of the calculation as possible between mappong calls.

# mechButton
class that creates a debounced button. It works, its in need of a rewrite.

# multiMap
Non-liner mapping function. Starts out blank and the user adds x,y points to it before use.

# resizeBuff
Simplified memory management. Initialize your pointers to NULL then resizeBuff() can allocate and dealocate your dynamic buffer space for you. Passes back true for successful allocations, false for unsiccessful. Saves a lot of code typing.

# runningAvg
Running avarage data smoother. Pop in a number, and out poppes the avarage of the last n numbers inputted.

# squareWave
Base class for creating thigs that are basied on square waves. IE blinking lights, flashing text, RC servo signals. Does NOT use interrupts or harware PWM. Runs in background.

# textBuff
Ring buffer for text. Handy for hardware that can pass in a lot of text at random times that you need to process.

# timeObj
A timer that takes a float Ms input and can tell the user when it has expired. Takes care of roll over issues as well. Very handy for getting away from delay(). Set a timer and let loop() run. When it expires, do your thing.
