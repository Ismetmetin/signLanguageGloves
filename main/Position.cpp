#include "Position.h"
#include <Wire.h>


void Position::gyro_signals() {
    Wire.beginTransmission(0x68);
    Wire.write(0x1A);
    Wire.write(0x05);
    Wire.endTransmission();

    Wire.beginTransmission(0x68);
    Wire.write(0x1C);
    Wire.write(0x10);
    Wire.endTransmission();

    Wire.beginTransmission(0x68);
    Wire.write(0x3B);
    Wire.endTransmission();
    Wire.requestFrom(0x68, 8);
    int16_t AccXLSB = Wire.read() << 8 | Wire.read();
    int16_t AccYLSB = Wire.read() << 8 | Wire.read();
    int16_t AccZLSB = Wire.read() << 8 | Wire.read();

    Wire.beginTransmission(0x68);
    Wire.write(0x1B);
    Wire.write(0x08);
    Wire.endTransmission();

    Wire.beginTransmission(0x68);
    Wire.write(0x43);
    Wire.endTransmission();

    Wire.requestFrom(0x68, 6);
   
    AccX = (float)AccXLSB / 5400;
    AccY = (float)AccYLSB / 5400;
    AccZ = (float)AccZLSB / 5400;

  
}

float Position::getAccX() {
    return AccX *180;
}

float Position::getAccY() {
    return AccY*180;
}

float Position::getAccZ() {
    return AccZ*180;
}
//2
void Position:: readSignal(*angleX,*angleY,*angleZ){
gyro_signals();
*angleX = getAccX();
*angleY = getAccY();
*angleZ = getAccZ();
}
