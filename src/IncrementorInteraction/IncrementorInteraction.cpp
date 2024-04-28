#include "IncrementorInteraction.h"
#include <LiquidCrystal.h>
#include "Interval.h"

IncrementorInteraction::IncrementorInteraction(LiquidCrystal& lcd, int incrementPin, int decrementPin, int rightPin, int backPin)
    : lcd(lcd), incrementPin(incrementPin), decrementPin(decrementPin), rightPin(rightPin), backPin(backPin)
{
}

String IncrementorInteraction::formatString(int value)
{
    return String(value);
}

int IncrementorInteraction::handleInteraction(int initialValue)
{
    int value = initialValue;
    lcd.setCursor(0, 0);
    lcd.print(message);

    bool exit = false;

    while (!exit)
    {
        lcd.setCursor(0, 2);
        lcd.print(formatString(value));
        lcd.print(suffix);
        lcd.print("        ");

        while (noButtonsPressed())
        {
            delay(10);
        }

        value = handleIncrementButtonPress(incrementPin, 1, value);
        value = handleIncrementButtonPress(decrementPin, -1, value);

        value = max(minVal, min(maxVal, value));

        exit = checkExitCondition();
        if (checkBackCondition())
        {
            Serial.println("Back button pressed");
            return BACK_CODE;
        }
    }

    return value;
}

int IncrementorInteraction::handleIncrementButtonPress(int button, int increment, int value)
{
    if (digitalRead(button) == LOW)
    {
        value += increment;
        delay(200);
    }

    return value;
}

bool IncrementorInteraction::checkBackCondition()
{
    if (digitalRead(backPin) == LOW)
    {
        delay(200);
        return true;
    }

    return false;
}

bool IncrementorInteraction::noButtonsPressed()
{
    return digitalRead(incrementPin) == HIGH && digitalRead(decrementPin) == HIGH && digitalRead(rightPin) == HIGH && digitalRead(backPin) == HIGH;
}

bool IncrementorInteraction::checkExitCondition()
{
    if (digitalRead(rightPin) == LOW){
        delay(200);
        return true;
    }
     
    return false;
}

/// StripCountIncrementorInteraction
StripCountIncrementorInteraction::StripCountIncrementorInteraction(LiquidCrystal& lcd, int incrementPin, int decrementPin, int rightPin, int backPin) : IncrementorInteraction(lcd, incrementPin, decrementPin, rightPin, backPin)
{
    message = "Strips: ";
    suffix = "";
    minVal = 1;
    maxVal = 10;
}

String StripCountIncrementorInteraction::formatString(int value)
{
    return String(value);
}

/// TimeIncrementorInteraction
TimeIncrementorInteraction::TimeIncrementorInteraction(LiquidCrystal& lcd, int incrementPin, int decrementPin, int rightPin, int backPin) : IncrementorInteraction(lcd, incrementPin, decrementPin, rightPin, backPin)
{
    message = "Time: ";
    suffix = "s";
    minVal = -20;
    maxVal = 60;
}

String TimeIncrementorInteraction::formatString(int value)
{
    return String(getTime(value), 1);
}

double TimeIncrementorInteraction::getTime(int step)
{
    double time = 8 * pow(2, (step / 12.0));

    return time;
}

/// IntervalIncrementorInteraction
IntervalIncrementorInteraction::IntervalIncrementorInteraction(LiquidCrystal& lcd, int incrementPin, int decrementPin, int rightPin, int backPin) : IncrementorInteraction(lcd, incrementPin, decrementPin, rightPin, backPin)
{
    message = "Interval: ";
    suffix = " steps";
    minVal = 0;
    maxVal = 3;
}

String IntervalIncrementorInteraction::formatString(int value)
{
    auto result = String(intervals[value].label);
    result.concat(": ");
    result.concat(intervals[value].fullLabel);

    return result;
}

