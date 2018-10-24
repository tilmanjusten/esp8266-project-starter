#ifndef ESP8266WiFiSetup_h
#define ESP8266WiFiSetup_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#ifndef WIFI_SSID
#define WIFI_SSID ""
#endif

#ifndef WIFI_PASS
#define WIFI_PASS ""
#endif

class ESP8266WiFiSetup
{
  public:
    void setup();
};

#endif