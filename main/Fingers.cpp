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


int Fingers::classifyThumbFlexValue(int sensorValue) {
    if (sensorValue < 5) {
        return 1;
    } else if (sensorValue >= 5 && sensorValue < 25) {
        return 2;
    } else {
        return 3;
    }
}
int Fingers::classifyIndexOrMiddleFlexValue(int sensorValue) {
    if (sensorValue < 40) {
        return 1;
    } else if (sensorValue >= 40 && sensorValue < 80) {
        return 2;
    } else {
        return 3;
    }
}
//ako tova raboti mojem da iztriem classifyPinkyFlexValue i classifyIndexOrMiddleValue
int Fingers::classifyIndexMiddleOrPinkyFlexValue(int sensorValue) {
    if (sensorValue < 40) {
        return 1;
    } else if (sensorValue >= 40 && sensorValue < 80) {
        return 2;
    } else {
        return 3;
    }
}
int Fingers::classifyRingFlexValue(int sensorValue) {
    if (sensorValue < 20) {
        return 1;
    } else if (sensorValue >= 20 && sensorValue < 35) {
        return 2;
    } else {
        return 3;
    }
}
int Fingers::classifyPinkyFlexValue(int sensorValue) {
    if (sensorValue < 40) {
        return 1;
    } else if (sensorValue >= 40 && sensorValue < 80) {
        return 2;
    } else {
        return 3;
    }
}
//1
void Fingers:: readAllSensors(int *thumb, int *index, int *middle, int *ring, int *pinky){
    thumbValue = analogRead(thumbPin);
    indexValue = analogRead(indexPin);
    middleValue = analogRead(middlePin);
    ringValue = analogRead(ringPin);
    pinkyValue = analogRead(pinkyPin);

    *thumb = classifyThumbFlexValue(thumbValue);
    *index = classifyIndexMiddleOrPinkyFlexValue(indexValue);
    *middle =classifyIndexMiddleOrPinkyFlexValue(middleValue); 
    *ring = classifyRingFlexValue(ringValue);
    *pinky = classifyIndexMiddleOrPinkyFlexValue(pinkyValue);

}

void Fingers::readFlexSensors() {
    thumbValue = analogRead(thumbPin);
    indexValue = analogRead(indexPin);
    middleValue = analogRead(middlePin);
    ringValue = analogRead(ringPin);
    pinkyValue = analogRead(pinkyPin);
    
    //pinkyValue = map(pinkyValue,200,440,0,520);

   /* Serial.print("Thumb Sensor Value: ");
    Serial.println(thumbValue);
    Serial.print("Thumb Classification: ");
    Serial.println(classifyThumbFlexValue(thumbValue));

    Serial.print("Index Sensor Value: ");
    Serial.println(indexValue);
    Serial.print("Index Classification: ");
    Serial.println(classifyIndexAndMiddleFlexValue(indexValue));

    Serial.print("Middle Sensor Value: ");
    Serial.println(middleValue);
    Serial.print("Middle Classification: ");
    Serial.println(classifyIndexAndMiddleFlexValue(middleValue));

    Serial.print("Ring Sensor Value: ");
    Serial.println(ringValue);
    Serial.print("Ring Classification: ");
    Serial.println(classifyRingFlexValue(ringValue));

    Serial.print("Pinky Sensor Value: ");
    Serial.println(pinkyValue);
    Serial.print("Pinky Classification: ");
    Serial.println(classifyPinkyFlexValue(pinkyValue));

    Serial.println("-------------");*/
}
//ako //1 raboti nqmame nujda ot tezi 
int Fingers::getThumbState()
{return classifyThumbFlexValue(thumbValue);}

int Fingers::getIndexState()
{return classifyIndexAndMiddleFlexValue(indexValue);}

int Fingers::getMiddleState()
{return classifyIndexAndMiddleFlexValue(middleValue);}

int Fingers::getRingState()
{return classifyRingFlexValue(ringValue);}

int Fingers::getPinkyState()
{return classifyPinkyFlexValue(pinkyValue);}
