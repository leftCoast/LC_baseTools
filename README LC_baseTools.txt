LC_baseTools

This is a handy grab bag of tools I'd found I needed and used again and again while writing code for Arduinos. Some roots of this kit date back to the Macintosh code development days. Some to Banderlog. For example, Multimapper was originally written to enter & interpret RPM profiles for Drag Boat engines.


www.leftcoast.biz 

Left Coast is where this came from. Use it all you want. I'd be nice if Left Coast got some credit for it.


Lets start with..



***
timeObj
***

timeObj is essentially an egg timer. Or, the timer you find on a microwave oven these days. Set a time and listen for the "ding" sound.

To use it, create one.

timeObj myTimer(Ms); // Ms is how long, in milliseconds  you'd like to wait. example 55.5

Now you can go of and do whatever you'd like to do in your program and when you're curious you can look at your time object to see if its expired or not.

if (myTimer.ding()) {
	//do something cause the timer went off
}

There's some other handy calls you can make.

myTimer.start();  // Start the timer NOW. Clear whatever it was doing and start timing.

myTimer.setTime(Ms); // Change the duration and restart NOW.
myTimer.setTime(Ms, maybeStart); // Change the duration and restart if maybeStart is true.

myTimer.stepTime();  // Sets up the timer for the next "ding" from the last "ding".. Removes latency.

NOTE : Timer deals with the issue of the microsecond clock crossing zero as well.



***
mapper
***

Mapper objects are used to map a range of value to another range of values. They are used for things like…

Assume you know your analog input swings from say..  127..963 and this corresponds to -26.3..47.02 degrees C.

mapper myMapper(127,963,-26.3,47.02); // This creates your mapper object.


int val = analogRead(analogPin);      // read the input pin
float degrees = myMapper.Map(val);    // Now you have that value in degrees as a float.

If your input is below the mapped range? The mapper returns the result of the lowest input possible.

If you input is above the mapped range?   The mapper returns the result of the highest input possible.

Other calls for the mapper object.

myMapper.setValues(x1,x2,y1,y2);     // Reset the mapper to a new set of values.

slope = myMapper.getSlope();         // Internally it is a line function. Want the values?
minX = myMapper.getMinX(void);
maxX = myMapper.getMaxX(void);
yintercept = myMapper.getIntercept(void);

void myMapper.printMap(void);        // For debugging. Outputs to current Serial port.


NOTE : Mappers do as much calculation as possible when they are set up. This is in hopes of making things run a little bit faster.

NOTE : Mappers were developed in the desktop computer world, so they call for doubles. I KNOW the Arduino only has floats. The compiler deals with it, so I left them that way.



***
multiMap
***

First see mapper above ^^^s. Grok that it will map one range of value to another given the end points of both sets. Now, keeping this in mind..

What if the function between your input values and your mapped output values is not a straight line? This is what the multiMap object is for.

To set it up, you just create one.

multiMap myMultiMapper;

Now you will want the points that define your curve to a good enough approximation. Many times its a table of X,Y pairs. This is perfect if it is because this is how you set up your multiMapper.

thingX  thingY
0       0
6       25.7045
49      51.375
64      0
67      0


Add your points..

myMultiMapper.addPoint(0,0);
myMultiMapper.addPoint(6,25.7045);
myMultiMapper.addPoint(49,51.375);
myMultiMapper.addPoint(64,0);
myMultiMapper.addPoint(67,0);

Now, any value in thingX will map to a corresponding value in thingY.

float result = myMultiMapper.Map(23.5); // For example


Other multiMap calls.

myMultiMapper.clearMap();   // Does just what it says and clears all the point data out.
myMultiMapper.outputList(); // For debugging will Dump the contents to the current Serial port.


NOTE : multiMap objects do no curve fitting or smoothing at all. Just liner interpretations from point to point. Its up to you to make sure that the error between the liner approximation and the theoretical curve is within tolerance.



***
lists
***

Lists contains a set of objects for managing linked lists. These are kind of like arrays that are dynamic in their size. They can grow or shrink as you add or delete bits. They can represent things like stacks & queues. If you've never worked with linked lists, don't worry. You may not need to directly use them. But, the rest of the library uses them so they need to be here as a toolkit.

Quickly, what we have here..



***
class linkListObj - Your basic node that can link itself into a single linked list. 
***


linkAfter(linkListObj* present);       // Given a pointer to a node, link yourself after it.

void linkToEnd(linkListObj* present);  // Given a pointer to a node, link yourself after the last in the chain.



***
class linkList - This is the managing class for a list of linkListObj objects.
***

To use, create the object..


linkList myList(true);  // I'm telling the list that once I hand a linkListObj to it. Its responsible to dispose of it. false means I'll deal with disposing of it.

To add something..

linkListObj* someObjPtr;		// Define a pointer..

