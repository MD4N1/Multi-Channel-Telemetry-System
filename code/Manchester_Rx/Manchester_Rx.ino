// LCD:     DB7       -> Arduino Digital 11
//          DB6       -> Arduino Digital 10
//          DB5       -> Arduino Digital 9
//          DB4       -> Arduino Digital 8
//          E         -> Arduino Digital 7
//          RS        -> Arduino Digital 6
#include <Arduino.h>
#include <Manchester.h>
#include <LiquidCrystal.h>
#include <DS1307.h>

uint8_t moo = 1;
uint8_t data;
uint8_t id;

// Init the LCD
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

#define RX_PIN 4
#define LED_PIN 13


void setup()
{
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, moo);
  man.setupReceive(RX_PIN, MAN_1200);
  man.beginReceive();
  lcd.begin(16,2);
  lcd.setCursor(0,0);lcd.print("TELEMETRY SYSTEM");
  lcd.setCursor(0,1);lcd.print("BY MD4N1 2014");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("SENDER-ID ");
  lcd.setCursor(10,0);lcd.print("DATA");
}

void loop() {
  if (man.receiveComplete()) //received something
  {
    uint16_t m = man.getMessage();
    man.beginReceive(); //start listening for next message right after you retrieve the message
    if (man.decodeMessage(m, id, data)) //extract id and data from message, check if checksum is correct
    {
      moo = ++moo % 2;
      digitalWrite(LED_PIN, moo);
    }
    lcd.setCursor(0,1);lcd.print("   ");
    lcd.setCursor(10,1);lcd.print("   ");
    lcd.setCursor(0,1);lcd.print(id);
    lcd.setCursor(10,1);lcd.print(data);
  }
}
