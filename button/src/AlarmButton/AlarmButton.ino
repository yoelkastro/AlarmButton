#include <WiFi.h>
#include <AsyncTCP.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <NetworkData.ino>

const int buttonPin = 16;
const int ledPin =  12;

String requestIp;
String REQUEST_PATH = "/stopAlarm";
bool isWaiting = false;

AsyncWebServer server(80);

void blinkLed() {
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(50);
}

void IRAM_ATTR handleButtonPress() {
    if(isWaiting) {
      HTTPClient http;
      http.begin(requestIp + REQUEST_PATH);

      int response = http.GET();
      while(response != HTTP_CODE_OK) {
        response = http.GET();
        delay(250);
      }

      requestIp = "";
      isWaiting = false;
      digitalWrite(ledPin, LOW);
    }
}

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, RISING);

  // Signal setup complete
  blinkLed();

  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Signal Wifi connected
  blinkLed();
  blinkLed();

  // Server endpoint for handshake
  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "OK");
  });

  server.on("/startAlarm", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(ledPin, HIGH);
    
    requestIp = request->client()->remoteIP().toString();
    isWaiting = true;

    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {}
