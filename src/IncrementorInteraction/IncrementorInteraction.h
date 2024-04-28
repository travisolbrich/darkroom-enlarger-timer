#include <Arduino.h>
#include <LiquidCrystal.h>



class IncrementorInteraction {


public:
    IncrementorInteraction(LiquidCrystal& lcd, int incrementPin, int decrementPin, int rightPin, int backPin);
    int handleInteraction(int initialValue);
    virtual String formatString(int value);
    const int BACK_CODE = -69;

protected:
    String message;
    String suffix;
    int minVal;
    int maxVal;
    LiquidCrystal& lcd;

    int incrementPin;
    int decrementPin;
    int rightPin;
    int backPin;

private:
    int handleIncrementButtonPress(int button, int increment, int value);
    bool noButtonsPressed();
    bool checkExitCondition();
    bool checkBackCondition();
};

class StripCountIncrementorInteraction : public IncrementorInteraction {
public:
    StripCountIncrementorInteraction(LiquidCrystal& lcd, int incrementPin, int decrementPin, int rightPin, int backPin);
    String formatString(int value) override;
};

class TimeIncrementorInteraction : public IncrementorInteraction {
public:
    TimeIncrementorInteraction(LiquidCrystal& lcd, int incrementPin, int decrementPin, int rightPin, int backPin);
    String formatString(int value) override;

private:
    double getTime(int step);
};

class IntervalIncrementorInteraction : public IncrementorInteraction {
public:
    IntervalIncrementorInteraction(LiquidCrystal& lcd, int incrementPin, int decrementPin, int rightPin, int backPin);
    String formatString(int value) override;
};