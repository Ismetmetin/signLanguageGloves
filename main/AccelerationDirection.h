/*
#ifndef ACCELERATIONDIRECTION_H
#define ACCELERATIONDIRECTION_H

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

class AccelerationDirection {
private:
    MPU6050 mpu;
    bool dmpReady;
    uint8_t mpuIntStatus;
    uint8_t devStatus;
    uint16_t packetSize;
    uint16_t fifoCount;
    uint8_t fifoBuffer[64];
    Quaternion q;
    VectorInt16 aa;
    VectorInt16 aaReal;
    VectorInt16 aaWorld;
    VectorFloat gravity;
    float euler[3];
    float ypr[3];

    uint32_t lastTime;
    float lastWorldAccel[3];
    const int directionThreshold;
    const int zDirectionThreshold;
    bool printedDirection;
    String detectedXDirection;
    String detectedYDirection;
    String detectedZDirection;

public:
    AccelerationDirection();
    void initialize();
    void detectDirectionChanges();

private:
    void setupMPU6050();
};

#endif*/
