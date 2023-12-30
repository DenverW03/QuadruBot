#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

#define servoPin 15

Servo servo;
const char* ssid = "espwifipoint";
const char* password = "password";

AsyncWebServer server(80);

void handleRoot(AsyncWebServerRequest *request) {
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

  // Setup the HTTP server
  server.on("/", HTTP_GET, handleRoot);
  server.begin();

  // Print ESP32 IP address
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