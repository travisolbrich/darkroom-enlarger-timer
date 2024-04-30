#include "TestStrip.h"



void TestStrip::printTestStripInfo(LiquidCrystal &lcd) const
{
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("#");
    lcd.print(stripCount);

    lcd.print(" ");
    lcd.print(String(time, 1));
    lcd.print("s ");

    lcd.print("+");
    lcd.print(interval.label);
}