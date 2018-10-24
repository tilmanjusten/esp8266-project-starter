#ifndef ESP8266_OTA_SETUP_h
#define ESP8266_OTA_SETUP_h

#include <Arduino.h>
#include <inttypes.h>
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef OTA_PORT
#define OTA_PORT 8266
#endif

#ifndef OTA_HOSTNAME
#define OTA_HOSTNAME "ploing"
#endif

#ifndef OTA_PASSWORD
#define OTA_PASSWORD ""
#endif

class ESP8266OTASetup
{
public:
  void setup();
  void handle();
};

#endif
