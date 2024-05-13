#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Interval/Interval.h>

#include "ButtonConfiguration.h"
#include "InteractionResult.h"

template <typename T>
class IncrementorInteraction
{
public:
    IncrementorInteraction(LiquidCrystal& lcd, ButtonConfiguration buttonConfiguration): lcd(lcd),
        buttonConfiguration(buttonConfiguration)
    {
    };

    InteractionResult handleInteraction(T& value)
    {
        lcd.setCursor(0, 0);
        lcd.print(message);

        while (true)
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
                Serial.println("Down button pressed. (" + String(buttonConfiguration.downButton));
                value = decrement(value);
                delay(200);
            }
            else if (isButtonPressed(buttonConfiguration.leftButton))
            {
                Serial.println("Left button pressed.");
                delay(200);
                return InteractionResult::Back;
            }
            else if (isButtonPressed(buttonConfiguration.exitButton))
            {
                Serial.println("Exit button pressed.");
                delay(200);
                return InteractionResult::MainMenu;
            }
            else if (isButtonPressed(buttonConfiguration.rightButton))
            {
                Serial.println("Right button pressed.");
                delay(200);
                return InteractionResult::Continue;
            }
            else if (isButtonPressed(buttonConfiguration.startStopButton))
            {
                Serial.println("Start/Stop button pressed.");
                delay(200);
                return InteractionResult::Done;
            }
        }
    }

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
        // Iterate over buttonConfiguration and check if any button is pressed


        return digitalRead(buttonConfiguration.upButton) == HIGH &&
            digitalRead(buttonConfiguration.downButton) == HIGH &&
            digitalRead(buttonConfiguration.leftButton) == HIGH &&
            digitalRead(buttonConfiguration.rightButton) == HIGH &&
            digitalRead(buttonConfiguration.exitButton) == HIGH &&
            digitalRead(buttonConfiguration.startStopButton) == HIGH;
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
