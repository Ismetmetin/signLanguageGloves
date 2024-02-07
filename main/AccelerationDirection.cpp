/*
#include "AccelerationDirection.h"

AccelerationDirection::AccelerationDirection() : directionThreshold(2000), zDirectionThreshold(2000) {
    dmpReady = false;
    lastTime = 0;
    printedDirection = false;
}

void AccelerationDirection::initialize() {
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000);
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(38400);
    while (!Serial);

    setupMPU6050();
}

void AccelerationDirection::setupMPU6050() {
    mpu.initialize();
    devStatus = mpu.dmpInitialize();

    if (devStatus == 0) {
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.PrintActiveOffsets();
        mpu.setDMPEnabled(true);
        mpuIntStatus = mpu.getIntStatus();
        dmpReady = true;
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
}

void AccelerationDirection::detectDirectionChanges() {
    if (!dmpReady)
        return;

    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetAccel(&aa, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
        mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);

        uint32_t currentTime = millis();
        if (currentTime - lastTime >= 100) {
            float deltaX = aaWorld.x - lastWorldAccel[0];
            float deltaY = aaWorld.y - lastWorldAccel[1];
            float deltaZ = aaWorld.z - lastWorldAccel[2];

           
                if (abs(deltaX) > directionThreshold) {
                    Serial.print("\tDirection X: ");
                    if (deltaX > 0) {
                        Serial.println("Backward");
                        detectedXDirection = "Backward";
                    } else {
                        Serial.println("Forward");
                        detectedXDirection = "Forward";
                    }
                }

                if (abs(deltaY) > directionThreshold) {
                    Serial.print("\tDirection Y: ");
                    if (deltaY > 0) {
                        Serial.println("Right");
                        detectedYDirection = "Right";
                    } else {
                        Serial.println("Left");
                        detectedYDirection = "Left";
                    }
                }

                if (abs(deltaZ) > zDirectionThreshold) {
                    Serial.print("\tDirection Z: ");
                    if (deltaZ > 0) {
                        Serial.println("Down");
                        detectedZDirection = "Down";
                    } else {
                        Serial.println("Up");
                        detectedZDirection = "Up";
                    }

                    // Set printedDirection to true to avoid repeated prints
                  

                lastWorldAccel[0] = aaWorld.x;
                lastWorldAccel[1] = aaWorld.y;
                lastWorldAccel[2] = aaWorld.z;
                lastTime = currentTime;
                delay(200);
            }
        }
    }
}*/
