#include <LiquidCrystal.h>
#include <math.h>
#include <limits.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

// based on https://www.tmax100.com/photo/pdf/fstoptiming.pdf

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int UP_BUTTON = 7;
const int DOWN_BUTTON = 6;
const int ENTER_BUTTON = 5;

double baseExposure = 8;

struct Interval {
  int interval;
  const char* label;
};

Interval intervals[] = {
  {12, "1"},
  {4, "1/3"},
  {2, "1/6"},
  {1, "1/12"}
};

void testStrip();
int getStripCount(int strips);
double getBaseTime(int stripCount);
Interval getIntervals(int stripCount, double baseTime);

int handleIncrementButtonPress(int pin, int increment, int current) {
  if (digitalRead(pin) == LOW) {
    current += increment;
    delay(200);
  }

  return current;
}

bool checkExitCondition(int pin) {
  if (digitalRead(pin) == LOW) {
      delay(200);
      return true;

  }
  return false;
}

bool noButtonsPressed() {
  return digitalRead(UP_BUTTON) == HIGH && digitalRead(DOWN_BUTTON) == HIGH && digitalRead(ENTER_BUTTON) == HIGH;
}

void setup() {
  Serial.begin(9600);

  lcd.begin(20, 4);

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  
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

void testStrip() {
  // int preset = EEPROM.read(0);
  int preset = 8;

  int strips = getStripCount(preset);

  if (strips != EEPROM.read(0)) {
    EEPROM.write(0, strips);
  }

  double baseTime = getBaseTime(strips);
  Interval interval = getIntervals(strips, baseTime);

  lcd.clear();

  printTestStripInfoLine(strips, baseTime, interval);
}

int getStripCount(int strips) {
  lcd.clear();
  lcd.print("# test strips?");

  bool exit = false;

  while (!exit) {
    lcd.setCursor(0, 2);
    lcd.print(strips);
    lcd.print(" strips        ");

    while (noButtonsPressed()) {
      delay(10);
    }

    strips = handleIncrementButtonPress(UP_BUTTON, 1, strips);
    strips = handleIncrementButtonPress(DOWN_BUTTON, -1, strips);
    exit = checkExitCondition(ENTER_BUTTON);
  }

  return strips;
}

double getBaseTime(int stripCount) {
  lcd.clear();
  lcd.print("Base exposure time?");
  
  printTestStripInfoLine(stripCount);

  bool exit = false;
  int step = 0;
  
  while (!exit) {
    lcd.setCursor(0, 2);
    lcd.print(String(getTime(step), 1));
    lcd.print(" seconds        ");

    while (noButtonsPressed()) {
      delay(10);
    }

    step = handleIncrementButtonPress(UP_BUTTON, 1, step);
    step = handleIncrementButtonPress(DOWN_BUTTON, -1, step);
    exit = checkExitCondition(ENTER_BUTTON);
  }

  return getTime(step);
}

Interval getIntervals(int stripCount, double baseTime){
  int intervalIndex = 1;

  lcd.clear();
  lcd.print("Step size?");
  lcd.setCursor(0, 2);
  lcd.print(intervals[intervalIndex].label);
  lcd.print(" step");

  printTestStripInfoLine(stripCount, baseTime);

  bool exit = false;

  while (!exit) {
    lcd.setCursor(0, 2);
    lcd.print(intervals[intervalIndex].label);
    lcd.print(" steps        ");

    while (noButtonsPressed()) {
      delay(10);
    }

    intervalIndex = handleIncrementButtonPress(UP_BUTTON, 1, intervalIndex);
    intervalIndex = handleIncrementButtonPress(DOWN_BUTTON, -1, intervalIndex);
    
    // Restrict to valid indicies
    intervalIndex = max(0, min(3, intervalIndex));

    exit = checkExitCondition(ENTER_BUTTON);
  }

  return intervals[intervalIndex];
}
