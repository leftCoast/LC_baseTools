
#include "multiMap.h"
#include "mapper.h"

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
