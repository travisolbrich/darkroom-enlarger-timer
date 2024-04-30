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
    TestStripConfiguration run();

private:
    LiquidCrystal &lcd;
    ButtonConfiguration &buttonConfiguration;

    enum TestStripMenuStates
    {
        STRIP_COUNT,
        TIME,
        INTERVAL_STEP,
        DONE
    };

    static constexpr double BASE_TIME = 8.0;
};
