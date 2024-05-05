#include <Servo.h>

Servo UDservo;  // create servo object to control a servo
Servo LRservo;

#define LDR1 A2 // Up
#define LDR2 A3 // Right
#define LDR3 A4 // Down
#define LDR4 A5 // Left

bool ldr1, ldr2, ldr3, ldr4;
int LRpos, UDpos;

void setup() {
  Serial.begin(9600);
  Serial.print("Recalibrating... Begin");
  pinMode(LDR2, INPUT);
  pinMode(LDR4, INPUT);
  pinMode(LDR1, INPUT);
  pinMode(LDR3, INPUT);
  UDservo.attach(10);
  LRservo.attach(9);
  UDservo.write(90);
  LRservo.write(90);
  UDpos = 90;
  LRpos = 90;
}

const int step_size = 10;
void loop() {
  ldr2 = !digitalRead(LDR2); // RIGHT
  ldr4 = !digitalRead(LDR4); // LEFT
  // 1 is light, 0 is dark

  Serial.print("[ " + String(ldr2) + " , " + String(ldr4) + " ]");
  if(ldr4 > ldr2){
    if(LRpos < 180){
      LRpos += step_size;
      Serial.print("\tMoving right " + String(LRpos));
      LRservo.write(LRpos);
    }
  }
  if(ldr4 < ldr2){
    if(LRpos > 0){
      LRpos -= step_size;
      Serial.print("\tMoving left " + String(LRpos));
      LRservo.write(LRpos);
    }
  }
  if(ldr1 < ldr3){
    if(LRpos > 45){
      UDpos += step_size;
      Serial.print("\tMoving up " + String(LRpos));
      UDservo.write(UDpos);
    }
  }
  if(ldr1 > ldr3){
    if(LRpos > 135){
      UDpos -= step_size;
      Serial.print("\tMoving down " + String(LRpos));
      UDservo.write(UDpos);
    }
  }
  Serial.print("\n");
  delay(1000);
}

