#pragma once

#include "Interval/Interval.h"
#include "ButtonConfiguration.h"
#include <LiquidCrystal.h>

struct TestStripConfiguration
{
    int stripCount;
    double time;
    Interval interval;
};

class TestStripMenu
{

public:
    TestStripMenu(LiquidCrystal &lcd, ButtonConfiguration &buttonConfiguration);
    void run();
    bool wasMenuExited();
    TestStripConfiguration getTestStripConfiguration();

private:
    LiquidCrystal &lcd;
    ButtonConfiguration &buttonConfiguration;

    TestStripConfiguration testStripConfiguration;
    bool menuExited = false;

    enum TestStripMenuStates
    {
        STRIP_COUNT,
        TIME,
        INTERVAL_STEP,
        DONE
    };

    static constexpr double BASE_TIME = 8.0;
};
