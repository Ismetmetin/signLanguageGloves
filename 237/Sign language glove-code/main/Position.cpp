#include "Position.h"
#include <Wire.h>  // Include the Wire library for I2C communication

void Position::gyro_signals() {
    // Initialize communication with the MPU6050 sensor
    Wire.beginTransmission(0x68);  // Start communication with the device at address 0x68
    Wire.write(0x1A);  // Set gyroscope configuration to ±250 degrees/s
    Wire.write(0x05);  
    Wire.endTransmission();

    Wire.beginTransmission(0x68);  // Start another transmission
    Wire.write(0x1C);  // Set accelerometer configuration to ±2g
    Wire.write(0x10);
    Wire.endTransmission();

    Wire.beginTransmission(0x68);  // Start another transmission
    Wire.write(0x3B);  // Request acceleration data
    Wire.endTransmission();
    Wire.requestFrom(0x68, 8);  // Request 8 bytes of data from the device
    int16_t AccXLSB = Wire.read() << 8 | Wire.read();  // Read X-axis acceleration data
    int16_t AccYLSB = Wire.read() << 8 | Wire.read();  // Read Y-axis acceleration data
    int16_t AccZLSB = Wire.read() << 8 | Wire.read();  // Read Z-axis acceleration data

    Wire.beginTransmission(0x68);  // Start another transmission
    Wire.write(0x1B);  // Set gyroscope configuration to ±500 degrees/s
    Wire.write(0x08);
    Wire.endTransmission();

    Wire.beginTransmission(0x68);  // Start another transmission
    Wire.write(0x43);  // Request gyroscope data
    Wire.endTransmission();
    Wire.requestFrom(0x68, 6);  // Request 6 bytes of data from the device

    // Convert raw data to acceleration values in g (gravity units)
    AccX = (float)AccXLSB / 5400;
    AccY = (float)AccYLSB / 5400;
    AccZ = (float)AccZLSB / 5400;
}

float Position::getAccX() {
    return AccX;  // Return X-axis acceleration
}

float Position::getAccY() {
    return AccY;  // Return Y-axis acceleration
}

float Position::getAccZ() {
    return AccZ;  // Return Z-axis acceleration
}
