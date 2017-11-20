#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// wifi
ESP8266WiFiMulti wifiMulti;
WiFiClientSecure client;

// stepper
const int stepsPerDose = 100;
Stepper myStepper(stepsPerDose, D1, D2, D3, D4);
int enA = D5;
int enB = D6;
int motorPower = 900;

// ultrasonic
long t;
int trigger = D8;
int echo = D7;
float distance;
float percentageFood;
float max_food = 23.50;

// telegram
#define BOTtoken "CHANGEME_TELEGRAM_TOKEN"
UniversalTelegramBot bot(BOTtoken, client);
int Bot_mtbs = 1000;
long Bot_lasttime;
bool Start = false;


void setup() {
  // Serial setup
  Serial.begin(115200);

  // Wifi connection setup
  wifiMulti.addAP("CHANGEME_SSID1", "CHANGEME_SSID1_PASS");
  wifiMulti.addAP("CHANGEME_SSID2", "CHANGEME_SSID2_PASS");
  while (wifiMulti.run() != WL_CONNECTED) {         // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(1000);
    Serial.print('.');
  }
  Serial.print(WiFi.localIP());

  // pins setup
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  // stepper speed
  myStepper.setSpeed(50);
}

// calc remaining food in %
void calcRemainingFood() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  t = (pulseIn(echo, HIGH) / 2);
  if (t == 0.00) {
    Serial.println("Failed to read from SR02");
    delay(1000);
    return;
  }
  distance = float(t * 0.0343);
  Serial.println(distance);
  Serial.println(t);
  percentageFood = (100 - ((100 / max_food) * distance));
  if (percentageFood < 0.00) {
    percentageFood = 0.00;
  }
  Serial.print("Remaining food:\t");
  Serial.print(percentageFood);
  Serial.println(" %");
  delay(500);
}

// feeds cats
void feedCats() {
  analogWrite(enA, motorPower);
  analogWrite(enB, motorPower);
  myStepper.step(stepsPerDose);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  delay(2000);
}

// telegram message handler
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/food") {
      if (percentageFood == 0.00) {
        bot.sendMessage(chat_id, "There's no food! (Distance: " + String(distance) + " cm)", "");
      }
      else {
        feedCats();
        bot.sendMessage(chat_id, "Cats have been feeded! Remaining food: " + String(percentageFood) + " % (" + String(distance) + " cm)", "");
      }
    }
    if (text == "/check") {
      calcRemainingFood();
      char buffer[5];
      bot.sendMessage(chat_id, "Remaining food: " + String(percentageFood) + " % (Distance: " + String(distance) + " cm)", "");
    }

    if (text == "/help") {
      String welcome = "Welcome to the most awesome ESP8266 catFeeder, " + from_name + "!\n";
      welcome += "/food : Delivers one dose of food.\n";
      welcome += "/check : Returs how much food remains.\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
  }
}

void loop() {
  calcRemainingFood();
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
  delay(1000);
}
