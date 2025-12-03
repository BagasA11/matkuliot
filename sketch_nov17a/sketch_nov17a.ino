
// #include <WiFiManager.h>
#include <WebServer.h>
#include <WiFi.h>
// #include "secrets.h"
#include "IPAddress.h"
const char* ssid="iot-bagas";
const char* pwd="bagas1234";


WebServer server(80);

byte ledStatus = HIGH;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(15, OUTPUT);
  WiFi.softAP(ssid, pwd);

  IPAddress myIP=WiFi.softAPIP();
  Serial.print("ap ip="); Serial.println(myIP);

  server.on("/", handle_OnConnect);
  server.on("/", handle_NotFound);

  server.on("/led-on", handle_ledON);
  server.on("/led-off", handle_ledOFF);

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  if(ledStatus == HIGH){
    digitalWrite(15, LOW);
  }else{
    digitalWrite(15, HIGH);
  }

}

void handle_OnConnect(){
  ledStatus=LOW;
  server.send(200, "text/html", updateWebPage(ledStatus));
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not Found");
}

String updateWebPage(byte ledStatus){
  // String page="<h1>welcome</h1>";
  String page;
  page+="    <html>";
  page+="    <head>";
  page+="        <meta charset=\"UTF-8\">";
  page+="        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
  page+="        <title>Document</title>";
  page+="        <style>";
  page+="            html{";
  page+="                font-family: Arial, Helvetica, sans-serif;";
  page+="                display: inline-block;";
  page+="                margin: 0px auto;";
  page+="                text-align: center;";
  page+="            }";
  page+="            body{";
  page+="                margin-top: 50px;";
  page+="            }";
  page+="            h1{";
  page+="                color: rgba(4, 7, 12, 0.7);";
  page+="                margin: 50px auto 30px;";
  page+="            }";
  page+="            ";
  page+="            .button-on{";
  page+="                background-color: lightblue;";
  page+="            }";
  page+="            ";
  page+="            .button-on:active{";
  page+="                background-color: rgb(112, 184, 209);";
  page+="            }";
  page+="            .button-off{";
  page+="                background-color: lightgrey;";
  page+="            }";
  page+="            .button-off:active{";
  page+="                background-color: rgb(174, 174, 174);";
  page+="            }";
  page+="    ";
  page+="            p{";
  page+="                font-size: 14px;";
  page+="                color: #888;";
  page+="                margin-bottom: 10px;";
  page+="            }";
  page+="        </style>";
  page+="    </head>";
  page+="    <body>";
  page+="        <h1>kontrol led dengan web ap</h1>";

  if (ledStatus==HIGH){
    page+="        <p>led on</p>";
    page+="        <a class=\"button button-off\" href=\"/led-off\">led off</a>";
  } 
  // page+="        <br>";
  else{
    page+="        <p>led off</p>";
    page+="        <a class=\"button button-on\" href=\"/led-on\">led off</a>";
  }
  page+="    </body>";
  page+="    </html>";
  return page;
}

void handle_ledON(){
  ledStatus=HIGH;
  Serial.println("ledstatus:ON");
  server.send(200, "text/html", updateWebPage(ledStatus));
}

void handle_ledOFF(){
  ledStatus=LOW;
  Serial.println("ledstatus:OFF");
  server.send(200, "text/html", updateWebPage(ledStatus));
}