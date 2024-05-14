#include <Arduino.h>


#include "TestStrip/TestStripExposer.h"
#include "TestStrip/TestStrip.h"


// todo don't redefine these
const char CLEAR_ROW[] = "                    ";
const int BUZZER_PIN = 3;
const int RELAY_PIN = 2;


bool TestStripExposer::exposeTestStrips(TestStrip &testStripConfig)
{
    double baseTime = testStripConfig.time;

    testStripConfig.printTestStripFooter(lcd);

    // First, expose the entire sheet of paper for the base time (first strip).
    printExposureInformation(1, testStripConfig.stripCount, testStripConfig.time, testStripConfig.time);
    waitStart();

    expose(testStripConfig.time);

    // Now, install the first sheet cover. We just exposed our first strip.

    // Then, expose each subsequent strip for that strip's time - the previous strip's time
    for (int strip = 1; strip < testStripConfig.stripCount; strip++)
    {
        double thisTime = baseTime * getTime(strip * testStripConfig.interval.divisor);
        double prevTime = baseTime * getTime((strip - 1) * testStripConfig.interval.divisor);

        double exposeTime = thisTime - prevTime;

        printExposureInformation(strip + 1, testStripConfig.stripCount, thisTime, exposeTime);
        waitStart();

        expose(exposeTime);
    }

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Test strip exposures");
    lcd.setCursor(0, 1);
    lcd.print("complete");

    return true;
}

void TestStripExposer::printExposureInformation(int stripNumber, int stripCount, double stripTotalTime,
                                                double exposureTime)
{
    lcd.setCursor(0, 0);
    lcd.print(CLEAR_ROW);
    lcd.setCursor(0, 1);
    lcd.print(CLEAR_ROW);
    lcd.setCursor(0, 2);
    lcd.print(CLEAR_ROW);

    // ex: Strip 1/5 (8s)
    lcd.setCursor(0, 0);
    lcd.print("Strip ");
    lcd.print(stripNumber);
    lcd.print("/");
    lcd.print(stripCount);
    lcd.print(" (");
    lcd.print(String(stripTotalTime, 1));
    lcd.print("s)");

    // ex: Exp. Time: 2s
    lcd.setCursor(0, 1);
    lcd.print("Exp. Time: ");
    lcd.print(String(exposureTime, 1));
    lcd.print("s");

    lcd.setCursor(0, 2);
    lcd.print("Press start");
}

void TestStripExposer::waitStart()
{
    while (digitalRead(buttonConfig.startStopButton) == HIGH)
    {
        delay(50);
    }
}

void TestStripExposer::beepOnSecond(unsigned long elapsedTime)
{
    // within 20ms of each whole second, beep
    if (abs((elapsedTime % 1000)) < 20)
    {
        digitalWrite(BUZZER_PIN, HIGH);
    }
    else
    {
        digitalWrite(BUZZER_PIN, LOW);
    }
}

// todo extract to an Exposer class?
void TestStripExposer::expose(double time)
{
    lcd.setCursor(0, 2);
    lcd.print(CLEAR_ROW);

    unsigned long startTime = millis();
    unsigned long currentTime = millis();
    unsigned long elapsedTime = 0;

    unsigned long lastLCDUpdate = 0;

    // todo extract to a RelayController class?
    digitalWrite(RELAY_PIN, HIGH);

    // todo REMOVE
    // time = min(2, time);

    while (elapsedTime < time * 1000)
    {
        currentTime = millis();
        elapsedTime = currentTime - startTime;

        if (currentTime - lastLCDUpdate >= 10)
        {
            lcd.setCursor(0, 2);
            lcd.print("Remaining: ");
            lcd.print(max(0.0, (time * 1000 - elapsedTime) / 1000));
            lcd.print("s");
            lastLCDUpdate = currentTime;
        }

        beepOnSecond(elapsedTime);

        delay(1);
    }

    digitalWrite(RELAY_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    lcd.setCursor(0, 2);
    lcd.print("Exposure complete");
    delay(1500);
}
