
#include <multiMap.h>



//****************************************************************************************
// mapPoint :
//****************************************************************************************


mapPoint::mapPoint(double inX, double inY)
   : linkListObj() {

   mX = inX;
   mY = inY;
   mUpMapper = NULL;
}


mapPoint::~mapPoint(void) {

   if (mUpMapper) {                                        // Just in case we have a mapper..
      delete(mUpMapper);                                   // Recycle it!
      mUpMapper = NULL;                                    // Flag it as gone.
   }
}


mapPoint* mapPoint::getNext(void) { return (mapPoint*)linkListObj::getNext(); }


// This is to be called on the top point **after** sorting.
void mapPoint::createUpMappers(void) {

   mapPoint* upPoint;

   if (mUpMapper) {                                        // Just in case, if we have a mapper.. (We shouldn't)
      delete(mUpMapper);                                   // Recycle it first!
      mUpMapper = NULL;                                    // Flag it as gone.
   }
   upPoint = getNext();                                    // Make a grab for the upstream guy.
   if (upPoint) {                                          // If there is an upstream mapPoint.
      mUpMapper = new mapper(mX,upPoint->mX,mY,upPoint->mY);// Using ours and the upstream's info. Create a spaning mapper.
      upPoint->createUpMappers();                          // We tell the upstream guy to do it to.
   }
}


// Are we greater than the obj being passed in? Primary sorting function.
bool mapPoint::isGreaterThan(linkListObj* compPoint) {

   mapPoint* compPtr;

   compPtr = (mapPoint*) compPoint;
   return mX > compPtr->mX;
}


// Are we less than the obj being passed in? Primary sorting function.
bool mapPoint::isLessThan(linkListObj* compPoint) {

   mapPoint* compPtr;

   compPtr = (mapPoint*) compPoint;
   return mX < compPtr->mX;
}


// This is to be called **after** the link list has been sorted and mappers have been
// created.
double  mapPoint::map(double inX) {

   mapPoint* next;

   if (inX<=mX) return mY;                                 // If its less than our x? Then we are the low limit. Return our y value.
   next = getNext();                                       // Make the grab for the next bigger point.
   if (next) {                                             // If there is a larger point..
      if (inX>mUpMapper->getMaxX()) {                      // If its larger than our mapper's limit..
         return next->map(inX);                            // Pass the x value to the next larger point. Return it's result.
      } else {                                             // Else, its larger than us and less than the limit..
         return mUpMapper->map(inX);                       // We map it and return the result.
      }
   } else {                                                // Else. its larger than us, but no next guy to pass it to.
      return mY;                                           // We are the larger limit. return our y value.
   }
}


// Just like map() above, this is to be called **after** the link list has been sorted and
// mappers have been created.
double  mapPoint::integrate(double x1,double x2) {

   if (mUpMapper) {                                        // Sanity, we have mappers? And, this also means we have an upper neighbor point.
      if (x1<=mUpMapper->getMinX()) {                      // If x1 is our end point or below..
         if (x2==mUpMapper->getMaxX()) {                   // If x2 is at our end point.
            return mUpMapper->integrate();                 // We return the complete integraton of our mapper.
         } else {                                          // Else, not equal.
            if (x2<mUpMapper->getMaxX()) {                 // If x2 is less than our end point..
               return mUpMapper->integrate(x1,x2);         // We return the partial integraton of our mapper.
            } else {                                       // Else, x2 goes beyond our mapper..
               return mUpMapper->integrate() + getNext()->integrate(x1,x2);// We return our total integration + The integration of next guy upstram of us.
            }
         }
      } else if (x1>=mUpMapper->getMaxX()) {               // Else if x1 is beyond us altogether.
         return getNext()->integrate(x1,x2);               // We pass it on to the next guy and return when he returns.
      } else {                                             // Else x1 lies within our mapper.
         if (x2<=mUpMapper->getMaxX()) {                   // If x2 lies within our mapper..
            return mUpMapper->integrate(x1,x2);            // We retun our partial integrtion.
         } else {                                          // Else, x2 is beyond our mapper..
            return mUpMapper->integrate(x1,x2) + getNext()->integrate(x1,x2);// We return our partial integration + The integration of next guy upstram of us.
         }
      }
   } else {                                                // Else, we have no mapper or neighbor upstram of us.
      return 0;                                            // Then there is no area under our line segment, we have no line segment.
   }
}



//****************************************************************************************
// multiMap :
//****************************************************************************************


// Create a new empty multi map.
multiMap::multiMap(void)
   : linkList() { mReady = false; }


// recycle everything.
multiMap::~multiMap(void) { }


// Add a new datapoint to a curve.
void multiMap::addPoint(double x, double y) {

   mapPoint*   newPoint;

   newPoint = new mapPoint(x,y);
   if (newPoint) {
      addToTop(newPoint);
      mReady  = false;
   }
}


// Dump and recycle everything in this map.
void multiMap::clearMap(void) {

   dumpList();
   mReady  = false;
}


// Want the first point? This'll hand it to you.
mapPoint* multiMap::getFirst() { return (mapPoint*) linkList::getFirst(); }


// Clean up any previous setups, sort out all the current points and get things ready for
// mapping. (Or integrations)
bool multiMap::setUp(void) {

   mReady = false;                                         // Well, they called us, assume its not ready.
   if (!isEmpty()) {                                       // If we have a list of points.
      sort(true);                                          // Sort the list.
      getFirst()->createUpMappers();                       // Create new set of mappers.
      mReady = true;                                       // Note we open for business!
   }
   return mReady;                                          // Return our result.
}


// Meat and potatoes, what we live for. Give us a value and we'll map it to the curve.
double multiMap::map(double inX) {

   if (!isEmpty()) {                                       // If we have points..
      if (mReady) {                                        // If we are ready (Sorted with mappers)
         return getFirst()->map(inX);                      // Return the resulting mapped value;
      } else {                                             // Else, we are not ready..
         if (setUp()) {                                    // If we can get ready..
            return getFirst()->map(inX);                   // Return the mapped result.
         }
      }
   }
   return 0;                                               // Mrs user is all screwed up. Return a zero.
}


// Well, since you asked nice. We CAN actually do integration over your inputted curve.
double  multiMap::integrate(double x1,double x2) {

   if (!isEmpty()) {                                       // If we have points..
      if (mReady) {                                        // If we are ready (Sorted with mappers)
         return getFirst()->integrate(min(x1,x2),max(x1,x2));// Return the integration result;
      } else {                                             // Else, we are not ready..
         if (setUp()) {                                    // If we can get ready..
            return getFirst()->integrate(min(x1,x2),max(x1,x2));// Return the integration result.
         }
      }
   }
   return 0;                                               // Mrs user is all screwed up. Return a zero.
}
