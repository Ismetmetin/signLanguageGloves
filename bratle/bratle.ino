
#include "Fingers.h"


const int thumbPin = A0;
const int indexPin = A1;
const int middlePin = A2;
const int ringPin = A3;
const int pinkyPin = A4;

Fingers handFingers(thumbPin, indexPin, middlePin, ringPin, pinkyPin);

void setup() {
  handFingers.setupFlexSensors();
  Serial.begin(38400);
}

void loop() {

  
 handFingers.readFlexSensors();
        delay(1000);

}
