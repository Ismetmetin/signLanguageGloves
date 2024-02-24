#include "Fingers.h"
#include "Position.h"
#include "AccelerationDirection.h"
#include "Wire.h"
#include "Arduino.h"

#include "mp3tf16p.h" // Include the header file for the MP3 player library
MP3Player mp3(10,9); // Initialize MP3 player object with pins 10 and 9

#define OUTPUT_READABLE_REALACCEL // Define a macro for readable real acceleration output

// Define analog pins for flex sensors
const int thumbPin = A0;
const int indexPin = A1;
const int middlePin = A2;
const int ringPin = A3;
const int pinkyPin = A4;

// Initialize Fingers object with flex sensor pins
Fingers handFingers(thumbPin, indexPin, middlePin, ringPin, pinkyPin);
// Initialize variables to store finger states
int thumbState;
int indexState;
int middleState;
int ringState;
int pinkyState;

Position position; // Initialize Position object
float angleX; // Initialize variables to store angles
float angleY;
float angleZ;

AccelerationDirection accelerationDirection; // Initialize AccelerationDirection object
String directionX; // Declare a string variable to store the X-axis direction
String directionY; // Declare a string variable to store the Y-axis direction
String directionZ; // Declare a string variable to store the Z-axis direction

long lastTime = 0; // Initialize variable to store last time

void setup() {
    mp3.initialize(); // Initialize MP3 player

    Serial.begin(38400); // Initialize serial communication
    Wire.setClock(400000); // Set I2C clock speed
    Wire.begin(); // Initialize I2C communication
    delay(250); // Delay for stabilization

    handFingers.setupFlexSensors(); // Setup flex sensors

    accelerationDirection.setup(); // Setup acceleration direction detection
}

void loop() {
    handFingers.readFlexSensors(); // Read flex sensor values
    position.gyro_signals(); // Read gyro signals
    accelerationDirection.loop(); // Detect acceleration direction

    long currentTime = millis(); // Get current time
    long timeDiff = currentTime - lastTime; // Calculate time difference

    checkGestures(currentTime, timeDiff); // Check for gestures
    lastTime = currentTime; // Update last time
}

