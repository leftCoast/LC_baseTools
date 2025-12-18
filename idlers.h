#ifndef idlers_h
#define idlers_h

#include <lists.h>

class idler : public linkListObj {

    public:
                idler(void);
    virtual    ~idler(void);

                void    hookup(void);
    virtual     void    idle(void);

                bool    hookedIn;
};


class idlers : public linkList {

    public:
                idlers(void);
    virtual    ~idlers(void);

                void	idle(void);
                void sleep(float ms);
};

extern  idlers  theIdlers;
extern  void    idle(void);
extern  void    sleep(float ms);
extern  bool    idling;

#endif