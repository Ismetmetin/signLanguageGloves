#include "Fingers.h"
#include "Position.h"
#include "AccelerationDirection.h"
#include "Wire.h"
#include "Arduino.h"

//#include"mp3tf16p.h"

//MP3Player mp3(10,9);

#define OUTPUT_READABLE_REALACCEL

const int thumbPin = A0;
const int indexPin = A1;
const int middlePin = A2;
const int ringPin = A3;
const int pinkyPin = A4;

Fingers handFingers(thumbPin, indexPin, middlePin, ringPin, pinkyPin);
int thumbState;
int indexState;
int middleState;
int ringState;
int pinkyState;


Position position;

float angleX;
float angleY;
float angleZ;

AccelerationDirection accelerationDirection;
//These strings will store the lates direction of the hand
String directionX;
String directionY;
String directionZ;

long lastTime = 0;

void gestureRecognition();

void setup() {
  //mp3.initialize();

  //Ако дава проблем със Serial-a следващите 3 реда ги изкарай от коментар и влез в AccelerationDirection.cpp setup() и от там махни //5
  // Serial.begin(38400);
  // Wire.setClock(400000);
  // Wire.begin();
  // delay(250); този коментар да се махне ако кода работи без проблеми
  //повтаря се със сетъпа на accelerationDirection


  handFingers.setupFlexSensors();

  accelerationDirection.setup();
  /*
    Wire.beginTransmission(0x68);
    Wire.write(0x6B);
    Wire.write(0x00);
    Wire.endTransmission();*/
}


void loop() {

  /*
    handFingers.readFlexSensors();
    thumbState=handFingers.getThumbState();
    indexState=handFingers.getIndexState();
    middleState=handFingers.getMiddleState();
    ringState=handFingers.getRingState();
    pinkyState=handFingers.getPinkyState();*/

  //reads values for  all five fingers and classifies them
  //testvai rukavicata s tozi red. Ako raboti normalno moje gornoto da se iztrie ot maina zashtoto e golqmo i stoi grozno. Ako ne proraboti shte go vurnem i shte mahnem vs promeni koito sum otbleqzal s //1
  handFinger.readAllSensors(&thumbState, &indexState, &middleState, &ringState, &pinkyState);

  /*position.gyro_signals();
    angleX=position.getAccX();
    angleY=position.getAccY();
    angleZ=position.getAccZ();*/
  //2
  position.readSignal(&angleX, &angleY, &angleZ);

  //3
  accelerationDirection.getDirections(&directionX,&directionY,&directionZ);

  /*accelerationDirection.loop();
  directionX = accelerationDirection.getXDirection();
  directionY = accelerationDirection.getYDirection();
  directionZ = accelerationDirection.getZDirection();*/

  //4
  gestureRecognition();
}

