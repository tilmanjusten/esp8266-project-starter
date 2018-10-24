#include "secrets.h"
#include <Arduino.h>
#include <ESP8266WiFiSetup.h>
#include <ESP8266OTASetup.h>
#include <ESP8266SmartHomeWebserver.h>

ESP8266WiFiSetup wifi;
ESP8266OTASetup ota;
ESP8266SmartHomeWebserver webserver;

void webserverSetup()
{
    // init server
    webserver.setup();

    // do some additional requests
    webserver.on("/new", []() {
        webserver.send(200, "text/plain", "hello world!");
    });
}

void setup()
{
    Serial.begin(115200);
    delay(10);

    // WiFi
    wifi.setup();

    // OTA
    ota.setup();

    // Webserver
    webserverSetup();
}

void loop()
{
    // OTA
    ota.handle();

    // Webserver
    webserver.handle();
}
