//#include "AccelerationDirection.h"
#include "Fingers.h"
#include "Position.h"

#include "Wire.h"
const int thumbPin = A0;
const int indexPin = A1;
const int middlePin = A2;
const int ringPin = A3;
const int pinkyPin = A4;

Fingers handFingers(thumbPin, indexPin, middlePin, ringPin, pinkyPin);

Position position;



void setup() {
    Serial.begin(38400);
    Wire.setClock(400000);
    Wire.begin();
    delay(250);
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission();
  
   // accelerationDirection.initialize(); 
    handFingers.setupFlexSensors();
}
  

void loop() {
    
    //accelerationDirection.detectDirectionChanges();

    position.gyro_signals();

    Serial.print("Acceleration X[g] = ");
    Serial.print(position.getAccX() * 180);
    Serial.print("Acceleration Y[g] = ");
    Serial.print(position.getAccY() * 180);
    Serial.print("Acceleration Z[g] = ");
    Serial.println(position.getAccZ() * 180);

    handFingers.readFlexSensors();
        delay(500);

}
