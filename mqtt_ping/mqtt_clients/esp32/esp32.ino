#include "WiFi.h"
#include "PubSubClient.h"
#include <WebServer.h>
#include <ArduinoJson.h>

#define L1 15
#define L2 2
#define L3 4
#define L4 5

const char* ssid="WARTEL_DURA";
const char* pw="DURA8442118";
const char* mqtt_server = "test.mosquitto.org";

char *topic_in = "esp32/in";
char* topic_out="nodemcu/in";

WiFiClient espClient;
PubSubClient client(espClient);

int leds[]={(int)L1, (int)L2, (int)L3, (int)L4};
int led_input[]={LOW, LOW, LOW, LOW};

WebServer server(80);

void setup_wifi() {
  WiFi.begin(ssid, pw);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.print("connected ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) message += (char)payload[i];
    // Buat objek JSON
  StaticJsonDocument<200> doc; // ukuran buffer, sesuaikan dengan kompleksitas JSON
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.print(F("deserializeJson() gagal: "));
    Serial.println(error.f_str());
    return;
  }

  // Ambil array dari key "data"
  JsonArray dataArray = doc["data"];
  for (int i=0; i<dataArray.size();i++){
    int state=dataArray[i];
    digitalWrite(leds[i], state);
  }
}

void reconnect(){
  while (!client.connected()){
    if (client.connect("esp32")){
      client.subscribe(topic_in);
    } else{
      delay(700);
      Serial.print(".");
    }
  }
}

void publishState(){
  StaticJsonDocument<200> doc;
  JsonArray arr=doc.createNestedArray("data");
  for (int i=0; i<4; i++) {
    arr.add(led_input[i]);
  }
  char buffer[200];
  serializeJson(doc, buffer);
  client.publish(topic_out, buffer);
}

void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++){
    pinMode(leds[i], OUTPUT);
  }

  Serial.begin(115200);
  // connect widi
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

    // handle on connect and not found
  server.on("/", handleOnConnect);
  server.onNotFound(hadleNotFound);
  server.on("/led1", handle_L1);
  server.on("/led2", handle_L2);
  server.on("/led3", handle_L3);
  server.on("/led4", handle_L4);

  server.on("/on", handle_onall);
  server.on("/off", handle_ofall);

  server.begin();
  Serial.println("http server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!client.connected()) reconnect();
  client.loop();
  server.handleClient();
}

void handleOnConnect(){
  server.send(200, "text/html", HTML());
}

void hadleNotFound(){
  server.send(404, "text/plain", "not found");
}

void handle_L1(){
  int curr_state = led_input[0];
  led_input[0]=toggle_state(curr_state);
  for (int i=0; i<4;i++){
    Serial.print(led_input[i]);
    Serial.print(" ");
  }Serial.println();
  publishState();
  server.send(200, "text/html", HTML());
}
void handle_L2(){
  int curr_state = led_input[1];
  led_input[1]=toggle_state(curr_state);
  for (int i=0; i<4;i++){
    Serial.print(led_input[i]);
    Serial.print(" ");
  }Serial.println();
  publishState();
  server.send(200, "text/html", HTML());
}
void handle_L3(){
  int curr_state = led_input[2];
  led_input[2]=toggle_state(curr_state);
  for (int i=0; i<4;i++){
    Serial.print(led_input[i]);
    Serial.print(" ");
  }Serial.println();
  publishState();
  server.send(200, "text/html", HTML());
}
void handle_L4(){
  int curr_state = led_input[3];
  led_input[3]=toggle_state(curr_state);
  for (int i=0; i<4;i++){
    Serial.print(led_input[i]);
    Serial.print(" ");
  }Serial.println();
  publishState();
  server.send(200, "text/html", HTML());
}

