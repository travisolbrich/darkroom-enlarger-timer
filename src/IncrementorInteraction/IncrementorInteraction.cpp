#include "IncrementorInteraction.h"
#include <LiquidCrystal.h>
#include "ButtonConfiguration.h"
#include <Arduino.h>

IncrementorInteraction::IncrementorInteraction(LiquidCrystal &lcd, const ButtonConfiguration &buttonConfiguration,
    IncrementFunction increment, DecrementFunction decrement, FormatFunction formatString, const char *message): lcd(lcd),
    buttonConfiguration(buttonConfiguration),
    increment(increment),
    decrement(decrement),
    formatString(formatString),
    message(message)
{
}

InteractionResult IncrementorInteraction::handleInteraction(TestStrip &testStrip)
{
    lcd.setCursor(0, 0);
    lcd.print(message);

    while (true)
    {
        lcd.setCursor(0, 2);
        lcd.print(formatString(testStrip));
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

bool IncrementorInteraction::isButtonPressed(int pin)
{
    return digitalRead(pin) == LOW;
}

bool IncrementorInteraction::noButtonsPressed() const
{
    // Iterate over buttonConfiguration and check if any button is pressed
    return digitalRead(buttonConfiguration.upButton) == HIGH &&
        digitalRead(buttonConfiguration.downButton) == HIGH &&
        digitalRead(buttonConfiguration.leftButton) == HIGH &&
        digitalRead(buttonConfiguration.rightButton) == HIGH &&
        digitalRead(buttonConfiguration.exitButton) == HIGH &&
        digitalRead(buttonConfiguration.startStopButton) == HIGH;
}
