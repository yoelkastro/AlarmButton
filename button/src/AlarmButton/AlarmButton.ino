#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <NetworkData.ino>

const int buttonPin = 16;
const int ledPin =  12;

AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

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
    
    while(!digitalRead(buttonPin));
    
    digitalWrite(ledPin, LOW);

    request->send(200, "text/plain", "OK");
  });
  // TO-DO: Implement async alarm stopped for response not received

  server.begin();
}

void loop() {}
