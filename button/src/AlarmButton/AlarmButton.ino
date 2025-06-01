#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <NetworkData.ino>

const int buttonPin = 32;
const int ledPin =  12;

AsyncWebServer server(80);

void IRAM_ATTR handleInterrupt() {
  digitalWrite(ledPin, !digitalRead(ledPin));
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, RISING);

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Server endpoint for handshake
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "OK");
  });

  server.on("/startAlarm", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "OK");
  });

  server.on("/stopAlarm", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {}