// Function to check for gestures based on finger states, angles, and acceleration direction
void checkGestures(long currentTime, long timeDiff) {
    // Get finger states
    thumbState = handFingers.getThumbState();
    indexState = handFingers.getIndexState();
    middleState = handFingers.getMiddleState();
    ringState = handFingers.getRingState();
    pinkyState = handFingers.getPinkyState();

    // Get angles from gyro
    angleX = position.getAccX() * 180;
    angleY = position.getAccY() * 180;
    angleZ = position.getAccZ() * 180;

    // Get acceleration directions
    directionX = accelerationDirection.getXDirection();
    directionY = accelerationDirection.getYDirection();
    directionZ = accelerationDirection.getZDirection();

    // Check for specific gestures and conditions to trigger MP3 playback
    if(angleZ>60&&angleZ<150&&angleX>50&&angleX<160&&directionY=="Right")
    {
      if(thumbState=2&&indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1&&angleZ>60&&angleZ<150&&angleX>50&&angleX<160&&timeDiff>=1000)
      {
          mp3.playTrackNumber(1,30);//This track(1) will play the word "здравей"//the volume is on 30
      }
    }
    else if(directionY=="Left")
    {
      if(thumbState==2&&indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1&&angleX>90&&angleX<170&&angleY>40&&angleY<120&&angleZ>0&&angleZ<80&&timeDiff>=1000)
      {
          mp3.playTrackNumber(2,30);//This track(2) will play the word "благодаря"
      }
    }
    
    else if(thumbState==1&&indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1&&angleY>0&&angleY<80&&angleZ>80&&angleZ<150&&timeDiff>=1000)
      {
           mp3.playTrackNumber(3,30);//This track(3) will play the word "моля"
      }
    
    else if(directionY=="Left")
    {
      if(thumbState==3&&indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3&&angleX>70&&angleX<130&&angleY>30&&angleY<70&&angleZ>0&&angleZ<100&&timeDiff>=1000)
      {
           mp3.playTrackNumber(4,30);//This track(4) will play the word "аз"
      }
    }
    if(directionZ=="Up")
    {
    else if (timeDiff >= 100)
      {
        lastTime = currentTime;
        if(directionY=="Right")
        {
          if(thumbState==1&&indexState == 2&& middleState == 2 && ringState == 2 && pinkyState == 2&&timeDiff>=1000)
          {
             mp3.playTrackNumber(5,30);//This track(5) will play the word "добре"
          }
        }
      }
    }
    else if(directionY=="Right"&&thumbState==3&&indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3)
    {
       if (timeDiff >= 100)
      {
        lastTime = currentTime;
        if(thumbState==3&&indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3&&angleX>0&&angleX<180&&angleY>-70&&angleY<0&&angleZ>90&&angleZ<150&&timeDiff>=1000)
        {
           mp3.playTrackNumber(6,30);//This track(6) will play the "не"
        }
      }
    }
    else if(thumbState==1&&indexState == 1 && middleState == 2 && ringState == 2 && pinkyState == 2&&angleX>0&&angleX<180&&angleY>-70&&angleY<0&&angleZ>90&&angleZ<150)
    {
       if (timeDiff >= 100)
      {
        if(thumbState==1&&indexState == 1 && middleState == 2 && ringState == 2 && pinkyState == 2&&angleX>-150&&angleX<-40&&angleZ>50&&angleZ<90&&timeDiff>=1000)
        {
           mp3.playTrackNumber(8,30);//This track(8) will play the word "да"
        }
      }
    }
    
    // Check if the finger states are as desired and enough time has passed
    else if (thumbState == 2 && indexState == 3 && middleState == 3 && ringState == 3 && pinkyState == 3&&angleX>90 && timeDiff >= 1000) {
         mp3.playTrackNumber(9,30);//This track(9) will play the letter "a"
    }

    // Check if the finger states are as desired and enough time has passed
    else if (thumbState == 3 && indexState == 1 && middleState == 2 && ringState == 3 && pinkyState == 3&&angleX>90&& timeDiff >= 1000) {
        mp3.playTrackNumber(10,30);//This track(10) will play the letter "б"
    }

    else if (thumbState == 1 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1 &&angleX>90&& timeDiff >= 1000) {
        mp3.playTrackNumber(11,30);//This track(11) will play the letter "в"
    }
    else if (thumbState == 1 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 &&angleX<-90&& timeDiff >= 1000) {
        mp3.playTrackNumber(12,30);//This track(12) will play the letter "г"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 3 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(13,30);//This track(13) will play the letter "д"
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2 &&angleX>90&& timeDiff >= 1000) {
        mp3.playTrackNumber(14,30);//This track(14) will play the letter "е"
    }
    else if (thumbState == 1 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(15,30);//This track(15) will play the letter "ж"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 2 && ringState == 2 && pinkyState == 2 &&angleX>90&& directionX=="Down") {
        if (timeDiff >= 100)
            {
               if (thumbState == 3 && indexState == 1 && middleState == 2 && ringState == 2 && pinkyState == 2 &&angleX>90&&timeDiff >= 1000){
                   mp3.playTrackNumber(16,30);//This track(16) will play the letter "з"
               }
            } 
    }
    else if (thumbState == 3 && indexState == 3 && middleState == 3 && ringState == 1 && pinkyState == 1 &&angleX>90&& timeDiff >= 1000) {
        mp3.playTrackNumber(17,30);//This track(17) will play the letter "и"
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 2 && ringState == 1 && pinkyState == 1 &&angleX>90&& timeDiff >= 1000) {
        mp3.playTrackNumber(18,30);//This track(18) will play the letter "й"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 3 &&angleX>90) {
      if (timeDiff >= 100)
            {
               if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 3 &&angleY>90&&timeDiff >= 1000){
                   mp3.playTrackNumber(19,30);//This track(19) will play the letter "к"
               }
            }   
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 3 && angleX < -90 && timeDiff >= 1000) {
        mp3.playTrackNumber(20,30);//This track(20) will play the letter "л"
    }
    else if (thumbState == 2 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 && angleX >90 && timeDiff >= 1000) {
        mp3.playTrackNumber(21,30);//This track(21) will play the letter "м"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 3 && pinkyState == 1 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(22,30);//This track(22) will play the letter "н"
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 1 && ringState == 1 && pinkyState == 1 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(23,30);//This track(23) will play the letter "о"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 1 && angleX <-90 && timeDiff >= 1000) {
        mp3.playTrackNumber(24,30);//This track(24) will play the letter "п"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 2 && ringState == 1 && pinkyState == 1 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(25,30);//This track(25) will play the letter "р"
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(26,30);//This track(26) will play the letter "с"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 && angleX < -90 && timeDiff >= 1000) {
        mp3.playTrackNumber(27,30);//This track(27) will play the letter "т"
    }
    else if (thumbState == 1 && indexState == 3 && middleState == 3 && ringState == 3 && pinkyState == 1 &&angleX>90&& timeDiff >= 1000) {
        mp3.playTrackNumber(28,30);//This track(28) will play the letter "у"
    }
    else if (thumbState == 2 && indexState == 2 && middleState == 2 && ringState == 2 && pinkyState == 2 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(29,30);//This track(29) will play the letter "ф"
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 3 && ringState == 3 && pinkyState == 3 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(30,30);//This track(30) will play the letter "х"
    }
    else if (thumbState == 1 && indexState == 1 && middleState == 1 && ringState == 2 && pinkyState == 2 &&angleX>90 && directionX=="Down") {
            if (thumbState == 1 && indexState == 1 && middleState == 1 && ringState == 2 && pinkyState == 2 &&angleX>90 && timeDiff >= 1000) {
               mp3.playTrackNumber(31,30);//This track(31) will play the letter "ц"
            }
    }
    else if (thumbState == 1 && indexState == 2 && middleState == 3 && ringState == 3 && pinkyState == 3 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(32,30);//This track(32) will play the letter "ч"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 &&angleX>90 && timeDiff >= 1000) {
        mp3.playTrackNumber(33,30);//This track(11) will play the letter "ш"
    }
    else if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 &&angleX>90&& directionX=="Down" ) {
             if (thumbState == 3 && indexState == 1 && middleState == 1 && ringState == 1 && pinkyState == 3 &&angleX>90 &&timeDiff >= 1000) {
                 mp3.playTrackNumber(34,30);//This track(34) will play the letter "щ"
             }
    }
    else if (thumbState == 1 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 &&angleX>90) {
            if (timeDiff >= 100)
            {
               if (thumbState == 1 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 &&angleZ>90&&timeDiff >= 1000){
                   mp3.playTrackNumber(35,30);//This track(35) will play the letter "ъ"
               }
            }       
    }
    else if (thumbState == 1 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 &&angleZ>90) {
      
            if (timeDiff >= 100)
            {
               if (thumbState == 1 && indexState == 1 && middleState == 3 && ringState == 3 && pinkyState == 3 &&angleX>90&&timeDiff >= 1000){
                   mp3.playTrackNumber(36,30);//This track(36) will play the letter "ь"
               }
            }   
    }
    else if (thumbState == 3 && indexState == 3 && middleState == 3 && ringState == 3 && pinkyState == 1 &&angleX>90 && timeDiff >= 1000) {
       mp3.playTrackNumber(37,30);//This track(37) will play the letter "ю"
    }
    else if (thumbState == 3 && indexState == 2 && middleState == 2 && ringState == 3 && pinkyState == 3 &&angleX>90 && timeDiff >= 1000) {
       mp3.playTrackNumber(38,30);//This track(38) will play the letter "я"
    }
}
