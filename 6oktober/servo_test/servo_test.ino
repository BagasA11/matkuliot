#include "ESP32Servo.h"
#define PIN 13

Servo myServo;

int step=0, maxStep=7;
int anglePerStep=30;


void setup() {
  // put your setup code here, to run once:
  myServo.attach(PIN);
  Serial.begin(9600);
  myServo.write(0);
  delay(10*1000);
}

void loop() {
  // put your main code here, to run repeatedly:
 if(step<maxStep){
  int angle=step*anglePerStep;
  Serial.print(step);Serial.print(", ");
  Serial.println(angle);
  if(step<=180){
    myServo.write(angle);
  }else{
    myServo.write(angle-180);
  }
  step++;
 } else{
  step=0;
 }

  delay(1000);
}
