
#include "multiMap.h"
#include "mapper.h"

/*
int pointCount = 0;
int multiMapCount = 0;
// ******************** mapPoint ********************


mapPoint::mapPoint(double inX, double inY)
	: linkListObj() {
	Serial.print("mapPoint() ");Serial.println(++pointCount);Serial.flush();
	mX = inX;
	mY = inY;
	mUpMapper = NULL;
}


mapPoint::~mapPoint(void) {

	Serial.print("~mapPoint() ");Serial.println(--pointCount);Serial.flush();
	if (mUpMapper) {			// Just in case we have a mapper..
		delete(mUpMapper);	// Recycle it!
		mUpMapper = NULL;		// Flag it as gone.
	}
}
	

mapPoint* mapPoint::getNext(void) { return (mapPoint*)linkListObj::getNext(); }


// This is to be called on the top point **after** sorting. 			
void mapPoint::createUpMappers(void) {

	mapPoint* upPoint;
	
	Serial.println("createMappers()");Serial.flush();
	if (mUpMapper) {															// Just in case, if we have a mapper.. (We shouldn't)
		Serial.println("Deleting a mapper.");Serial.flush();
		delete(mUpMapper);													// Recycle it first!
		mUpMapper = NULL;														// Flag it as gone.
	}
	upPoint = getNext();														// Make a grab for the upstream guy.
	if (upPoint) {																// If there is an upstream mapPoint.
		mUpMapper = new mapper(mX,upPoint->mX,mY,upPoint->mY);	//	Using ours and the upstream's info. Create a spaning mapper.
		Serial.println("Recurse!!");Serial.flush();
		upPoint->createUpMappers();										// We tell the upstream guy to do it to.
		Serial.println("Pop!!");Serial.flush();
	}
}


// Are we greater than the obj being passed in? Primary sorting function.
bool mapPoint::isGreaterThan(linkListObj* compPoint) {

	mapPoint* compPtr;
	Serial.println("isGreaterThan");Serial.flush();
	compPtr = (mapPoint*) compPoint;
	return mX > compPtr->mX;
}


// Are we less than the obj being passed in? Primary sorting function.
bool mapPoint::isLessThan(linkListObj* compPoint) {

	mapPoint* compPtr;
	Serial.println("isLessThan");Serial.flush();
	compPtr = (mapPoint*) compPoint;
	return mX < compPtr->mX;
}


// This is to be called **after** the link list has been sorted and mappers have been created.
double  mapPoint::map(double inX) {

	mapPoint* next;
	
	if (inX<=mX) return mY;						// If its less than our x? Then we are the low limit. Return our y value.
	next = getNext();								// Make the grab for the next bigger point.
	if (next) {										// If there is a larger point..
		if (inX>mUpMapper->getMaxX()) {		// If its larger than our mapper's limit..
			return next->map(inX);				// Pass the x value to the next larger point. Return it's result.
		} else {										// Else, its larger than us and less than the limit..
			return mUpMapper->map(inX);		// We map it and return the result.
		}
	} else {											// Else. its larger than us, but no next guy to pass it to.
		return mY;									// We are the larger limit. return our y value.
	}
}


// ******************** multiMap ********************


multiMap::multiMap(void)
	: linkList() { mReady = false; }
	
	
multiMap::~multiMap(void) { }


void multiMap::addPoint(double x, double y) {

	mapPoint*	newPoint;
	Serial.println("addPoint()");Serial.flush();
	newPoint = new mapPoint(x,y);
	if (newPoint) {
		addToTop(newPoint);
		sort(false);
		mReady  = false;
	}
}


void multiMap::clearMap(void) {

	dumpList();
	mReady  = false;
}


mapPoint* multiMap::getFirst() { return (mapPoint*) getFirst(); }


double multiMap::map(double inX) {
	
	mapPoint* first;
	
	if (!isEmpty()) {									// If we have points..
		if (mReady) {									// If we are ready (Sorted with mappers)
			first = getFirst();
			if (first) {
				return first->map(inX);				// Return the resulting mapped value;
			} else {
				return 0;
			}
		} else {											// Else, not ready?
			//sort(false);								// Sort the list.
			first = getFirst();
			if (first) {
				first->createUpMappers();	// Create new set of mappers.
				mReady = true;							// Note we open for business!
				return first->map(inX);				// Return the mapped result.
			} else {
				return 0;
			}						
		}
	}
	return 0;											// Mrs user is all screwed up. Return a zero.
}


// Legacy..
double  multiMap::Map(double inX) { return map(inX); }


double  multiMap::integrate(double x1,double x2,double c) { return 0; }

*/
mapper mapItemMppr(1,2,1,2);


mapItem::mapItem(double inX, double inY) {

  x = inX;
  y = inY;
  lessItem = NULL;
  greaterItem = NULL;
}


