#include "Fingers.h"

Fingers::Fingers(int thumbPin, int indexPin, int middlePin, int ringPin, int pinkyPin) {
    this->thumbPin = thumbPin;
    this->indexPin = indexPin;
    this->middlePin = middlePin;
    this->ringPin = ringPin;
    this->pinkyPin = pinkyPin;
}

void Fingers::setupFlexSensors() {
    pinMode(thumbPin, INPUT);
    pinMode(indexPin, INPUT);
    pinMode(middlePin, INPUT);
    pinMode(ringPin, INPUT);
    pinMode(pinkyPin, INPUT);
}

int Fingers::classifyFlexValue(int sensorValue) {
    if (sensorValue < 15) {
        return 1;
    } else if (sensorValue >= 15 && sensorValue < 50) {
        return 2;
    } else if (sensorValue >= 50 && sensorValue < 80) {
        return 3;
    } else {
        return 4;
    }
}

void Fingers::readFlexSensors() {
    thumbValue = analogRead(thumbPin);
    indexValue = analogRead(indexPin);
    middleValue = analogRead(middlePin);
    ringValue = analogRead(ringPin);
    pinkyValue = analogRead(pinkyPin);

    pinkyValue = map(pinkyValue,200,440,0,520);

    Serial.print("Thumb Sensor Value: ");
    Serial.println(thumbValue);
    Serial.print("Thumb Classification: ");
    Serial.println(classifyFlexValue(thumbValue));

    Serial.print("Index Sensor Value: ");
    Serial.println(indexValue);
    Serial.print("Index Classification: ");
    Serial.println(classifyFlexValue(indexValue));

    Serial.print("Middle Sensor Value: ");
    Serial.println(middleValue);
    Serial.print("Middle Classification: ");
    Serial.println(classifyFlexValue(middleValue));

    Serial.print("Ring Sensor Value: ");
    Serial.println(ringValue);
    Serial.print("Ring Classification: ");
    Serial.println(classifyFlexValue(ringValue));

    Serial.print("Pinky Sensor Value: ");
    Serial.println(pinkyValue);
    Serial.print("Pinky Classification: ");
    Serial.println(classifyFlexValue(pinkyValue));

    Serial.println("-------------");
}
