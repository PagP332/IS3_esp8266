#include <Servo.h>
//#include <Stream>
//#include <vector>
#include "ardToEsp.h"

Servo UDservo;  // create servo object to control a servo
Servo LRservo;

// LDR1 - A2
// LDR2 - A3
// LDR3 - A4
// LDR4 - A5

#define LDR1  A5 // Up A2
#define LDR2  A3 // Right A3
#define LDR3  A4 // Down A4
#define LDR4  A2 // Left A5

#define RXPIN A0
#define TXPIN A1
extern ESP serialESP(RXPIN, TXPIN, 9600);

bool ldr2, ldr4, ldr1, ldr3;
int LRpos, UDpos;

void setup() {
  Serial.begin(115200);
  Serial.print("Recalibrating... Begin");
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  pinMode(LDR3, INPUT);
  pinMode(LDR4, INPUT);
  UDservo.attach(9);
  LRservo.attach(10);
  UDservo.write(90);
  LRservo.write(90);
  UDpos = 90;
  LRpos = 90;
}
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
// void check_app(){
//   String recievedData = serialESP.readSerial();
//   Serial.print(recievedData);
// }
// int check_joystick(){
//   String recievedData = serialESP.readSerial();
//   Serial.println("\tRecieved: " + recievedData);
//   int joystickx = getValue(recievedData, ',' ,0).toInt();
//   int joysticky = getValue(recievedData, ',' ,1).toInt();
//   int remote_switch = getValue(recievedData, ',' ,2).toInt();
//   Serial.print(String(joystickx) + " " + String(joysticky) + " " + String(remote_switch));
// }

const int step_size = 10;
void moveUD(String direction){
  if(direction == "UP"){
    if(UDpos < 180){
      if (UDpos >= 160) UDpos = 160;
      else{
      UDpos += step_size;
      Serial.print("\tMoving up " + String(UDpos));
      UDservo.write(UDpos);
      }
    }
  }
  else if (direction == "DOWN"){
    if(UDpos > 0){
      if (UDpos <= 40) UDpos = 40;
      else{
      UDpos -= step_size;
      Serial.print("\tMoving down " + String(UDpos));
      UDservo.write(UDpos);
      }
    }
  }
}

void moveLR(String direction){
  if(direction == "RIGHT"){
    if(LRpos < 180){
      //if (LRpos >= 160) LRpos = 160;
      //else{
      LRpos += step_size;
      Serial.print("\tMoving right " + String(LRpos));
      LRservo.write(LRpos);
      //}
    }
  }
  else if(direction == "LEFT"){
    if(LRpos > 0){
      //if (LRpos <= 40) LRpos = 40;
      //else{
      LRpos -= step_size;
      Serial.print("\tMoving left " + String(LRpos));
      LRservo.write(LRpos);
      //}
    }
  }
}

void check_ldr(){
  ldr1 = !digitalRead(LDR1); // UP
  ldr2 = !digitalRead(LDR2); // RIGHT
  ldr3 = !digitalRead(LDR3); // DOWN
  ldr4 = !digitalRead(LDR4); // LEFT
  // 1 is light, 0 is dark

  Serial.print("[ " + String(ldr1) + " , " + String(ldr2) + " , " + String(ldr3) + " , " + String(ldr4) + " ]");
  if(ldr4 < ldr2){
    // right
    moveLR("RIGHT");
  }
  else if(ldr4 > ldr2){
    // left
    moveLR("LEFT");
  }

  else if(ldr3 < ldr1){
    // up
    moveUD("UP");
  }
  else if(ldr3 > ldr1){
    // down
    moveUD("DOWN");
  }

  Serial.print("\n");
}

int xyswitch;
void loop() {
  //check_app();
  check_ldr();
  delay(100);
  
}
