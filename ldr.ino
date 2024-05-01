#include <Servo.h>

Servo UDservo;  // create servo object to control a servo
Servo LRservo;

#define LDR2 A3 // Right
#define LDR4 A5 // Left

bool ldr2, ldr4;
int LRpos, UDpos;

void setup() {
  Serial.begin(9600);
  Serial.print("Recalibrating... Begin");
  pinMode(LDR2, INPUT);
  pinMode(LDR4, INPUT);
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
  Serial.print("\n");
  delay(1000);
}

