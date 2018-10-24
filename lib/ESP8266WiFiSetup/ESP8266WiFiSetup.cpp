#include <ESP8266WiFiSetup.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

void ESP8266WiFiSetup::setup()
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
