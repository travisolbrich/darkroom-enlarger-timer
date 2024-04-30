#pragma once

#include "Interval/Interval.h"
#include "ButtonConfiguration.h"
#include <LiquidCrystal.h>

#include "TestStrip.h"

class TestStripMenu
{

public:
    TestStripMenu(LiquidCrystal &lcd, ButtonConfiguration &button_configuration)
        : lcd(lcd),
          buttonConfiguration(button_configuration)
    {
    }

    bool run(TestStrip &outTestStrip);

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