someObjPtr = new linkListObj();  // Create the object..


mlinkList.addToTop(someObjPtr);  // You can add it to the top or..

mlinkList.addToEnd(someObjPtr);  // You can add it to the end..

Knocking objects out of your list. Remember, if YOU own them, YOU need to deal with deleting them. If you don't, you leak memory all over. This is why its default to letting the list own them. Then they just go away without leaking memory.

myList.deleteFromTop();        // Unlinks the top object. If it owns it, it'll delete it for you.

myList.deleteObj(someObjPtr);  // If found, it unlinks it. Deletes it, if it owns it.

gotNuthin = myList.isEmpty();  // Lets us know if its empty or not. true == empty.

myList.dumpList();             // Unlinks everything. Deletes everything if it owns them.

someObjPtr = myList.getList(); // Gives back the pointer to the top object.



***
class stack - Your basic dynamic stack representation.
***

Stack objects force the issue that they own the objects they contain. So you create the obects and when you "pop" them off the stack the stack will delete them for you.


To use, create one..

stack mStack;


To add objects create them..

linkListObj* someObjPtr;         // Define a pointer..
someObjPtr = new linkListObj();  // Create the object..

mStack.push(someObjPtr); 	     // And push it onto the stack.

mStack.pop();      	             // Deletes the last one you pushed in.
    
linkListObj = mStack.top();      // Passes back the last object pushed in.

mStack.dump();                   // This deletes everything.

gotNuthin = mStack.empty();      // Passes back true for empty.



***
class queue - Your basic dynamic queue representation.
***

Queue objects force the issue that they own the objects they contain. So you create the objects and when you "pop" them off the queue the queue will delete them for you.


To use, create one..

queue mQueue;


To add objects create them..

linkListObj* someObjPtr;         // Define a pointer..
someObjPtr = new linkListObj();  // Create the object..

mQueue.push(someObjPtr); 	     // And push it onto the stack.

mQueue.pop();      	             // Deletes the oldest pushed in.
    
linkListObj = mQueue.top();      // Passes back the oldest object pushed in.

mQueue.dump();                   // This deletes everything.

gotNuthin = mQueue.empty();      // Passes back true for empty.



*** idlers ***

Idlers let your Arduino act like its multi threaded. There are two classes in idlers.



***
idlers
***

You can pretty much ignore idlers because, all it does is setup the framework to list all the different idlers and gives you the call idle(); to put in your loop() function.

How to use?

void loop() {

   idle();
   //do your stuff..
}

That's it. BUT! Now everything that was based on the idler class has just spent some time doing whatever they do.



***
idler
***

When you create a class that you would like to run in the background, inherit from idle and it will.

For example, from my blinker class..

class blinker : public idler, timeObj {

   bla bla bla..
   
   virtual void idle(void);  // What to do in our spare time?
   
   more bla bla bla..

};


When you inherit from idler you get the idle function so you can fill it out to do something. In the blinker class it checks the timer to see if the time is up. If so? Switches the state of the LED and restarts the timer.

Suddenly you have as many blinking LEDs as you have pins to blink EM. 

hookup(); // This hooks your idler class up so it gets idle time to do things.

NOTE : One thing you need to do when you inherit idler is to make a call from your class to hookup(); And, sadly, this can't be in the constructor. This is a one time call. The idea was to have it in the constructor so you wouldn't need to deal with it, but the complier didn't work with that.


That's it, inherit idler in your class, fill in the idle() function with your tasks and make sure hookup is called one time at the start of everything. Like in the setup() funtion.



***
blinker - NO BLOCKING
***

Well, since we already met blinker, here you go. This is just a simple class to blink an LED in the background. I use it just to let me know that the main loop() is still running.

blinker mBlinker;

void setup(void) {

   mBLinker.setBlink(true); // turns it on..
}

void loop(void) {

	idle();
	// Do my stuff
}

That's all there is to it.

Other setups..

mBlinker(Pin);                    // Set the pin when allocating. Default is pin13
mBlinker(inPin,OnMs);             // Set the pin and how long the blink is.
blinker(inPin,inOnMs,inPeriodMs); // How long the period is from blink through blink.



***
PulseOut - SOME BLOCKING
***

PulseOut is for creating a quick and dirty square wave. The period is run by a timerObj and the pulse, where the pin goes high, is run by sitting in a while loop. I know, bad bad, but it works and if your in a hurry and you don't want to deal with mucking about with chip stuff, sometimes this works just fine.

pulseOut myPWM(inPin,inPeriod); // This creates the object. Pin number and Period in milliseconds.


myPWM.setWidth(inWidth);	    // This sets the on time of the pulse in milliseconds.

When you call your idle(); function in your main loop(), it'll run in the background for you. You can call myPWM.setWidth(inWidth); any time.

