#include "secrets.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266OTASetup.h>
#include <ESP8266SmartHomeWebserver.h>

ESP8266OTASetup ota;
ESP8266SmartHomeWebserver webserver;

void wifiSetup()
{
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to: ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.print("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

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
    wifiSetup();

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
