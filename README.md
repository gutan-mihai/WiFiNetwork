# WiFiNetwork
Library to work with WiFi in ESP8266

## How It Works
- when your ESP starts up, it sets it up in Station mode and tries to connect to a previously saved Access Point
- if this is unsuccessful (or no previous network saved) it moves the ESP into Access Point mode and spins up a DNS and WebServer with name `ESP8266 Config` and password `31415926` (default ip 192.168.1.1)
- using any wifi enabled device with a browser (computer, phone, tablet) connect to the newly created Access Point
- indicate ssid of any access point, enter password, click Try connect
- ESP will try to connect. If successful, it relinquishes control back to your app. If not, reconnect to AP and reconfigure

## Structure
```cpp
// start WiFi access point
void start();

// handle server client and process DNS request
bool tick();
```

## Example
```cpp
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
```