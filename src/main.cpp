#include <LiquidCrystal.h>
#include <math.h>
#include <limits.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "IncrementorInteraction/IncrementorInteraction.h"
#include "Interval.h"

// based on https://www.tmax100.com/photo/pdf/fstoptiming.pdf

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int UP_BUTTON = 7;
const int DOWN_BUTTON = 6;
const int ENTER_BUTTON = 5;
const int BACK_BUTTON = 4;

double baseExposure = 8;

void testStrip();


void setup() {
  Serial.begin(9600);

  lcd.begin(20, 4);

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);
  
  for ( int strip = 0; strip < 13; strip++) {
    // step by thirds
    int step = strip*12/3;

    double time = baseExposure * pow(2, (step/12.0));  

    time = round(time * 10.0)/10.0;

    Serial.print(strip);
    Serial.print(": +");
    Serial.print(step);
    Serial.print("/12 ");
    Serial.println(time);
  }


  testStrip();
}

void loop() {
  
}

double getTime(int step) {

  double time = baseExposure * pow(2, (step/12.0));  

  return time;
}

void printTestStripInfoLine(int strips) {
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("#");
  lcd.print(strips);
}

void printTestStripInfoLine(int strips, double time) {
  printTestStripInfoLine(strips);
  lcd.print(" ");
  lcd.print(String(time, 1));
  lcd.print("s ");
}

void printTestStripInfoLine(int strips, double time, Interval interval) {
  printTestStripInfoLine(strips, time);
  lcd.print("+");
  lcd.print(interval.label);
}


enum TestStripMenuStates {
  STRIP_COUNT,
  TIME,
  INTERVAL_STEP, 
  DONE
};

void testStrip() {
  int strips = 8;
  int timeIdx = 0;
  int intervalIdx = 0;
  double baseTime = 0;

  StripCountIncrementorInteraction stripCountIncrementorInteraction(lcd, UP_BUTTON, DOWN_BUTTON, ENTER_BUTTON, BACK_BUTTON, strips);
  TimeIncrementorInteraction timeIncrementorInteraction(lcd, UP_BUTTON, DOWN_BUTTON, ENTER_BUTTON, BACK_BUTTON, timeIdx);
  IntervalIncrementorInteraction intervalIncrementorInteraction(lcd, UP_BUTTON, DOWN_BUTTON, ENTER_BUTTON, BACK_BUTTON, intervalIdx);



  TestStripMenuStates state = STRIP_COUNT;

 
  Interval interval = intervals[0];

  while (state != DONE) {
    switch (state) {
      case STRIP_COUNT:
        strips = stripCountIncrementorInteraction.handleInteraction();
        
        if (strips == stripCountIncrementorInteraction.BACK_CODE) {
          return;
        }

        state = TIME;
        break;

      case TIME:
        printTestStripInfoLine(strips);
        timeIdx = timeIncrementorInteraction.handleInteraction();

        if (timeIdx == timeIncrementorInteraction.BACK_CODE) {
          state = STRIP_COUNT;
          break;
        }

        baseTime = getTime(timeIdx);
        
        state = INTERVAL_STEP;
        break;

      case INTERVAL_STEP:
        printTestStripInfoLine(strips, baseTime);
        intervalIdx = intervalIncrementorInteraction.handleInteraction();
        
        if (intervalIdx == intervalIncrementorInteraction.BACK_CODE) {
          state = TIME;
          break;
        }
        
        interval = intervals[intervalIdx];
        state = DONE;
        break;
    }

    lcd.clear();
  }

  printTestStripInfoLine(strips, baseTime, interval);
}