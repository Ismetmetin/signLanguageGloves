#ifndef ACCELERATION_DIRECTION_H
#define ACCELERATION_DIRECTION_H


#include "Arduino.h"  // Include Arduino library for Arduino-specific functions and definitions
#include "I2Cdev.h"   // Include I2Cdev library for I2C communication
#include "MPU6050_6Axis_MotionApps20.h"  // Include MPU6050 library for interfacing with the sensor

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"  // Include Wire library for I2C communication (Arduino Wire implementation)
#endif

#define OUTPUT_READABLE_REALACCEL  // Define a macro for readable real acceleration output

class AccelerationDirection {
public:
    AccelerationDirection();  // Constructor
    void setup();  // Function to set up the sensor
    void loop();  // Main loop function
    String getXDirection();  // Function to get X-axis direction
    String getYDirection();  // Function to get Y-axis direction
    String getZDirection();  // Function to get Z-axis direction

private:
    MPU6050 mpu;  // MPU6050 object for interfacing with the sensor
    bool dmpReady;  // Flag to indicate if DMP is ready
    uint16_t packetSize;  // Size of DMP packet
    uint8_t fifoBuffer[64];  // FIFO buffer for DMP data
    volatile bool mpuInterrupt;  // Flag for MPU interrupt
    uint8_t mpuIntStatus;  // MPU interrupt status
    bool printedDirection;  // Flag indicating if direction is printed
    VectorInt16 aa;  // Raw acceleration data
    VectorInt16 aaReal;  // Real acceleration data
    VectorInt16 aaWorld;  // World-frame acceleration data
    VectorFloat gravity;  // Gravity vector
    Quaternion q;  // Quaternion for orientation
    float euler[3];  // Euler angles
    float ypr[3];  // Yaw, pitch, and roll angles
    uint32_t lastTime;  // Timestamp of last measurement
    float lastWorldAccel[3];  // Last measured world-frame acceleration
    const int directionThreshold;  // Threshold for direction detection
    const int zDirectionThreshold;  // Threshold for Z-axis direction detection
    String detectedXDirection;  // Detected X-axis direction
    String detectedYDirection;  // Detected Y-axis direction
    String detectedZDirection;  // Detected Z-axis direction

    void dmpDataReady();  // Function called when DMP data is ready
};

#endif
