#include <LiquidCrystal.h>
#include <math.h>
#include <limits.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

// based on https://www.tmax100.com/photo/pdf/fstoptiming.pdf

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int UP_BUTTON = 7;
const int DOWN_BUTTON = 6;
const int ENTER_BUTTON = 5;

double baseExposure = 8;

void testStrip();
int getStripCount();

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

void testStrip() {
  int strips = getStripCount();
  
  lcd.clear();
  lcd.print("Base exposure time?");
  lcd.setCursor(0, 3);
  lcd.print(strips);
  lcd.print(" strips");


  bool exit = false;
  int step = 0;
  
  while (!exit) {
    lcd.setCursor(0, 2);
    lcd.print(String(getTime(step), 1));
    lcd.print(" seconds        ");

    while (digitalRead(UP_BUTTON) == HIGH && digitalRead(DOWN_BUTTON) == HIGH && digitalRead(ENTER_BUTTON) == HIGH) {
      delay(10);
    }

    if (digitalRead(UP_BUTTON) == LOW && step < 100) {
      step+=1;
      delay(200);
    }

    if (digitalRead(DOWN_BUTTON) == LOW && step > 0) {
      step-=1;
      delay(200);
    }

    if (digitalRead(ENTER_BUTTON) == LOW) {
      exit = true;
      delay(200);
    }
  }
}

int getStripCount() {
  lcd.clear();
  lcd.print("# test strips?");

  int strips = 5;
  bool exit = false;

  while (!exit) {
    lcd.setCursor(0, 2);
    lcd.print(strips);
    lcd.print(" strips        ");

    while (digitalRead(UP_BUTTON) == HIGH && digitalRead(DOWN_BUTTON) == HIGH && digitalRead(ENTER_BUTTON) == HIGH) {
      delay(10);
    }

    if (digitalRead(UP_BUTTON) == LOW && strips < 100) {
      strips++;
      delay(200);
    }

    if (digitalRead(DOWN_BUTTON) == LOW && strips > 1) {
      strips--;
      delay(200);
    }

    if (digitalRead(ENTER_BUTTON) == LOW) {
      exit = true;
      delay(200);
    }
  }

  return strips;
}