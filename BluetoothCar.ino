
#define IN1 2
#define IN2 3
#define IN3 10
#define IN4 11

#define BT_TX 13
#define BT_RX 12

int intData[2];
boolean recievedFlag;
int dutyRight, dutyLeft;
int dataX, dataY;

#include "Motor.h"
Motor motorLeft(IN1, IN2);
Motor motorRight(IN3, IN4);

#include <SoftwareSerial.h>
SoftwareSerial btSerial(12, 13);

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop() {
  parsing();
  if (recievedFlag) {
    recievedFlag = false;
    dataX = intData[0];
    dataY = intData[1];
  }

  if (dataX == 0 && dataY == 0) {
    motorRight.setMode(STOP);
    motorLeft.setMode(STOP);
    dutyRight = 0;
    dutyLeft = 0;
  } else {
    
    dutyRight = (dataY + dataX);
    dutyLeft = (dataY - dataX);
    
    Serial.print(dutyRight);
    Serial.print(" ");
    Serial.println(dutyLeft);

    if (dutyRight > 0) motorRight.setMode(FORWARD);
    else motorRight.setMode(BACKWARD);

    if (dutyLeft > 0) motorLeft.setMode(FORWARD);
    else motorLeft.setMode(BACKWARD);
    
    dutyRight = interval(abs(dutyRight), 0, 255);
    dutyLeft = interval(abs(dutyLeft), 0, 255);
  }
  motorRight.setSpeed(dutyRight);
  motorLeft.setSpeed(dutyLeft);
}

int interval(int value, int minVal, int maxVal){
  if(value > maxVal){
    return maxVal;
  }else if(value < minVal){
    return minVal;
  }else{
    return value;
  }
}

boolean getStarted;
byte index;
String string_convert = "";
void parsing() {
  if (btSerial.available() > 0) {
    char incomingByte = btSerial.read();

     if (incomingByte == '$') {
      getStarted = true;
      index = 0;
      string_convert = "";
      incomingByte = btSerial.read();
     }
    
    if (getStarted) {
      if (incomingByte != ' ' && incomingByte != ';') {
        string_convert += incomingByte;
      } else {
        intData[index] = string_convert.toInt();
        string_convert = "";
        index++;
      }
    }

    if (incomingByte == ';') {
      getStarted = false;
      recievedFlag = true;
    }
    
  }
}
