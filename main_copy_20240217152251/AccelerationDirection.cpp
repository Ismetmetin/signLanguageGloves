
#include "AccelerationDirection.h"

#define OUTPUT_READABLE_REALACCEL

AccelerationDirection::AccelerationDirection() :
    dmpReady(false),
    mpuInterrupt(false),
    lastTime(0),
    directionThreshold(700),
    zDirectionThreshold(800),
    detectedXDirection(""),
    detectedYDirection(""),
    detectedZDirection("") {}

void AccelerationDirection::setup() {
    //5
    Wire.begin();
    Wire.setClock(400000);
    Serial.begin(38400);
    //до тук
    while (!Serial);

    mpu.initialize();
    uint8_t devStatus = mpu.dmpInitialize();
    if (devStatus == 0) {
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
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

void AccelerationDirection::loop() {
     bool printedDirection = false; // Declare printedDirection here
    if (!dmpReady) return;
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
            if (!printedDirection) {
                if (abs(deltaX) > directionThreshold) {
                    
                    if (deltaX > 0) {
                        //Serial.println("Backward");
                        detectedXDirection="Backward";
                    } else {
                        //Serial.println("Forward");
                        detectedXDirection="Forward";
                    }
                }else{detectedXDirection=" ";}
                if (abs(deltaY) > directionThreshold) {
                    
                    if (deltaY > 0) {
                        //Serial.println("Right");
                        detectedYDirection = "Right";
                    } else {
                        //Serial.println("Left");
                        detectedYDirection = "Left";
                    }
                }else{detectedYDirection=" ";}
                if (abs(deltaZ) > zDirectionThreshold) {
                    
                    if (deltaZ > 0) {
                        //Serial.println("Down");
                        detectedZDirection = "Down";
                    } else {
                        //Serial.println("Up");
                        detectedZDirection = "Up";
                    }
                }else{detectedZDirection=" ";}
                //Serial.println();
                lastWorldAccel[0] = aaWorld.x;
                lastWorldAccel[1] = aaWorld.y;
                lastWorldAccel[2] = aaWorld.z;
                lastTime = currentTime;
                
            }
        }
    }
}
String AccelerationDirection::getXDirection() {
    return detectedXDirection;
}
String AccelerationDirection::getYDirection() {
    return detectedYDirection;
}
String AccelerationDirection::getZDirection() {
    return detectedZDirection;
}
//3
void AccelerationDirection::getDirections(String *dirX, String *dirY,String *dirZ){
  loop();
  *dirX=getXDirection();
  *dirY=getYDirection();
  *dirZ=getZDirection();
}
