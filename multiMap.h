#ifndef multiMap_h
#define multiMap_h


#include "mapper.h"

// 6/19/2020 : Backed out the multiMap changes. So for now? We'll see.

/*

#include "lists.h"


class mapPoint :	public linkListObj {

	public :
  				mapPoint(double inX, double inY);
	virtual	~mapPoint(void);
	
				mapPoint*	getNext(void);
				void			createUpMappers(void);
	virtual	bool			isGreaterThan(linkListObj* compPoint);	// Are we greater than the obj being passed in? Primary sorting function.
   virtual	bool			isLessThan(linkListObj* compPoint);		// Are we less than the obj being passed in? Primary sorting function.
   			double		map(double inX);
   			
   private:			
				double	mX;
				double	mY;
				mapper*	mUpMapper;
};


class multiMap :	public linkList {

	public:
	
				multiMap(void);
	virtual	~multiMap(void);

				void			addPoint(double x, double y);
  				void			clearMap(void);
  				double		map(double inVal);
  				double		Map(double inVal);
  				double		integrate(double x1,double x2,double c);
  	private:
  	
  	virtual	mapPoint*	getFirst();
  	
  				bool	mReady;
};
*/


class mapItem {

	public :
  				mapItem(double inX, double inY);
	virtual	~mapItem(void);

  				void		setValues(void);
  				bool		linkIn(mapItem* itemPtr);
  				double	Map(double inVal);
  				double	doMap(double inVal);
  				//void	outputItem(void);

  				double	x;
  				double	y;
  				double	slope;
  				double	intercept;
  				mapItem*	lessItem;
  				mapItem*	greaterItem;
};


class multiMap {

	public:
				multiMap(void);
	virtual	~multiMap(void);

  				void		addPoint(double x, double y);
  				void		clearMap(void);
  				double	Map(double inVal);
  				//void outputList(void);
  				
	private :
  				mapItem*	itemList;
};

#endif