mapItem::~mapItem(void) {     // Time to die. If your in a list, remove yourself.

  if (lessItem!=NULL) // Have a "less" item.
    lessItem->greaterItem = greaterItem;
  if (greaterItem!=NULL) // Have a greater item.
    greaterItem->lessItem = lessItem;
  lessItem = NULL;
  greaterItem = NULL;
  // Our work is done here..
}


void mapItem::setValues() {

  if (lessItem!=NULL) {
    mapItemMppr.setValues(lessItem->x,x,lessItem->y,y);
    slope = mapItemMppr.getSlope();
    intercept = mapItemMppr.getIntercept();
  }
}


bool mapItem::linkIn(mapItem* itemPtr) {

  if (itemPtr==NULL)                         // Sanity, is there a list?
    return false;
  if (itemPtr->x == x)                       // Duplicates are NOT allowed!
    return false;
  if (itemPtr->x < x) {                      // Ok, we belong on the greater side..
    if (itemPtr->greaterItem!=NULL) {        // There is a greater one..
      return linkIn(itemPtr->greaterItem);   // Do the recursive jump.
    }
    else {                                   // There is no one on greater side..
      lessItem = itemPtr;                    // Link in to end of list here.
      lessItem->greaterItem = this;
      setValues();
      return true;
    }
  } 
  else {                                     // We belong on the less side..
    if (itemPtr->lessItem!=NULL) {           // There is a lesser one..
      if (itemPtr->lessItem->x<x) {          // This is our spot!
        lessItem = itemPtr->lessItem;
        greaterItem = itemPtr;
        lessItem->greaterItem = this;
        greaterItem->lessItem = this;
        setValues();
        greaterItem->setValues();
        return true;
      } 
      else                                  // We are NOT greater than the less item..
      return linkIn(itemPtr->lessItem);     // Do the recursive jump down.
    } 
    else {                                  // There is no lesser one. And we are smaller..
      greaterItem = itemPtr;
      itemPtr->lessItem = this;
      setValues();
      greaterItem->setValues();
      return true;
    }
  }
}


double mapItem::Map(double inVal) {  // We need to find the correct mapper and map this value.

  if (inVal == x)                      // Hey its us!
    return (y);                        // Pass back our y value.
  if (inVal>x) {                       // inVal is greater than us.
    if (greaterItem!=NULL)             // Fine, if there's a greaterItem -
      return greaterItem->Map(inVal);  // Pass it up the line.
    else                               // Oh! We are the top of the line..
    return(y);                         // Again, pass back our y value.
  } 
  else {                               // inVal is less than us..
    if (lessItem==NULL)                // We are the smallest and inVal's smaller?
      return(y);                       // Again, pass back our y value.
    else {                             // inVal's less than us, and there is someone down there..
      if (lessItem->x>inVal)            // inVal is less than the smaller guy -
        return lessItem->Map(inVal);      // Pass it down the line.
      else {                            // inVal is less than us but not less than the smaller guy?
        return doMap(inVal);             // This one we can map!       
      }
    }
  }
}   


double mapItem::doMap(double inVal) {  // We have been choosen to map this value.

  if (inVal < lessItem->x)
    inVal = lessItem->x;
  else if (inVal > x)
    inVal = x;
  return(slope*inVal+intercept);
}


/*
void mapItem::outputItem() {

  Serial.print(F("x = "));
  Serial.print(x);
  Serial.print(F(", y = "));
  Serial.println(y);
}
*/

// ***********************

multiMap::multiMap() {

  itemList  = NULL;
}


multiMap::~multiMap(void) {

  clearMap();
}


void multiMap::addPoint(double x, double y) {

  mapItem* newItem;
  newItem = new mapItem(x,y);          // Whip up a fresh item.
  if (itemList == NULL) {             // Look its the first one!
    itemList = newItem;  
  } 
  else {
    if (newItem->linkIn(itemList)) {  // We were successful at linking this in?
      while(itemList->lessItem!=NULL)  // Make sure we point at the smaller end.
        itemList = itemList->lessItem;
    } 
    else {
      delete(newItem);                // Not succesfull at linkin in the new item? Recycle it.
    }
  }
}


void multiMap::clearMap(void) {

  if (itemList!=NULL) {
    while(itemList->greaterItem!=NULL)
      delete(itemList->greaterItem);
    while(itemList->lessItem!=NULL)
      delete(itemList->lessItem);
    delete(itemList);
    itemList = NULL;
  } 
}


double multiMap::Map(double inVal) {

  if (itemList!=NULL)              	// If we have mappers..
    return itemList->Map(inVal);   	// Map that item!
  else                             	// What the heck? We have no mappers at all?
  return 0;                      	// I guess zero is the best we can do here.
}

/*
void multiMap::outputList(void) {

  mapItem* trace;

  if (itemList!=NULL) {           // If we have mappers..
    trace = itemList;
    while(trace!=NULL) {
      trace->outputItem();
      trace = trace->greaterItem;
    } 
  } 
  else  {                           // What the heck? We have no mappers at all?
    Serial.println(F("Empty"));
  }
}
*/

