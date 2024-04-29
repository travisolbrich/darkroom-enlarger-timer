#include "TestStripUtil.h"


void TestStripUtil::printTestStripInfo(LiquidCrystal &lcd, TestStripConfiguration &config)
{
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("#");
    lcd.print(config.stripCount);

    lcd.print(" ");
    lcd.print(String(config.time, 1));
    lcd.print("s ");

    lcd.print("+");
    lcd.print(config.interval.label);
}