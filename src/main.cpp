#include <LiquidCrystal.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "ButtonConfiguration.h"
#include "TestStrip/TestStripMenu.h"
#include "TestStrip/TestStrip.h"
#include "TestStrip/TestStripExposer.h"

// based on https://www.tmax100.com/photo/pdf/fstoptiming.pdf

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int UP_BUTTON = 7;
const int DOWN_BUTTON = 6;
const int RIGHT_BUTTON = 5;
const int LEFT_BUTTON = 4;
const int START_STOP_BUTTON = PIN_A0;
const int EXIT_BUTTON = PIN_A1;

const int BUZZER_PIN = 3;
const int RELAY_PIN = 2;

const char CLEAR_ROW[] = "                    ";

ButtonConfiguration buttonConfiguration = {UP_BUTTON, DOWN_BUTTON, RIGHT_BUTTON, LEFT_BUTTON, START_STOP_BUTTON, EXIT_BUTTON};


void setup()
{
    Serial.begin(9600);

    lcd.begin(20, 4);

    pinMode(UP_BUTTON, INPUT_PULLUP);
    pinMode(DOWN_BUTTON, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
    pinMode(LEFT_BUTTON, INPUT_PULLUP);
    pinMode(START_STOP_BUTTON, INPUT_PULLUP);
    pinMode(EXIT_BUTTON, INPUT_PULLUP);

    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);

    TestStripMenu testStripMenu = TestStripMenu(lcd, buttonConfiguration);
    TestStripExposer testStripExposer = TestStripExposer(lcd, buttonConfiguration);

    TestStrip testStrip = TestStrip();

    if (!testStripMenu.run(testStrip))
    {
        lcd.clear();
        lcd.print("Menu exited");
        lcd.setCursor(0, 2);
        lcd.print("MainMenu placeholder");
        return;
    }

    lcd.clear();

    testStripExposer.exposeTestStrips(testStrip);
}

void loop()
{

}
