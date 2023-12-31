#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

/* Servo pin definitions */
#define servoPin 15

/* Declaring the servo objects */
Servo servo;

/* Network credentials */
const char* ssid = "espwifipoint";
const char* password = "password";

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

/* Creating the server object with the port (HTTP default is 80 typically) */
AsyncWebServer server(80);

/* Structures a HTML webpage to send to a client */
String SendHTML(){
  String str = "<!DOCTYPE html><html><head><title>QuadruBot</title><style>html{font-family:Helvetica;}a{background-color:rgb(238,183,0);color:black;width:10vw;height:10vw;display:flex;align-items:center;justify-content:center;text-decoration:none;font-size:2vw;}body{background-color:rgb(93,93,93);display:flex;flex-direction:column;}.wrapper{display:flex;flex-direction:row;gap:2rem;margin:auto;}h1{color:white;align-self:center;}</style></head><body><h1>QuadruBotControlServer</h1><div class=\"wrapper\"><a href=\"/?command=open\">OPEN</a><a href=\"/?command=close\">CLOSE</a></div></body></html>";
  return str;
}

/* Called when a GET request is receieved from client, handles servo control */
void handleRoot(AsyncWebServerRequest *request) {
  request->send(200, "text/html", SendHTML());
  String command = request->arg("command");
  Serial.println(command);
  if (command == "open") {
    servo.write(120);
    request->send(200, "text/plain", "Servo opened");
  } else if (command == "close") {
    servo.write(60);
    request->send(200, "text/plain", "Servo closed");
  } else {
    request->send(400, "text/plain", "Invalid command");
  }
}

void setup() {
  Serial.begin(9600);

  // Creating the access point
  Serial.println("\n[*] Creating AP");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.print("[+] AP Created with IP Gateway ");
  Serial.println(WiFi.softAPIP());

  // Attaching the servo control to pins
  servo.attach(servoPin);

  // Setup the HTTP server to call this function when a HTTP GET request is received
  server.on("/", HTTP_GET, handleRoot);

  // Starting the web server
  server.begin();

  // Print ESP32 IP address to monitoring terminal
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // servo.write(120);
  // delay(1000);
  // servo.write(60);
  // delay(1000);
  delay(10);
}