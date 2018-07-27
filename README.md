# MQTT catFeeder
catFeeder is an Arduino (ESP8266) MQTT controlled cat feeder which I use to feed my cats when I'm away or in the bed at 6.30 AM on a Sunday morning.
	The project is forked upon https://github.com/jorgerance/catFeeder which usees a telegram bot.

i also added a pushbutton for manual operation and  Home-assistant integration through a script and 2 mqtt sensor.
![](https://i.imgur.com/I6HMVH6.png)
![](https://i.imgur.com/JwnOMNt.jpg)

## About the ESP8266:
Wikipedia:

> The **ESP8266** is a low-cost Wi-Fi chip with full TCP/IP stack and MCU (microcontroller unit) capability produced by Shanghai-based Chinese manufacturer, Espressif Systems.

[Click here to access the full article](https://en.wikipedia.org/wiki/ESP8266)

## Main features:
- Controlled via **MQTT**.
- Wifi connection.
- Possibility to check how much food can be still delivered with an **HC-SR04 ultrasonic ranging sensor**.
- ~~Multi access point (can manage more than one SSID / password).~~ Removed because i dont need it, could be easily reintegrated?

## Materials Needed:
- 1 x NodeMCU V3 dev board (esp8266): ~2.65 USD. / ~5€ 
- 1 x NodeMCU Base Breadboard (optional): ~1.88 USD. / 3€
- 1 x L298N Dual H bridge driver: ~3.33 USD. / 7€
- 1 x HC-SR04 ultrasonic ranging sensor: ~1.50 USD. / 2€
- 1 x 12V 2A Power Supply*: ~6.58 USD. / i had one around :)
- 1 x Cereal dispenser: ~10.00 USD. / ~ 12€ for a dual
- 2 x MDF pieces, i used 45x15 and 15x15: ~6.00 USD. / 2-4 € worth of MDF
- 2 x Little metal L bracket
- 1 x Plastic enclosure for PSU: ~4.00 USD. / 1€ for a standard elecrtical box
- 1 x 4 pieces lot 5x8mm couplings: ~5.50 USD. / 8.99 €
- 1 x NEMA 17 Motor 1.7A: ~9.00 USD.  // 12€
- 1 x Misc. cables: ~2.00 USD. // had some laying around
- 1 x Can of acrylic spray paint 5€


**Total cost: up to what you have available :)

## Schematics:

![](https://i.imgur.com/3LSziQ2.png)

There's actually no need of perfboard / protoboard. However, in order to mount the HC-SR04 on the top of the cereal dispenser you may use a hot glue gun.

![](https://i.imgur.com/0e6oNYw.jpg)

## Parameters to be updated on the .ino file:

    Just search for REPLACEME inside the ino before uploading.
	
Necessary libraries:

	#include <Stepper.h>
	#include <ESP8266WiFi.h>
	#include <ArduinoOTA.h>
	#include <PubSubClient.h>
	#include <NTPClient.h> (https://github.com/arduino-libraries/NTPClient/releases)


## How to control the cat feeder via mqtt/Home Assistant:
just publish
    feed


to the MQTT command channel, which if you dont change anything is
    home/catfeeder/feed

you can use the script i provided under the HASS folder.

