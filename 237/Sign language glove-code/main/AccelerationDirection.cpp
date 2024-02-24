#include "AccelerationDirection.h"
#define OUTPUT_READABLE_REALACCEL  // Define a macro for readable real acceleration output

// Constructor: Initialize member variables
AccelerationDirection::AccelerationDirection() :
    dmpReady(false),
    mpuInterrupt(false),
    lastTime(0),
    directionThreshold(700),  // Threshold for direction detection on X and Y axes
    zDirectionThreshold(800), // Threshold for direction detection on Z axis
    detectedXDirection(""),   // Detected X-axis direction
    detectedYDirection(""),   // Detected Y-axis direction
    detectedZDirection("") {} // Detected Z-axis direction

// Setup function: Initialize sensor, serial communication, and DMP
void AccelerationDirection::setup() {
    Wire.begin();  // Initialize I2C communication
    Wire.setClock(400000);  // Set I2C clock speed
    Serial.begin(38400);    // Initialize serial communication with a baud rate of 38400
    while (!Serial);  // Wait for serial port to connect
    
    mpu.initialize();  // Initialize MPU6050 sensor
    uint8_t devStatus = mpu.dmpInitialize();  // Initialize DMP
    if (devStatus == 0) {  // Check if DMP initialization was successful
        mpu.CalibrateAccel(6);  // Calibrate accelerometer
        mpu.CalibrateGyro(6);   // Calibrate gyroscope
        mpu.setDMPEnabled(true);  // Enable DMP
        mpuIntStatus = mpu.getIntStatus();  // Get MPU interrupt status
        dmpReady = true;  // Set DMP ready flag
        packetSize = mpu.dmpGetFIFOPacketSize();  // Get FIFO packet size
    } else {
        Serial.print(F("DMP Initialization failed (code "));  // Print error message if DMP initialization fails
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

// Loop function: Main loop for processing sensor data
void AccelerationDirection::loop() {
    bool printedDirection = false; // Declare printedDirection here
    if (!dmpReady) return;  // Exit loop if DMP is not ready
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {  // Check if FIFO packet is available
        mpu.dmpGetQuaternion(&q, fifoBuffer);  // Get quaternion data from DMP
        mpu.dmpGetAccel(&aa, fifoBuffer);      // Get raw accelerometer data from DMP
        mpu.dmpGetGravity(&gravity, &q);       // Get gravity vector from DMP
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);  // Get real acceleration data from DMP
        mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);  // Get acceleration data in world frame from DMP
        uint32_t currentTime = millis();  // Get current time
        if (currentTime - lastTime >= 100) {  // Check if enough time has passed
            float deltaX = aaWorld.x - lastWorldAccel[0];  // Calculate change in acceleration on X axis
            float deltaY = aaWorld.y - lastWorldAccel[1];  // Calculate change in acceleration on Y axis
            float deltaZ = aaWorld.z - lastWorldAccel[2];  // Calculate change in acceleration on Z axis
            if (!printedDirection) {  // Check if direction is already printed
                if (abs(deltaX) > directionThreshold) {  // Check if change in X acceleration exceeds threshold
                    if (deltaX > 0) {
                        detectedXDirection = "Backward";  // Set X direction to backward if acceleration is positive
                    } else {
                        detectedXDirection = "Forward";   // Set X direction to forward if acceleration is negative
                    }
                } else {
                    detectedXDirection = " ";  // Set X direction to blank if change in X acceleration is below threshold
                }
                if (abs(deltaY) > directionThreshold) {  // Check if change in Y acceleration exceeds threshold
                    if (deltaY > 0) {
                        detectedYDirection = "Right";  // Set Y direction to right if acceleration is positive
                    } else {
                        detectedYDirection = "Left";   // Set Y direction to left if acceleration is negative
                    }
                } else {
                    detectedYDirection = " ";  // Set Y direction to blank if change in Y acceleration is below threshold
                }
                if (abs(deltaZ) > zDirectionThreshold) {  // Check if change in Z acceleration exceeds threshold
                    if (deltaZ > 0) {
                        detectedZDirection = "Down";  // Set Z direction to down if acceleration is positive
                    } else {
                        detectedZDirection = "Up";    // Set Z direction to up if acceleration is negative
                    }
                } else {
                    detectedZDirection = " ";  // Set Z direction to blank if change in Z acceleration is below threshold
                }
                lastWorldAccel[0] = aaWorld.x;  // Update last measured world-frame acceleration on X axis
                lastWorldAccel[1] = aaWorld.y;  // Update last measured world-frame acceleration on Y axis
                lastWorldAccel[2] = aaWorld.z;  // Update last measured world-frame acceleration on Z axis
                lastTime = currentTime;  // Update last measured time
            }
        }
    }
}

// Function to get X-axis direction
String AccelerationDirection::getXDirection() {
    return detectedXDirection;
}

// Function to get Y-axis direction
String AccelerationDirection::getYDirection() {
    return detectedYDirection;
}

// Function to get Z-axis direction
String AccelerationDirection::getZDirection() {
    return detectedZDirection;
}
