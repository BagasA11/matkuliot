const char* ssid = "WARTEL_DURA";
const char* password = "DURA8442118";

const char* serverName = "http://192.168.1.5:8080/led/state";






#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

// Ganti dengan SSID dan password WiFi kamu
/*
const char* ssid = "wifi-name";
const char* password = "wifi-password";

const char* serverName = "http://localip():8080/led/state";

*/

unsigned long timepoint = 0;

int ledPIN[4]={15, 2, 4, 5};
String ledState[]= {"off", "off", "off", "off"};

void setup() {
  Serial.begin(115200);
  for(int i=0; i<4;i++){
    pinMode(ledPIN[i], OUTPUT);
  }

  delay(1000);

  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);

  // Tunggu hingga terhubung
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi terhubung!");
  Serial.print("Alamat IP: ");
  Serial.println(WiFi.localIP());
  timepoint = millis();
}

String httpGETRequest(const char* serverName){
  HTTPClient http;
  http.begin(serverName);
  int httpCode = http.GET();
  String payload;
  if ((httpCode > 0) && (httpCode == 200)){
    payload = http.getString();
    Serial.print("response code: "); Serial.println(httpCode);

  } else{
    Serial.print("error code: "); Serial.println(httpCode);
  }
  http.end();
  return payload;
}

byte stateToDigital(String state){
  // String on = "on";
  state.toLowerCase();
  if(state == "on"){
    return HIGH;
  } else{
    return LOW;
  }
}

void toggleLED(String state, int PIN){
  digitalWrite(PIN, stateToDigital(state));
}

void loop() {
  if(millis() - timepoint > 5000){
    timepoint=millis();
    if(WiFi.status() == WL_CONNECTED){
      String payload = httpGETRequest(serverName);
      JSONVar myobject = JSON.parse(payload);

      if (JSON.typeof(myobject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
      JSONVar mydata=myobject["data"];
      for(int i=0; i<4; i++){
        JSONVar row = mydata[i];
        String status=row["status"];
        ledState[i]=status;
        Serial.println(ledState[i]);
      }
      
      // Serial.println(ledState);

    }

  }

  for(int i=0; i<4; i++){
    toggleLED(ledState[i], ledPIN[i]);
  }
}
