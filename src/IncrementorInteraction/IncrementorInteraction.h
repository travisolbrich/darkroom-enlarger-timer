#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <TestStrip/TestStrip.h>

#include "ButtonConfiguration.h"
#include "InteractionResult.h"

class IncrementorInteraction
{
public:
    IncrementorInteraction(LiquidCrystal& lcd, ButtonConfiguration buttonConfiguration): lcd(lcd),
        buttonConfiguration(buttonConfiguration)
    {
    };

    InteractionResult handleInteraction(TestStrip& testStrip)
    {
        lcd.setCursor(0, 0);
        lcd.print(message);

        while (true)
        {
            lcd.setCursor(0, 2);
            lcd.print(formatString(testStrip));
            lcd.print(suffix);
            lcd.print("        ");

            while (noButtonsPressed())
            {
                delay(10);
            }

            if (isButtonPressed(buttonConfiguration.upButton))
            {
                increment(testStrip);
                delay(200);
            }
            else if (isButtonPressed(buttonConfiguration.downButton))
            {
                Serial.println("Down button pressed. (" + String(buttonConfiguration.downButton));
                decrement(testStrip);
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

    virtual String formatString(TestStrip& testStrip) = 0;
    virtual void increment(TestStrip& testStrip) = 0;
    virtual void decrement(TestStrip& testStrip) = 0;

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

class StripCountIncrementorInteraction : public IncrementorInteraction
{
public:
    StripCountIncrementorInteraction(LiquidCrystal& lcd, const ButtonConfiguration& buttonConfiguration);

protected:
    String formatString(TestStrip& testStrip) override;
    void increment(TestStrip& testStrip) override;
    void decrement(TestStrip& testStrip) override;
};

class TimeIncrementorInteraction : public IncrementorInteraction
{
public:
    TimeIncrementorInteraction(LiquidCrystal& lcd, const ButtonConfiguration& buttonConfiguration);

protected:
    String formatString(TestStrip& testStrip) override;
    void increment(TestStrip& testStrip) override;
    void decrement(TestStrip& testStrip) override;
};

class IntervalIncrementorInteraction : public IncrementorInteraction
{
public:
    IntervalIncrementorInteraction(LiquidCrystal& lcd, const ButtonConfiguration& buttonConfiguration);

protected:
    String formatString(TestStrip& testStrip) override;
    void increment(TestStrip& testStrip) override;
    void decrement(TestStrip& testStrip) override;
};
