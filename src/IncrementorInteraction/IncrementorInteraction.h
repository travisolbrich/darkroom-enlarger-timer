#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Interval/Interval.h>

#include "ButtonConfiguration.h"

template <typename T>
class IncrementorInteraction
{
public:
    IncrementorInteraction(LiquidCrystal& lcd, ButtonConfiguration buttonConfiguration): lcd(lcd),
        buttonConfiguration(buttonConfiguration)
    {
    };

    bool handleInteraction(T& value)
    {
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

            if (isButtonPressed(buttonConfiguration.upButton))
            {
                value = increment(value);
                delay(200);
            }
            else if (isButtonPressed(buttonConfiguration.downButton))
            {
                value = decrement(value);
                delay(200);
            }
            else if (isButtonPressed(buttonConfiguration.leftButton))
            {
                return false;
            }
            else if (isButtonPressed(buttonConfiguration.rightButton))
            {
                exit = true;
                delay(200);
            }
        }

        return true;
    };

protected:
    String message;
    String suffix;
    LiquidCrystal& lcd;

    ButtonConfiguration buttonConfiguration;

    virtual String formatString(T value) = 0;
    virtual T increment(T value) = 0;
    virtual T decrement(T value) = 0;

private:
    bool isButtonPressed(int pin)
    {
        return digitalRead(pin) == LOW;
    };

    bool noButtonsPressed()
    {
        return digitalRead(buttonConfiguration.upButton) == HIGH &&
            digitalRead(buttonConfiguration.downButton) == HIGH &&
            digitalRead(buttonConfiguration.leftButton) == HIGH &&
            digitalRead(buttonConfiguration.rightButton) == HIGH;
    };
};

class StripCountIncrementorInteraction : public IncrementorInteraction<int>
{
public:
    StripCountIncrementorInteraction(LiquidCrystal& lcd, const ButtonConfiguration& buttonConfiguration);

protected:
    String formatString(int value) override;
    int increment(int value) override;
    int decrement(int value) override;
};

class TimeIncrementorInteraction : public IncrementorInteraction<double>
{
public:
    TimeIncrementorInteraction(LiquidCrystal& lcd, const ButtonConfiguration& buttonConfiguration);

protected:
    String formatString(double value) override;
    double increment(double value) override;
    double decrement(double value) override;
};

class IntervalIncrementorInteraction : public IncrementorInteraction<Interval>
{
public:
    IntervalIncrementorInteraction(LiquidCrystal& lcd, const ButtonConfiguration& buttonConfiguration);

protected:
    String formatString(Interval value) override;
    Interval increment(Interval value) override;
    Interval decrement(Interval value) override;
};
