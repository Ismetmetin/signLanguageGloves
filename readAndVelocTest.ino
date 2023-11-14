#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
int16_t ax,ay,az,gx,gy,gz;
double nAx,nAy,nAz, nGx, nGy, nGz;
MPU6050 accelgyro;

void setup() {
  // put your setup code here, to run once:
 #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.begin(38400);

    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

}

void loop() {
  // put your main code here, to run repeatedly:
    //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    // nAx = ax/1688.0;
    // nAy = ay/1688.0;
    // nAz = az/1688.0;

    // //Serial.print(nAx);
    // //Serial.print("\t");
    // Serial.print(nAy);
    // Serial.print("\t");
    //Serial.println(nAz);

    double V = 0.0;
    //double dA = ay/1688.0;;
    double t;
    for (t = 0.001;t<=2;t+=0.001){
      accelgyro.getAcceleration(&ax, &ay, &az);
      V= V+(az/1688.0)*t;

      Serial.println(V);
      delay(1);
    }
    delay(2000);
    Serial.println(V/2000.0);
    delay(10000);

}
