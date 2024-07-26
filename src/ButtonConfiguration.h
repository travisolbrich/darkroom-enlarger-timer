#pragma once

#include <Arduino.h>

class ButtonConfiguration
{
public:
    ButtonConfiguration(int upButton, int downButton, int rightButton, int leftButton, int startStopButton,
                        int exitButton)
        : upButton(upButton),
          downButton(downButton),
          rightButton(rightButton),
          leftButton(leftButton),
          startStopButton(startStopButton),
          exitButton(exitButton)
    {
    }

    enum class Button
    {
        Up,
        Down,
        Right,
        Left,
        StartStop,
        Exit,
    };

    Button waitForButtonPress() const
    {
        while (true)
        {
            if (isButtonPressed(upButton))
            {
                return Button::Up;
            }
            if (isButtonPressed(downButton))
            {
                return Button::Down;
            }
            if (isButtonPressed(rightButton))
            {
                return Button::Right;
            }
            if (isButtonPressed(leftButton))
            {
                return Button::Left;
            }
            if (isButtonPressed(startStopButton))
            {
                return Button::StartStop;
            }
            if (isButtonPressed(exitButton))
            {
                return Button::Exit;
            }

            delay(10);
        }
    }

    void waitForRelease() const{
        // debounce delay?
        delay(100);

        while (isButtonPressed(upButton) || isButtonPressed(downButton) || isButtonPressed(rightButton) || isButtonPressed(leftButton) || isButtonPressed(startStopButton) || isButtonPressed(exitButton))
        {
            delay(10);
        }
    }


private:
    int upButton;
    int downButton;
    int rightButton;
    int leftButton;
    int startStopButton;
    int exitButton;

    static bool isButtonPressed(int buttonPin)
    {
        return digitalRead(buttonPin) == LOW;
    }
};
