#include "IncrementorInteraction.h"

#include <Arduino.h>
#include <LiquidCrystal.h>

#include "ButtonConfiguration.h"

IncrementorInteraction::IncrementorInteraction(LiquidCrystal &lcd, const ButtonConfiguration &buttonConfiguration,
                                               IncrementFunction increment, DecrementFunction decrement,
                                               FormatFunction formatString, const char *message) :
    lcd(lcd), buttonConfiguration(buttonConfiguration), increment(increment), decrement(decrement),
    formatString(formatString), message(message)
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


        buttonConfiguration.waitForRelease();
        ButtonConfiguration::Button button = buttonConfiguration.waitForButtonPress();

        switch (button)
        {
        case ButtonConfiguration::Button::Up:
            increment(testStrip);
            break;

        case ButtonConfiguration::Button::Down:
            decrement(testStrip);
            break;

        case ButtonConfiguration::Button::Left:
            return InteractionResult::Back;

        case ButtonConfiguration::Button::Exit:
            return InteractionResult::MainMenu;

        case ButtonConfiguration::Button::Right:
            return InteractionResult::Continue;

        case ButtonConfiguration::Button::StartStop:
            return InteractionResult::Done;
        }
    }
}
