#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
//?import??
//Кода не е тестван на ардуино 
//като се ползват сензори трябва типа да се смени на инт и да се анализират стойностите от тях

//Опростени стойности за сгънат(true) и разгънат(false) пръст
bool flexT, flexI, flexM, flexR,flexP;
/*
*/
int16_t nAx,nAy,nAz, nGx, nGy, nGz;
MPU6050 accelgyro;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  flexT=1, flexI = 1, flexM = 1, flexR =1, flexP = 0; 
  /*
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
  */
}
/*Идеята ми е да четем данни от флекс сензорите всеки 0,25/0,5 секунди. В случай че Засечените данни са буква или начало на жест четенето от флекс сензорите спира.
  За да отделим буквите от жестовете (в случай че някоя буква прилича на жест по стойностите в флекс сензора), ще се даде един период от време(например 1-2сек) за направа на движението
  което ще бъде предварително анализирано какви промени ще настъпят в ax ay az gx gy gz. При много малка разлика в движенията се изписва буквата на конзолата, при драстична
  разлика в движениета което match-va предварително изследваните разлики в координатите се изписва жеста. В случай че не се намери движение което пасва на стойностите не се принтира нищо.
  В случай че се засече буква/жест може да се спре периода за направа на движение за да се продължи със следващия жест/буква (за да изглежда по smooth). -> Обясни го на Екатерина
 */

 /* Опция 1: Като се стигне до частта с засичането на направа на движение може да се използва интегриране на Скорост започвайки от 0 докато скоростта не стигне 0 отново????????????
    Опция 2: В периода от 1-2 секунди ще се четат данните на модула и ще се запазват за сверяване?????? */


void loop() {
  //При липса на сензори въвеждаме данните за пръстите ръчно
  
  Serial.println(condition(flexT, flexI, flexM, flexR,flexP));
  
    
  //На теория това трябва да работи но няма как да го тествам.
}

String condition(bool flexT, bool flexI, bool flexM, bool flexR, bool flexP){

   bool A = flexT&&flexI&&flexM&&flexR&&!flexP;

   if(A){
    return AorHi();
   }else{ return "In development";
  }
}

String AorHi(){
  accelgyro.getAcceleration(&nAx, &nAy, nAz);
  double avgDeltaAx, avgDeltaAy, avgDeltaAz;
//период в който ще чака движение 1500ms
  for (int i=0; i< 1500; i+=100) {
    //ne znam kakvo vrushta tazi funkciq PROVERI GO!
    avgDeltaAx += accelgyro.getAccelerationX();
    avgDeltaAy += accelgyro.getAccelerationY();
    avgDeltaAz += accelgyro.getAccelerationZ();
    delay(100);
  }
  avgDeltaAx/=(1688.0*15.0); 
  avgDeltaAy/=(1688.0*15.0); 
  avgDeltaAz/=(1688.0*15.0); 

  //Условие че координатите са сравнително близки един до друг
  if((abs(avgDeltaAx-1)<abs(nAx)&&abs(avgDeltaAx+1)<abs(nAx))&&(abs(avgDeltaAy-1)<abs(nAy)&&abs(avgDeltaAy+1)<abs(nAy))&&(abs(avgDeltaAz-1)<abs(nAz)&&abs(avgDeltaAz+1)<abs(nAz))){
    return "A";
  }else{
    //в случая не знаем дали е извършено правилното движение за жеста затова го ограничаваме. Ограничение: Ако има разлика в xyz => е направено правилното движение.
    return "Hi!";
  }
}



