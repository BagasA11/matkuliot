/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6iZDAhTBB"
#define BLYNK_TEMPLATE_NAME "random sensor"
#define BLYNK_AUTH_TOKEN "VG6oaox5PkUZOpe8f67_HbKjxzOBGIf-"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
// # include <Arduino_LED_Matrix.h>
// #include <ArduinoGraphics.h>
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "UDINUS H3";
char pass[] = "";

// data from blynk
// BlynkTimer timer;
BlynkTimer timer;

void sendRandomValues() {
  int value1 = random(0, 101);
  int value2 = random(100, 201);

  Blynk.virtualWrite(V1, value1);
  Blynk.virtualWrite(V2, value2);
}

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000, sendRandomValues);
}

void loop() {
  Blynk.run();
  timer.run();
}
