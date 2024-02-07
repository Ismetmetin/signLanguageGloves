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

    int16_t GyroX = Wire.read() << 8 | Wire.read();
    int16_t GyroY = Wire.read() << 8 | Wire.read();
    int16_t GyroZ = Wire.read() << 8 | Wire.read();

    RateRoll = (float)GyroX / 65.5;
    RatePitch = (float)GyroY / 65.5;
    RateYaw = (float)GyroZ / 65.5;

    AccX = (float)AccXLSB / 4096;
    AccY = (float)AccYLSB / 4096;
    AccZ = (float)AccZLSB / 4096;

  
}

float Position::getAccX() {
    return AccX;
}

float Position::getAccY() {
    return AccY;
}

float Position::getAccZ() {
    return AccZ;
}

/*void Position::getPosition() {
    if (AccZ < 160) {
        thePosition = "normalna";
    }
    if (AccX < -15 && AccX > 30 && AccY >-180 && AccY <= -120 && AccZ > 110 && AccZ < 150) {
        thePosition = "zdravei";
    }
    if (AccX < -15 && AccX > 30 && AccY >= 150 && AccY <= 190 && AccZ > 50 && AccZ < 120) {
        thePosition = "zdraveiAmaNaobratno";
    }
    if (AccX < -15 && AccX > 30 && AccY >= 150 && AccY <= 190 && AccZ > 50 && AccZ < 120) {
        thePosition = "normalna";
    }
   
    
    return thePosition;
}
*/
