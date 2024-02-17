#ifndef FINGERS_H
#define FINGERS_H

#include <Arduino.h>

class Fingers {
public:
    Fingers(int thumbPin, int indexPin, int middlePin, int ringPin, int pinkyPin);
    void setupFlexSensors();
    void readFlexSensors();
    //ako //1 raboti tezi ne sa nujni
    int getThumbState();
    int getIndexState();
    int getMiddleState();
    int getRingState();
    int getPinkyState();

    //1
    void readAllSensors(int *thumb, int *index, int *middle, int *ring, int *pinky);

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

    int classifyThumbFlexValue(int sensorValue);
    int classifyIndexOrMiddleFlexValue(int sensorValue);
    int classifyRingFlexValue(int sensorValue);
    int classifyPinkyFlexValue(int sensorValue);
    //1
    int classifyIndexMiddleOrPinkyFlexValue(int sensorValue);
};

#endif
