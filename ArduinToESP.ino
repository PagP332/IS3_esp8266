#include "ardToEsp.h"

#define RXPIN 2
#define TXPIN 3
extern ESP serialESP(RXPIN, TXPIN, 9600);

const int trigPin = 9;
const int echoPin = 10;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  
}

void loop() {
  distance = data();
  Serial.print("Distance: ");
  Serial.println(distance);
  String value = "Distance: " + String(distance) + "\n";
  serialESP.writeStr(value);
  delay(1000);
}

float data(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  return distance;
}