#pragma once

#include "ButtonConfiguration.h"

#include "TestStrip/TestStrip.h"

class TestStripExposer
{
public:
	TestStripExposer(LiquidCrystal& lcd, ButtonConfiguration& buttonConfiguration)
		: lcd(lcd), buttonConfig(buttonConfiguration)
	{
	}

	bool exposeTestStrips(TestStrip& testStrip);

private:
	LiquidCrystal& lcd;
	ButtonConfiguration& buttonConfig;

	void printExposureInformation(int stripNumber, int stripCount, double stripTotalTime, double exposureTime);
	void waitStart();
	void beepOnSecond(unsigned long elapsedTime);
	void expose(double time);
};
