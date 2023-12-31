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
  String str = "<!DOCTYPE html> <html>\n";
  str +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  str +="<title>LED Control</title>\n";
  str +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  str +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  str +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  str +="</style>\n";
  str +="</head>\n";
  str +="<body>\n";
  str +="<h1>ESP32 Web Server</h1>\n";

  // Adding the control buttons
  str +="<a href=\"/?command=open\">OPEN</a>\n";
  str +="<a href=\"/?command=close\">CLOSE</a>\n";

  str +="</body>\n";
  str +="</html>\n";
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