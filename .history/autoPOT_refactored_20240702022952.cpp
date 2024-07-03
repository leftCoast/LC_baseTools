/*
#ifndef autoPOT_h
#define autoPOT_h

class autoPOT {
public:
    autoPOT(int inPin);
    virtual ~autoPOT();
    void setCallback(void(*funct)(int));
    void idle();
    int getAverage(int numSamples = 1);

private:
    void(*callback)(int);
    int pinNum;
    int value;
    void hookup();
};

#endif
*/