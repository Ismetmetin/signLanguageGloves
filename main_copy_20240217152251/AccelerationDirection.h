#ifndef ACCELERATION_DIRECTION_H
#define ACCELERATION_DIRECTION_H

#include "Arduino.h"
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

#define OUTPUT_READABLE_REALACCEL

class AccelerationDirection {
public:
    AccelerationDirection();
    void setup();
    void loop();
    String getXDirection();
    String getYDirection();
    String getZDirection();

private:
 MPU6050 mpu;
    bool dmpReady;
    uint16_t packetSize;
    uint8_t fifoBuffer[64];
    volatile bool mpuInterrupt;
    uint8_t mpuIntStatus; 
    bool printedDirection;
    VectorInt16 aa;
    VectorInt16 aaReal;
    VectorInt16 aaWorld;
    VectorFloat gravity;
    Quaternion q;
    float euler[3];
    float ypr[3];
    uint32_t lastTime;
    float lastWorldAccel[3];
    const int directionThreshold;
    const int zDirectionThreshold;
    String detectedXDirection;
    String detectedYDirection;
    String detectedZDirection;
    void dmpDataReady();
  //3
    void getDirections(String *dirX, String *dirY,String *dirZ);
};

#endif
