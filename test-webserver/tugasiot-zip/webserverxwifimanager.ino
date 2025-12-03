#include <WiFiManager.h>
#include <WebServer.h>

#define PIN 15

byte ledState=LOW;
bool status=false;//default off -> false

const char* ssid="test";
const char* pw="test";

WebServer server(80);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PIN, OUTPUT);
  // digitalWrite(PIN, HIGH);
  WiFiManager wm;
  wm.resetSettings();
  bool res;
    // res = wm.autoConnect(); // auto generated AP name from chipid
    // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("test","test1234"); // password protected ap
  if(!res) {
      Serial.println("Failed to connect");
      // ESP.restart();
  } 
  else {
    //if you get here you have connected to the WiFi    
    Serial.println("connected...yeey :)");
  }

  server.on("/", handleOnConnect);
  server.on("/on", handle_ledON);
  server.on("/off", handle_ledOFF);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("http server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handleOnConnect(){
  server.send(200, "text/html", createHtml(status));
}

void handleNotFound(){
  server.send(404, "text/plain", "not found");
}

void handle_ledON(){
  status=true;
  digitalWrite(PIN, HIGH);
  server.send(200, "text/html", createHtml(status));
}

void handle_ledOFF(){
  status=false;
  digitalWrite(PIN, LOW);
  server.send(200, "text/html", createHtml(status));
}


String createHtml(bool status){
  String page;
  page+="<!DOCTYPE html>";
  page+="<html lang=\"id\">";
  page+="<head>";
  page+="<meta charset=\"UTF-8\">";
  page+="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  page+="<title>Web Kontrol LED</title>";
  page+="<style>";
  page+="    body {";
  page+="        font-family: Arial, sans-serif;";
  page+="        display: flex;";
  page+="        flex-direction: column;";
  page+="        align-items: center;";
  page+="        justify-content: flex-start;";
  page+="        height: 100vh;";
  page+="        margin: 0;";
  page+="        background: white;";
  page+="    }";
  page+="    h1 {margin-top: 60px;font-size: 48px;font-weight: 800;}";
  page+="    .section {";
  page+="        margin-top: 20px;text-align: center;";
  page+="        font-size: 32px;font-weight: 700;";
  page+="        display: flex;flex-direction: column;";
  page+="        align-items: center;justify-content: center;}";
  page+="    .btn {display: inline-block;margin-top: 20px;";
  page+="        width: 280px;padding: 35px 0;";
  page+="        font-size: 32px;font-weight: 500;color: white;";
  page+="        text-align: center;text-decoration: none;";
  page+="        border-radius: 5px;cursor: pointer;}";
  page+="    .btn-off {background: #6e6e6e;}";
  page+="    .btn-on {background: #89e665;}";
  page+="</style></head>";
  page+="<body>";
  page+="    <h1>WEB KONTROL LED</h1>";

  if (status){
    page+="    <div class=\"section\">";
    page+="        LED nyala";
    page+="        <a href=\"/off\" class=\"btn btn-off\">OFF</a>";
    page+="    </div>  ";
  } else{
    page+="    <div class=\"section\">";
    page+="        LED mati";
    page+="        <a href=\"/on\" class=\"btn btn-on\">ON</a>";
    page+="    </div>";
  }
  page+="</body></html>";

  return page;
}