void handle_onall(){
  for(int i=0;i<4;i++)led_input[i]=HIGH;
  for (int i=0; i<4;i++){
    Serial.print(led_input[i]);
    Serial.print(" ");
  }Serial.println();
  publishState();
  server.send(200, "text/html", HTML());
}
void handle_ofall(){
  for(int i=0;i<4;i++)led_input[i]=LOW;
  for (int i=0; i<4;i++){
    Serial.print(led_input[i]);
    Serial.print(" ");
  }Serial.println();
  publishState();
  server.send(200, "text/html", HTML());
}

int toggle_state(int val){
  if (val == LOW){
    return HIGH;
  } else{
    return LOW;
  }
}

String HTML(){
  String page ="";
  page+="<!DOCTYPE html><html lang=\"id\"><head>";
  page+="<meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  page+="<title>Panel Kontrol ESP32</title>";
  page+="<style>";
  page+="    body {";
  page+="        font-family: Arial, sans-serif;";
  page+="        display: flex;";
  page+="        flex-direction: column;";
  page+="        align-items: center;";
  page+="        margin: 0;";
  page+="        padding-top: 40px;";
  page+="        background: #ffffff;";
  page+="    }";
  page+="    h1 {";
  page+="        font-size: 48px;margin: 0;";
  page+="        font-weight: 700;";
  page+="        text-align: center;";
  page+="    }";
  page+="    h2 {";
  page+="        font-size: 44px; margin-top: 5px;font-weight: 700;text-align: center;";
  page+="    }";
  page+="    .main-container {";
  page+="        display: flex;gap: 100px;margin-top: 60px;";
  page+="        align-items: center;";
  page+="    }";
  page+="    .panel {";
  page+="        background: #efefef;";
  page+="        padding: 40px;";
  page+="        border-radius: 8px;";
  page+="        display: grid;";
  page+="        grid-template-columns: repeat(2, 180px);";
  page+="        grid-template-rows: repeat(2, 120px);";
  page+="        gap: 40px;";
  page+="    }";
  page+="    .led-box {";
  page+="        background: #5ee6ea;";
  page+="        border-radius: 6px;";
  page+="        display: flex;";
  page+="        align-items: center;";
  page+="        justify-content: center;";
  page+="        font-size: 28px;";
  page+="        font-weight: 700;";
  page+="        color: black;";
  page+="        text-decoration: none;"; /* hyperlink tanpa garis bawah */
  page+="    }";
  page+="    /* Tombol di sisi kanan */";
  page+="    .btn {";
  page+="        width: 250px;";
  page+="        padding: 32px 0;";
  page+="        margin: 20px 0;";
  page+="        text-align: center;";
  page+="        text-decoration: none;";
  page+="        color: white;";
  page+="        font-size: 32px;";
  page+="        font-weight: 600;";
  page+="        border-radius: 6px;";
  page+="        display: block;";
  page+="    }";
  page+="    .btn-off {";
  page+="        background: #6e6e6e;";
  page+="    }";
  page+="    .btn-on {";
  page+="        background: #8ae665;";
  page+="    }";
  page+="</style></head>";
  page+="<body>";
  page+="<h1>Panel Kontrol</h1><h2>ESP32</h2>";
  page+="<div class=\"main-container\">";
  page+="    <!-- PANEL LED 4 KOTAK -->";
  page+="    <div class=\"panel\">";
  page+="        <a href=\"/led1\" class=\"led-box\">LED 1</a>";
  page+="        <a href=\"/led2\" class=\"led-box\">LED 2</a>";
  page+="        <a href=\"/led3\" class=\"led-box\">LED 3</a>";
  page+="        <a href=\"/led4\" class=\"led-box\">LED 4</a>";
  page+="    </div>";
  page+="    <!-- PANEL TOMBOL ON / OFF -->";
  page+="    <div class=\"button-group\">";
  page+="        <a href=\"/off\" class=\"btn btn-off\">OFF</a>";
  page+="        <a href=\"/on\" class=\"btn btn-on\">ON</a>";
  page+="    </div>";
  page+="</div>";
  page+="</body></html>";
  return page;
}
