#pragma once

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ButtonConfiguration.h"

class IncrementorInteraction
{

// todo: make generic incrementor interaction class with virtual increment/decrement to support strip, time, and interval
public:
    IncrementorInteraction(LiquidCrystal &lcd, ButtonConfiguration buttonConfiguration, int initialValue);
    int handleInteraction();
    virtual String formatString(int value);
    const int BACK_CODE = -69;

protected:
    String message;
    String suffix;
    int minVal;
    int maxVal;
    LiquidCrystal &lcd;

    ButtonConfiguration buttonConfiguration;

private:
    int handleIncrementButtonPress(int button, int increment, int value);
    bool noButtonsPressed();
    bool checkExitCondition();
    bool checkBackCondition();
    int selection;
};

class StripCountIncrementorInteraction : public IncrementorInteraction
{
public:
    StripCountIncrementorInteraction(LiquidCrystal &lcd, ButtonConfiguration buttonConfiguration, int initialValue);
    String formatString(int value) override;
};

class TimeIncrementorInteraction : public IncrementorInteraction
{
public:
    TimeIncrementorInteraction(LiquidCrystal &lcd, ButtonConfiguration buttonConfiguration, int initialValue);
    String formatString(int value) override;
};

class IntervalIncrementorInteraction : public IncrementorInteraction
{
public:
    IntervalIncrementorInteraction(LiquidCrystal &lcd, ButtonConfiguration buttonConfiguration, int initialValue);
    String formatString(int value) override;
};
