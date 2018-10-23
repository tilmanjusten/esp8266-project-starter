#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "secrets.h"

ESP8266WebServer server(HTTP_PORT);

void handleWebRequests404()
{
    String message = "File Not Detected\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";

    for (uint8_t i = 0; i < server.args(); i++)
    {
        message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
    }

    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.send(404, "text/plain", message);

    Serial.println(message);
}

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

void setupWebserver()
{
    if (MDNS.begin("Door Station"))
    {
        Serial.println("MDNS responder started");
    }

    // Overview
    server.serveStatic("/", SPIFFS, "/www/index.html");
    server.serveStatic("/index.html", SPIFFS, "/www/index.html");
    server.serveStatic("/styles.css", SPIFFS, "/www/styles.css");
    server.serveStatic("/scripts.js", SPIFFS, "/www/scripts.js");

    // Debug
    server.on("/state", []() {
        server.send(200, "text/plain", "");
    });

    // 404
    server.onNotFound(handleWebRequests404);

    // Start server
    server.begin();
    Serial.println("HTTP server started");
}

bool loadFromSpiffs(String path)
{
    String dataType = "text/plain";

    if (path.endsWith("/"))
        path += "index.html";

    if (path.endsWith(".src"))
        path = path.substring(0, path.lastIndexOf("."));
    else if (path.endsWith(".html"))
        dataType = "text/html";
    else if (path.endsWith(".htm"))
        dataType = "text/html";
    else if (path.endsWith(".css"))
        dataType = "text/css";
    else if (path.endsWith(".js"))
        dataType = "application/javascript";
    else if (path.endsWith(".png"))
        dataType = "image/png";
    else if (path.endsWith(".gif"))
        dataType = "image/gif";
    else if (path.endsWith(".jpg"))
        dataType = "image/jpeg";
    else if (path.endsWith(".ico"))
        dataType = "image/x-icon";
    else if (path.endsWith(".xml"))
        dataType = "text/xml";
    else if (path.endsWith(".pdf"))
        dataType = "application/pdf";
    else if (path.endsWith(".zip"))
        dataType = "application/zip";

    File dataFile = SPIFFS.open(path.c_str(), "r");

    if (server.hasArg("download"))
    {
        dataType = "application/octet-stream";
    }

    if (server.streamFile(dataFile, dataType) != dataFile.size())
    {
    }

    dataFile.close();

    return true;
}

void setupOTA()
{
    // Port defaults to 8266
    ArduinoOTA.setPort(OTA_PORT);

    // Hostname defaults to esp8266-[ChipID]
    ArduinoOTA.setHostname(OTA_HOSTNAME);

    // No authentication by default
    ArduinoOTA.setPassword((const char *)OTA_PASSWORD);

    ArduinoOTA.onStart([]() {
        Serial.println("Start");
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR)
            Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR)
            Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR)
            Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR)
            Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR)
            Serial.println("End Failed");
    });

    ArduinoOTA.begin();

    Serial.println("OTA Ready.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void setup()
{
    Serial.begin(115200);
    delay(10);

    // WiFi
    wifiSetup();

    // OTA
    setupOTA();

    // Webserver
    SPIFFS.begin();
    setupWebserver();
}

void loop()
{
    // OTA
    ArduinoOTA.handle();

    // Webserver
    server.handleClient();
}
