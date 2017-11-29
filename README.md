# catFeeder
catFeeder is an Arduino (ESP8266) Telegram controlled cat feeder which I use to feed my cats when I'm away.

![](https://user-images.githubusercontent.com/22028245/33085175-3e69b6a0-cee4-11e7-9d4e-a9e88cb42ec3.jpg)

## About the ESP8266:
Wikipedia:

> The **ESP8266** is a low-cost Wi-Fi chip with full TCP/IP stack and MCU (microcontroller unit) capability produced by Shanghai-based Chinese manufacturer, Espressif Systems.

[Click here to access the full article](https://en.wikipedia.org/wiki/ESP8266)

## Main features:
- Controlled via **Telegram bot**.
- Wifi connection.
- Possibility to check how much food can be still delivered with an **HC-SR04 ultrasonic ranging sensor**.
- Multi access point (can manage more than one SSID / password).

## Bill of materials (with shipping):
- 1 x NodeMCU V3 dev board (esp8266): ~2.65 USD.
- 1 x NodeMCU Base Breadboard (optional): ~1.88 USD.
- 1 x L298N Dual H bridge driver: ~3.33 USD.
- 1 x HC-SR04 ultrasonic ranging sensor: ~1.50 USD.
- 1 x 12V 2A Power Supply*: ~6.58 USD.
- 1 x Cereal dispenser: ~10.00 USD.
- 1 x 80x25x1.8cm piece of wood: ~6.00 USD.
- 1 x Plastic enclosure for PSU: ~4.00 USD.
- 1 x 4 pieces lot 5x8mm couplings: ~5.50 USD.
- 1 x NEMA 17 Motor 1.7A: ~9.00 USD.
- 1 x Misc. cables: ~2.00 USD.

**Total cost: 52,44 USD.**

## Schematics:

![](https://user-images.githubusercontent.com/22028245/33085257-7f37354a-cee4-11e7-9f8f-23e35e81b02c.png)

There's actually no need of perfboard / protoboard. However, in order to mount the HC-SR04 on the top of the cereal dispenser you may use a hot glue gun.

![](https://user-images.githubusercontent.com/22028245/33085429-ebc592ce-cee4-11e7-948f-427cd2cfa7e3.jpg)

## Parameters to be updated on the .ino file:

Define how many steps will the stepper motor rotate in order to deliver one dose:
	
	const int stepsPerDose = 100;
	
Define de max. distance the ultrasonic sensor measures when the cereal dispenser is empty:

	float max_food = 23.50;

Replace "XXXXXXX" with your Telegram Token:

    #define BOTtoken "CHANGEME_TELEGRAM_TOKEN"

Add one of those statements for each SSID you want to be able to connect:

	wifiMulti.addAP("CHANGEME_SSID1", "CHANGEME_SSID1_PASS");
	wifiMulti.addAP("CHANGEME_SSID2", "CHANGEME_SSID2_PASS");
	
Necessary libraries:

	#include <Stepper.h>
	#include <ESP8266WiFi.h>
	#include <ESP8266WiFiMulti.h>
	#include <WiFiClientSecure.h>
	#include <UniversalTelegramBot.h>

## How to control the cat feeder via Telegram bot:
![](https://user-images.githubusercontent.com/22028245/33397924-848a583c-d54d-11e7-86c7-b1a0c73cc42d.jpg)
