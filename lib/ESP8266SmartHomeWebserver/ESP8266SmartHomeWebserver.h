#ifndef ESP8266SmartHomeWebserver_h
#define ESP8266SmartHomeWebserver_h

#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#ifndef HTTP_PORT
#define HTTP_PORT 80
#endif

class ESP8266SmartHomeWebserver
{
public:
  void setup();
  void handle();
  void on(const String &uri, std::function<void(void)> handler);
  void on(const String &uri, HTTPMethod method, std::function<void(void)> fn);
  void on(const String &uri, HTTPMethod method, std::function<void(void)> fn, std::function<void(void)> ufn);
  // void send(int code, const char *content_type = NULL, const String &content = String(""));
  void send(int code, char *content_type, const String &content);
  void send(int code, const String &content_type, const String &content);
};

#endif