#ifndef FINGERS_H
#define FINGERS_H

#include <Arduino.h>

class Fingers {
public:
    Fingers(int thumbPin, int indexPin, int middlePin, int ringPin, int pinkyPin);
    void setupFlexSensors();
    void readFlexSensors();

private:
    int thumbPin;
    int indexPin;
    int middlePin;
    int ringPin;
    int pinkyPin;

    int thumbValue;
    int indexValue;
    int middleValue;
    int ringValue;
    int pinkyValue;

    int classifyFlexValue(int sensorValue);
};

#endif
