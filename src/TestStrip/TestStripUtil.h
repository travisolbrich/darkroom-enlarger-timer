#pragma once

#include <liquidCrystal.h>
#include "Interval/Interval.h"
#include "TestStrip/TestStripMenu.h"

class TestStripUtil
{
public:
    static void printTestStripInfo(LiquidCrystal &lcd, TestStripConfiguration &config);
};