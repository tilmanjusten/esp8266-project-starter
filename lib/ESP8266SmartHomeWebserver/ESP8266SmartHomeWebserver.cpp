#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>
#include <ESP8266SmartHomeWebserver.h>

ESP8266WebServer espWebserver(HTTP_PORT);

void ESP8266SmartHomeWebserver::setup()
{
  if (MDNS.begin("ESP-01"))
  {
    Serial.println("MDNS responder started");
  }

  SPIFFS.begin();

  // Overview
  espWebserver.serveStatic("/", SPIFFS, "/www/index.html");
  espWebserver.serveStatic("/index.html", SPIFFS, "/www/index.html");
  espWebserver.serveStatic("/styles.css", SPIFFS, "/www/styles.css");
  espWebserver.serveStatic("/scripts.js", SPIFFS, "/www/scripts.js");

  // Debug
  espWebserver.on("/debug", []() {
    espWebserver.send(200, "text/plain", "ok");
  });

  // 404
  espWebserver.onNotFound([]() {
    String message = "File Not Detected\n\n";
    message += "URI: ";
    message += espWebserver.uri();
    message += "\nMethod: ";
    message += (espWebserver.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += espWebserver.args();
    message += "\n";

    for (uint8_t i = 0; i < espWebserver.args(); i++)
    {
      message += " NAME:" + espWebserver.argName(i) + "\n VALUE:" + espWebserver.arg(i) + "\n";
    }

    espWebserver.sendHeader("Access-Control-Allow-Origin", "*");
    espWebserver.send(404, "text/plain", message);

    Serial.println(message);
  });

  // Start espWebserver
  espWebserver.begin();

  Serial.println("HTTP espWebserver started");
}

void ESP8266SmartHomeWebserver::handle()
{
  espWebserver.handleClient();
}

void ESP8266SmartHomeWebserver::on(const String &uri, std::function<void(void)> handler)
{
  espWebserver.on(uri, handler);
}

void ESP8266SmartHomeWebserver::on(const String &uri, HTTPMethod method, std::function<void(void)> fn)
{
  espWebserver.on(uri, method, fn);
}

void ESP8266SmartHomeWebserver::on(const String &uri, HTTPMethod method, std::function<void(void)> fn, std::function<void(void)> ufn)
{
  espWebserver.on(uri, method, fn, ufn);
}

// void ESP8266SmartHomeWebserver::send(int code, const char *content_type = NULL, const String &content = String(""))
// {
//   espWebserver.send(code, content_type, content);
// }

void ESP8266SmartHomeWebserver::send(int code, char *content_type, const String &content)
{
  espWebserver.send(code, content_type, content);
}

void ESP8266SmartHomeWebserver::send(int code, const String &content_type, const String &content)
{
  espWebserver.send(code, content_type, content);
}
