#include <WiFi.h> 
#include <WebServer.h>

const char* ssid="WARTEL_DURA";
const char* pw="DURA8442118";

WebServer server(80);

int counter=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  // connect widi
  WiFi.begin(ssid, pw);
  Serial.print("connecting wifi");
  while(WiFi.status()!=WL_CONNECTED){
    Serial.println(".");
  }
  Serial.print("connected ");
  Serial.print(WiFi.localIP());

  // handle on connect and not found
  server.on("/", handleOnConnect);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("http server started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

void handleOnConnect(){
  counter++;
  server.send(200, "text/html", createHtml(counter));
}

void handleNotFound() {
  server.send(404, "text/plain", "Not found");
}

String createHtml(int counter){
  String page="<!DOCTYPE html><html>";
  page+="<head>";
  page+="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">";
  page+="<style>";
  page+="body {font-family: Arial, sans-serif; color: #444; text-align: center;}";
  page+=".title {font-size: 30px; font-weight: bold; letter-spacing: 2px; margin: 80px 0 55px;}";
  page+=".counter {font-size: 80px; font-weight: 300; line-height: 1; margin: 0px; color: #4285f4;}";
  page+="</style>";
  page+="</head>";
  page+="<body>";
  page+="<h1 class=\"title\">Visitor Counter</h1>";
  page+="<div> class=\"counter\"";
  page+=String(counter);
  page+="</div>";
  page+="</body>";
  page+="</html>";
  return page;
}