#include "Fingers.h"

// Constructor to initialize the pin numbers for each flex sensor
Fingers::Fingers(int thumbPin, int indexPin, int middlePin, int ringPin, int pinkyPin) {
    this->thumbPin = thumbPin;   // Initialize thumb pin
    this->indexPin = indexPin;   // Initialize index finger pin
    this->middlePin = middlePin; // Initialize middle finger pin
    this->ringPin = ringPin;     // Initialize ring finger pin
    this->pinkyPin = pinkyPin;   // Initialize pinky finger pin
}

// Function to set up the flex sensors as inputs
void Fingers::setupFlexSensors() {
    pinMode(thumbPin, INPUT);   // Set thumb pin as input
    pinMode(indexPin, INPUT);   // Set index finger pin as input
    pinMode(middlePin, INPUT);  // Set middle finger pin as input
    pinMode(ringPin, INPUT);    // Set ring finger pin as input
    pinMode(pinkyPin, INPUT);   // Set pinky finger pin as input
}

// Function to classify the flex sensor value for the thumb
int Fingers::classifyThumbFlexValue(int sensorValue) {
    if (sensorValue < 5) {
        return 1;  // Thumb fully extended
    } else if (sensorValue >= 5 && sensorValue < 15) {
        return 2;  // Thumb partially flexed
    } else {
        return 3;  // Thumb fully flexed
    }
}

// Function to classify the flex sensor value for the index and middle fingers
int Fingers::classifyIndexAndMiddleFlexValue(int sensorValue) {
    if (sensorValue < 20) {
        return 1;  // Finger fully extended
    } else if (sensorValue >= 12 && sensorValue < 60) {
        return 2;  // Finger partially flexed
    } else {
        return 3;  // Finger fully flexed
    }
}

// Function to classify the flex sensor value for the ring finger
int Fingers::classifyRingFlexValue(int sensorValue) {
    if (sensorValue < 20) {
        return 1;  // Finger fully extended
    } else if (sensorValue >= 20 && sensorValue < 55) {
        return 2;  // Finger partially flexed
    } else {
        return 3;  // Finger fully flexed
    }
}

// Function to classify the flex sensor value for the pinky finger
int Fingers::classifyPinkyFlexValue(int sensorValue) {
    if (sensorValue < 10) {
        return 1;  // Pinky finger fully extended
    } else if (sensorValue >= 10 && sensorValue < 60) {
        return 2;  // Pinky finger partially flexed
    } else {
        return 3;  // Pinky finger fully flexed
    }
}

// Function to read the values from all flex sensors
void Fingers::readFlexSensors() {
    thumbValue = analogRead(thumbPin);     // Read thumb sensor value
    indexValue = analogRead(indexPin);     // Read index finger sensor value
    middleValue = analogRead(middlePin);   // Read middle finger sensor value
    ringValue = analogRead(ringPin);       // Read ring finger sensor value
    pinkyValue = analogRead(pinkyPin);     // Read pinky finger sensor value
}

// Functions to get the state of each finger
int Fingers::getThumbState() {
    return classifyThumbFlexValue(thumbValue);  // Return thumb state
}

int Fingers::getIndexState() {
    return classifyIndexAndMiddleFlexValue(indexValue);  // Return index finger state
}

int Fingers::getMiddleState() {
    return classifyIndexAndMiddleFlexValue(middleValue);  // Return middle finger state
}

int Fingers::getRingState() {
    return classifyRingFlexValue(ringValue);  // Return ring finger state
}

int Fingers::getPinkyState() {
    return classifyPinkyFlexValue(pinkyValue);  // Return pinky finger state
}
