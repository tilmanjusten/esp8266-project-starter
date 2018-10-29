# ESP8266 project starter

Project starter for ESP8266 with webserver and over the air updates enabled.

## Features

- Webinterface
- Over the air updates
- Website resources on SPIFFS
- Enable logging for development purposes

## Development

Requires [PlatformIO](https://platformio.org).

### ESP8266

1. Create ``src/secret.h`` from ``src/secrects.template.h``
1. Set SSID and password of your WLAN and over the air hostname
1. Update ``OTA_HOSTNAME`` depending on your needs
1. First deploy only: 
    1. Comment out ``upload_port`` and ``upload_port`` in ``platform.io`` 
    1. Plug device to FTDI adapter
1. Flash device via OTA update/FTDI adapter
1. Upload web resources to SPIFFS

### Webinterface

Use resources in ``data/www/`` and change depending on your needs. There is a [Browsersync config](https://browsersync.io) in ``bs-config.js`` you can use for development. Requires gobally installed Browsersync (``$ npm i -g browser-sync``):  
``$ browser-sync start --config bs-config.js``

### Dependencies

Required libraries:

- ArduinoOTA
- SHA-1 Hash
- ESP Async WebServer

## Deployment

See (development section above)[#Development].

## Hardware

### Parts

- ESP8266
- FTDI adapter for first deployment
