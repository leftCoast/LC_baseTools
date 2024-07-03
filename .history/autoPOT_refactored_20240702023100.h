/*
#include <autoPOT.h>

autoPOT::autoPOT(int inPin) {
    callback = NULL;
    pinNum = inPin;
    value = -1;
}

autoPOT::~autoPOT() {}

void autoPOT::setCallback(void(*funct)(int)) {
    callback = funct;
    hookup();
}

void autoPOT::idle() {
    int newVal;
    if (callback) {
        newVal = analogRead(pinNum);
        if (newVal != value) {
            value = newVal;
            callback(value);
        }
    }
}

int autoPOT::getAverage(int numSamples) {
    int sum = 0;
    for (int i = 0; i < numSamples; i++) {
        sum += analogRead(pinNum);
    }
    return sum / numSamples;
}
*/