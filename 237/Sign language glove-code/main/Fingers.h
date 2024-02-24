#ifndef FINGERS_H
#define FINGERS_H

#include <Arduino.h> // Include the Arduino library for Arduino-specific functions and definitions

class Fingers {
public:
    // Constructor to initialize the pins for the flex sensors
    Fingers(int thumbPin, int indexPin, int middlePin, int ringPin, int pinkyPin);
    
    // Function to set up the flex sensors
    void setupFlexSensors();
    
    // Function to read the flex sensors
    void readFlexSensors();
    
    // Functions to get the state of each finger
    int getThumbState();
    int getIndexState();
    int getMiddleState();
    int getRingState();
    int getPinkyState();

private:
    // Pin numbers for each flex sensor
    int thumbPin;
    int indexPin;
    int middlePin;
    int ringPin;
    int pinkyPin;

    // Variables to store the values read from each flex sensor
    int thumbValue;
    int indexValue;
    int middleValue;
    int ringValue;
    int pinkyValue;

    // Functions to classify the flex sensor values into states for each finger
    int classifyThumbFlexValue(int sensorValue);
    int classifyIndexAndMiddleFlexValue(int sensorValue);
    int classifyRingFlexValue(int sensorValue);
    int classifyPinkyFlexValue(int sensorValue);
};
#endif
