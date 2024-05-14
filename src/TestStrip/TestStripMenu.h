#pragma once

#include <InteractionResult.h>
#include <LiquidCrystal.h>

#include "ButtonConfiguration.h"
#include "TestStrip.h"

class TestStripMenu
{
public:
	TestStripMenu(LiquidCrystal& lcd, ButtonConfiguration& button_configuration)
		: lcd(lcd),
		  buttonConfiguration(button_configuration)
	{
	}

	InteractionResult run(TestStrip& outTestStrip);

private:
	LiquidCrystal& lcd;
	ButtonConfiguration& buttonConfiguration;
};
