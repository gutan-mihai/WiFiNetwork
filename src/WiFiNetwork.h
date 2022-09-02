#define WN_AP_NAME "ESP8266 Config"
#define WN_AP_PASS "31415926"
#define WN_AP_IP 192,168,1,1

#ifndef _WiFiNetwork_h
  #define _WiFiNetwork_h
  #include <DNSServer.h>
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  #include <EEManager.h>
  #include "extras/WiFiNetwork.template.h"

  class WiFiNetwork
  {
    public:
      WiFiNetwork();
      WiFiNetwork(byte eeprom_addr);

      void start();
      bool tick();

    private:
      EEManager *_memory;

      byte _eeprom_addr = 0;
      bool _started = false;
      byte _status = 0;

      void init();
      void connect(bool saveCredentials);
      bool reconnect();
      void stop();

      // HTTP Server Methods
      void handleRoot();
      void handleSaveForm();
      void handleReset();
  };
#endif