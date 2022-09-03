#include <ESP8266WiFi.h>
#include <WiFiNetwork.h>

// create global WiFiNetwork instance
WiFiNetwork network;

unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);

  // start WiFi access point
  network.start();
}

void loop() {
  // tick wifi network
  network.tick();

  // displat network status every 5 seconds
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 5000) {
    Serial.printf("WiFi status: %d\n", WiFi.status()); // wifi status
    Serial.println(WiFi.SSID().c_str()); // wifi SSID name
    Serial.println(WiFi.localIP()); // wifi IP
    previousMillis = currentMillis;
  }
}