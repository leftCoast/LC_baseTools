#ifndef multiMap_h
#define multiMap_h


#include "lists.h"
#include "mapper.h"


class mapPoint :   public linkListObj {

   public :
            mapPoint(double inX, double inY);
   virtual  ~mapPoint(void);
   
            mapPoint*   getNext(void);
            void        createUpMappers(void);
   virtual  bool        isGreaterThan(linkListObj* compPoint); // Are we greater than the obj being passed in? Primary sorting function.
   virtual  bool        isLessThan(linkListObj* compPoint);    // Are we less than the obj being passed in? Primary sorting function.
            double      map(double inX);
            double      integrate(double x1,double x2);
   private:       
            double   mX;
            double   mY;
            mapper*  mUpMapper;
};


class multiMap :  public linkList {

   public:
   
            multiMap(void);
   virtual  ~multiMap(void);

            void        addPoint(double x, double y);
            void        clearMap(void);
            double      map(double inVal);
            double      Map(double inVal);
            double      integrate(double x1,double x2);
   
   private:
            mapPoint*   getFirst();
            bool        setUp(void);
            
            bool  mReady;
};


#endif
