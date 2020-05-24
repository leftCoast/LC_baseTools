#ifndef idlers_h
#define idlers_h

#include "lists.h"

class idler : public linkListObj {

	public: 
  				idler(void);
  	virtual	~idler(void);

  				void	hookup(void);
	virtual	void	idle(void);

				bool	hookedIn;
};


class idlers : public linkList {

	public:
  				idlers(void);
	virtual	~idlers(void);

  				void	idle(void);
};

extern	idlers	theIdlers;
extern	void		idle(void);
extern	bool		idling;

#endif