void gestureRecognition(){
  long currentTime = millis();             // Get the current time in milliseconds
  long timeDiff = currentTime - lastTime;  // Calculate the time difference*/

  if (angleZ > 60 && angleZ < 150 && angleX > 50 && angleX < 160 && directionY == "Right") {
    if (thumbState == 2 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1 && angleZ > 60 && angleZ < 150 && angleX > 50 && angleX < 160 && timeDiff >= 1000) {
      //Serial.print("zdravei");//utre kato vzema modula za mp3 failovete ste go smenq na tva da go kazva
      lastTime = currentTime;
    }
  }
  if (directionY == "Left") {
    if (thumbState == 2 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1 && angleX > 90 && angleX < 170 && angleY > 40 && angleY < 120 && angleZ > 0 && angleZ < 80 && timeDiff >= 1000) {
      //Serial.print("blagodarq");
      lastTime = currentTime;
    }
  }
  if (angleX > 80 && angleX < 110 && angleY > 0 && angleY < 80 && angleZ > 80 && angleZ < 150) {
    if (angleX > 80 && angleX < 110 && angleY > 0 && angleY < 80 && angleZ > 80 && angleZ < 150 && timeDiff >= 1000) {
      //Serial.print("molq");
      lastTime = currentTime;
    }
  }
  if (directionY == "Left") {
    if (thumbState == 3 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 && angleX > 70 && angleX < 130 && angleY > 30 && angleY < 70 && angleZ > 0 && angleZ < 100 && timeDiff >= 1000) {
      //Serial.print("az");
      lastTime = currentTime;
    }
  }
  if (directionZ == "Up") {
    if (timeDiff >= 100) {
      lastTime = currentTime;
      if (directionY == "Right") {
        if (thumbState == 1 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2 && timeDiff >= 1000) {
          Serial.print("dobre");
          lastTime = currentTime;
        }
      }
    }
  }
  /* // Check if the finger states are as desired and enough time has passed
    if (thumbState == 2 && indexState == 3 && middleState == 3 && ringState == 3 && pinkyState == 3 && timeDiff >= 1000) {
        Serial.println("a"); // Print "a" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }else{Serial.println(" ");}

    // Check if the finger states are as desired and enough time has passed
    else if (thumbState == 3 && indexState == 1 && middleState == 2 && ringState == 3 && pinkyState == 3 && timeDiff >= 1000) {
        Serial.println("b"); // Print "b" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }

    else if (thumbState == 1 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("v"); // Print "v" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 1 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 && angleX < -160 && timeDiff >= 1000) {
        Serial.println("g"); // Print "g" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 3 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("d"); // Print "d" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("e"); // Print "e" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 1 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2&& angleZ > 160 && timeDiff >= 1000) {
        Serial.println("j"); // Print "j" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 2 && ringState == 2 && pinkyState == 2 && angleZ > 160 && directionX=="Down" && timeDiff >= 1000) {
        Serial.println("z"); // Print "z" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 3 && middleState == 3 && ringState == 1 && pinkyState == 1 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("i"); // Print "i" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 1 && ringState == 1 && pinkyState == 1 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("ii"); // Print "ii" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 3 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("k"); // Print "k" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 3 && angleX < -160 && timeDiff >= 1000) {
        Serial.println("l"); // Print "l" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("m"); // Print "m" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 1 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("n"); // Print "n" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 1 && ringState == 1 && pinkyState == 1 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("o"); // Print "o" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1 && angleX <-160 && timeDiff >= 1000) {
        Serial.println("p"); // Print "p" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 2 && ringState == 1 && pinkyState == 1 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("r"); // Print "r" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2 && angleZ > 160 && timeDiff >= 1000) {
        Serial.println("s"); // Print "s" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 && angleX < -160 && timeDiff >= 1000) {
        Serial.println("t"); // Print "t" if conditions are met
        lastTime = currentTime; // Update the last time the conditions were met
    }
    else if (thumbState == 1 && indexState == 3 && middleState == 3 && ringState == 3 && pinkyState == 1 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("u"); 
        lastTime = currentTime; 
    }
    else if (thumbState == 2 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("f"); 
        lastTime = currentTime; 
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 3 && ringState == 3 && pinkyState == 3 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("h"); 
        lastTime = currentTime; 
    }
    else if (thumbState == 1 && indexState == 1 && middleState == 1 && ringState == 2 && pinkyState == 2 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("ts"); 
        lastTime = currentTime; 
    }
    else if (thumbState == 1 && indexState == 2 && middleState == 2 && ringState == 3 && pinkyState == 3 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("ch"); 
        lastTime = currentTime; 
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("sh");
        lastTime = currentTime; 
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 && angleX > 160 && directionX=="Down" &&timeDiff >= 1000) {
        Serial.println("sht"); 
        lastTime = currentTime; 
    }
    else if (thumbState == 1 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 && angleX > 160 &&directionY=="Left" && timeDiff >= 1000) {
        Serial.println("er golyam"); 
        lastTime = currentTime; 
    }
    else if (thumbState == 1 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 && angleX > 160 &&directionY=="Right" && timeDiff >= 1000) {
        Serial.println("er malak"); 
        lastTime = currentTime;
    }
    else if (thumbState == 3 && indexState == 3 && middleState == 3 && ringState == 3 && pinkyState == 1 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("iu"); 
        lastTime = currentTime;
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 2 && ringState == 3 && pinkyState == 3 && angleX > 160 && timeDiff >= 1000) {
        Serial.println("q"); 
        lastTime = currentTime; 
    }*/

}

