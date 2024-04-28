#include "IncrementorInteraction.h"
#include <LiquidCrystal.h>
#include "Interval.h"
#include "ButtonConfiguration.h"

IncrementorInteraction::IncrementorInteraction(LiquidCrystal& lcd, ButtonConfiguration buttonConfiguration, int initialValue)
    : lcd(lcd), buttonConfiguration(buttonConfiguration), selection(initialValue)
{
}

String IncrementorInteraction::formatString(int value)
{
    return String(value);
}

int IncrementorInteraction::handleInteraction()
{
    lcd.setCursor(0, 0);
    lcd.print(message);

    bool exit = false;

    while (!exit)
    {
        lcd.setCursor(0, 2);
        lcd.print(formatString(selection));
        lcd.print(suffix);
        lcd.print("        ");

        while (noButtonsPressed())
        {
            delay(10);
        }

        selection = handleIncrementButtonPress(buttonConfiguration.upButton, 1, selection);
        selection = handleIncrementButtonPress(buttonConfiguration.downButton, -1, selection);

        selection = max(minVal, min(maxVal, selection));

        exit = checkExitCondition();
        if (checkBackCondition())
        {
            Serial.println("Back button pressed");
            return BACK_CODE;
        }
    }

    return selection;
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
    if (digitalRead(buttonConfiguration.leftButton) == LOW)
    {
        delay(200);
        return true;
    }

    return false;
}

bool IncrementorInteraction::noButtonsPressed()
{
    return digitalRead(buttonConfiguration.upButton) == HIGH && 
    digitalRead(buttonConfiguration.downButton) == HIGH && 
    digitalRead(buttonConfiguration.leftButton) == HIGH && 
    digitalRead(buttonConfiguration.rightButton) == HIGH;
}

bool IncrementorInteraction::checkExitCondition()
{
    if (digitalRead(buttonConfiguration.rightButton) == LOW){
        delay(200);
        return true;
    }
     
    return false;
}

/// StripCountIncrementorInteraction
StripCountIncrementorInteraction::StripCountIncrementorInteraction(LiquidCrystal& lcd, ButtonConfiguration buttonConfiguration, int initialValue) : IncrementorInteraction(lcd, buttonConfiguration, initialValue)
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
TimeIncrementorInteraction::TimeIncrementorInteraction(LiquidCrystal& lcd, ButtonConfiguration buttonConfiguration, int initialValue) : IncrementorInteraction(lcd, buttonConfiguration, initialValue)
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
IntervalIncrementorInteraction::IntervalIncrementorInteraction(LiquidCrystal& lcd, ButtonConfiguration buttonConfiguration, int initalValue) : IncrementorInteraction(lcd, buttonConfiguration, initalValue)
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

