#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <NetworkData.ino>

const int buttonPin = 32;
const int ledPin =  12;

AsyncWebServerRequest *curRequest = NULL;

AsyncWebServer server(80);

void IRAM_ATTR handleInterrupt() {
  if(curRequest != NULL){
    digitalWrite(ledPin, LOW);
    curRequest->send(200, "text/plain", "OK");
    curRequest = NULL;
  }
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
    digitalWrite(ledPin, HIGH);
    curRequest = request;
  });

  // TO-DO: Implement async alarm stopped for response not received

  server.begin();
}

void loop() {}
