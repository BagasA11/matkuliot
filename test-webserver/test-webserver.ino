#include <WiFi.h>

const char* ssid = "WARTEL_DURA";
const char* password = "DURA8442118";

#define ledPin 15

WiFiServer server(80);
String header;

String ledState="OFF";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPin, 15);
  digitalWrite(ledPin, LOW);
  
  // connect to wifi
  Serial.print("connecting to");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
  }
    // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server.available(); //listen for incoming client
  if(client){ //if new client incoming
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client

    while(client.connected() && currentTime - previousTime < timeoutTime){
      currentTime = millis();
      if(client.available()){
        char c = client.read();
        Serial.write(c);
        header += c;

        if(c=='\n'){
          if(currentLine.length() == 0){
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // if(header.indexOf("GET /led/on")>=0){
            //   Serial.println("GPIO 26 on");
            //   // Serial.println("GPIO 26 off");
            //   ledState = "ON";
            //   digitalWrite(ledPin, HIGH);
            // } else if (header.indexOf("GET /led/off") >= 0){
            //   Serial.println("GPIO 26 off");
            //   ledState = "OFF";
            //   digitalWrite(ledPin, LOW);
            // }
            client.println("<p>hello world</p>");
            client.println();
            break;
          } else{
            currentLine = "";
          }
        } else if(c!='\r'){
          currentLine += c;
        }


        
      }
    }
        // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");

  }


}
