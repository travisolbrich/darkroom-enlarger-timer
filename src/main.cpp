#include <LiquidCrystal.h>
#include <math.h>
#include <limits.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "IncrementorInteraction/IncrementorInteraction.h"
#include "Interval.h"
#include "ButtonConfiguration.h"
#include "TestStrip/TestStripMenu.h"

// based on https://www.tmax100.com/photo/pdf/fstoptiming.pdf

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int UP_BUTTON = 7;
const int DOWN_BUTTON = 6;
const int ENTER_BUTTON = 5;
const int BACK_BUTTON = 4;

ButtonConfiguration buttonConfiguration = {UP_BUTTON, DOWN_BUTTON, ENTER_BUTTON, BACK_BUTTON};

TestStripMenu testStripMenu(lcd, buttonConfiguration);

void setup()
{
  Serial.begin(9600);

  lcd.begin(20, 4);

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);

  auto config = testStripMenu.run();

  // todo: remove debug serial print later
  Serial.println("");
  Serial.print("Strips: ");
  Serial.println(config.stripCount);
  Serial.print("Time: ");
  Serial.println(config.time);
  Serial.print("Interval: ");
  Serial.println(config.interval.label);

  for (int strip = 0; strip < config.stripCount; strip++)
  {
    Serial.print("\tStrip ");
    Serial.println(strip);
    Serial.print("\tTime ");
    Serial.println(String(getTime(config.time, strip * config.interval.interval), 1));
    Serial.println();
  }
}

void loop()
{
}
