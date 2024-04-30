#include <LiquidCrystal.h>
#include <math.h>
#include <limits.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <arduino-timer.h>

#include "IncrementorInteraction/IncrementorInteraction.h"
#include "Interval/Interval.h"
#include "ButtonConfiguration.h"
#include "TestStrip/TestStripMenu.h"
#include "TestStrip/TestStripUtil.h"

// based on https://www.tmax100.com/photo/pdf/fstoptiming.pdf

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int UP_BUTTON = 7;
const int DOWN_BUTTON = 6;
const int ENTER_BUTTON = 5;
const int BACK_BUTTON = 4;
const int START_STOP_BUTTON = A0;

const int BUZZER_PIN = 3;
const int RELAY_PIN = 2;

const char CLEAR_ROW[] = "                    ";

ButtonConfiguration buttonConfiguration = {UP_BUTTON, DOWN_BUTTON, ENTER_BUTTON, BACK_BUTTON, START_STOP_BUTTON};

TestStripMenu testStripMenu(lcd, buttonConfiguration);

void exposeTestStrips(TestStripConfiguration testStripConfig);
void expose(double time);

void setup()
{
  Serial.begin(9600);

  lcd.begin(20, 4);

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);
  pinMode(START_STOP_BUTTON, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  testStripMenu.run();

  if(testStripMenu.wasMenuExited())
  {
    lcd.clear();
    lcd.print("Menu exited");
    lcd.setCursor(0, 2);
    lcd.print("MainMenu placeholder");
    return;
  }

  TestStripConfiguration config = testStripMenu.getTestStripConfiguration();
  

  // todo: remove debug serial print later
  /** Serial.println("");
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
   } */

  lcd.clear();

  exposeTestStrips(config);
}

void loop()
{
}

void exposeTestStrips(TestStripConfiguration testStripConfig)
{
  TestStripUtil::printTestStripInfo(lcd, testStripConfig);
  Serial.println("Exposing test strips");



  // First, expose the entire sheet of paper for the base time
  expose(testStripConfig.time);

  // Now, install the first sheet cover. That's the first strip.

  // Then, expose each subsequent strip for that strip's time - the previous strip's time
  for (int strip = 1; strip < testStripConfig.stripCount; strip++)
  {
    double thisTime = getTime(testStripConfig.time, strip * testStripConfig.interval.interval);
    double prevTime = getTime(testStripConfig.time, (strip - 1) * testStripConfig.interval.interval);

    Serial.print("Strip ");
    Serial.print(strip + 1);
    Serial.print(" time: ");
    Serial.print(thisTime);
    Serial.print(" Previous strip time: ");
    Serial.println(prevTime);

    double exposeTime = thisTime - prevTime;
    expose(exposeTime);
  }
}

void expose(double time)
{
  lcd.setCursor(0, 0);
  lcd.print(CLEAR_ROW);
  lcd.setCursor(0, 1);
  lcd.print(CLEAR_ROW);

  lcd.setCursor(0, 0);
  lcd.print("Exposing for ");
  lcd.print(time);
  lcd.print("s");

  lcd.setCursor(0, 1);
  lcd.print("Press start");

  // Wait for start button press
  while (digitalRead(START_STOP_BUTTON) == HIGH)
  {
    delay(50);
  }

  unsigned long startTime = millis();
  unsigned long currentTime = millis();
  unsigned long elapsedTime = 0;

  unsigned long lastLCDUpdate = 0;

  digitalWrite(RELAY_PIN, HIGH);

  while (elapsedTime < time * 1000)
  {
    currentTime = millis();
    elapsedTime = currentTime - startTime;

    if (currentTime - lastLCDUpdate >= 10)
    {
      lcd.setCursor(0, 1);
      lcd.print("Remaining: ");
      lcd.print(max(0.0, (time * 1000 - elapsedTime) / 1000));
      lcd.print("s");
      lastLCDUpdate = currentTime;
    }

    // within 20ms of each whole second, beep
    if (abs((elapsedTime % 1000)) < 20)
    {
      digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
      digitalWrite(BUZZER_PIN, LOW);
    }

    delay(1);
  }

  digitalWrite(RELAY_PIN, LOW);
  lcd.setCursor(0, 1);
  lcd.print("Exposure complete");
  delay(1500);
}