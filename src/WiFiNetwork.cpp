#include "WiFiNetwork.h"
static DNSServer dnsServer;
static ESP8266WebServer server(80);

struct WiFiNetworkCfg {
  char ssid[32] = "";
  char pass[32] = "";
};
WiFiNetworkCfg wiFiNetworkCfg;

WiFiNetwork::WiFiNetwork() {
  init();
}

WiFiNetwork::WiFiNetwork(byte eeprom_addr) {
  _eeprom_addr = eeprom_addr;
  init();
}

void WiFiNetwork::init() {
  _memory = new EEManager(wiFiNetworkCfg, 512);
  _memory->begin(_eeprom_addr, 'w');
}

void WiFiNetwork::start() {
  if (reconnect()) {
    return;
  }

  WiFi.softAPdisconnect();
  WiFi.disconnect();
  IPAddress apIP(WN_AP_IP);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, subnet);
  WiFi.softAP(WN_AP_NAME, WN_AP_PASS);
  dnsServer.start(53, "*", apIP);
  server.on("/", std::bind(&WiFiNetwork::handleRoot, this));
  server.on("/save-credits", HTTP_POST, std::bind(&WiFiNetwork::handleSaveForm, this));
  server.on("/reset", HTTP_POST, std::bind(&WiFiNetwork::handleReset, this));
  server.onNotFound(std::bind(&WiFiNetwork::handleRoot, this));
  server.begin();

  _started = true;
  _status = 0;
}

bool WiFiNetwork::tick() {
  if (_started) {
    dnsServer.processNextRequest();
    server.handleClient();
    yield();

    if (_status) {
      stop();
      connect(true);

      return 1;
    }
  }

  return 0;
}

void WiFiNetwork::stop() {
  WiFi.softAPdisconnect();
  server.stop();
  dnsServer.stop();
  _started = false;
}

bool WiFiNetwork::reconnect() {
  _memory->read();
  if (wiFiNetworkCfg.ssid[0] != '\0') {
    _status = 1;
    connect(false);

    return 1;
  }

  return 0;
}

void WiFiNetwork::connect(bool saveCredentials) {
  if (_status != 1) {
    return;
  }

  WiFi.mode(WIFI_STA);
  if (wiFiNetworkCfg.pass[0] != '\0') {
    WiFi.begin(wiFiNetworkCfg.ssid, wiFiNetworkCfg.pass);
  } else {
    WiFi.begin(wiFiNetworkCfg.ssid);
  }

  uint32_t tmr = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (millis() - tmr > 15000) {
      break;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    _status = 2;
    WiFi.setAutoReconnect(true);
    WiFi.persistent(true);
    if (saveCredentials) {
      _memory->save();
    }
  } else {
    start();
  }
}

void WiFiNetwork::handleRoot() {
  server.send(200, "text/html", WN_Connect_Page);
}

void WiFiNetwork::handleSaveForm() {
  strcpy(wiFiNetworkCfg.ssid, server.arg("ssid").c_str());
  strcpy(wiFiNetworkCfg.pass, server.arg("pass").c_str());

  _status = 1;
}

void WiFiNetwork::handleReset() {
  _memory->reset();
  WiFi.disconnect();
}