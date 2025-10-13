#include "ESP32Servo.h"
#define PIN 13
#define LED 12
#define BUZZ 14
#define SERVO 5

Servo myServo;
byte lastLdrstate = LOW;
unsigned long oneSecond=0;

// void ledBlink(int ledPin){
//   digitalWrite(ledPin, LOW);
//   digitalWrite(ledPin, HIGH);
//   delay(100);
//   digitalWrite(ledPin, LOW);
//   delay(100);
// }

// void ledBuzzBlink(int ledPin){
//   // tone(buzz, 1535, 100);
//   digitalWrite(ledPin, LOW);
//   digitalWrite(ledPin, HIGH);
//   delay(100);
//   digitalWrite(ledPin, LOW);
//   delay(100);
// }

void setup() {
  // put your setup code here, to run once:
  myServo.attach(SERVO);
  Serial.begin(9600);
  pinMode(PIN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  digitalWrite(LED, LOW);
  oneSecond=millis();
  for(int i=0; i<18; i++){
    myServo.write(i*10);
    delay(500);
  }
  for(int i=0; i<10; i++){
    myServo.write(0);
    delay(100);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  // delay(1000)
  if(millis()-oneSecond>=1000){
    oneSecond=millis();
    lastLdrstate=digitalRead(PIN);
    // lastLdrstate=!lastLdrstate;
    
    Serial.println(lastLdrstate);
    // Serial.println("buzz");
    // if(lastLdrstate==HIGH){
      
    // }
  }
  // gelap tidak menerima cahaya
  if(lastLdrstate==HIGH){
    tone(BUZZ,700, 500);
    digitalWrite(LED,LOW);
    noTone(BUZZ);
    myServo.write(90);
  } else {
    // terang 
    digitalWrite(LED,HIGH);
    noTone(BUZZ);
    myServo.write(0);
  }
  // noTone(BUZZ);
}
