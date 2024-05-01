#pragma once

#include <liquidCrystal.h>
#include "Interval/Interval.h"

class TestStrip
{
public:
	int stripCount = 5;
	double time = 8.0;
	Interval interval = intervals[2];

	TestStrip();

	TestStrip(int strip_count, double time, const Interval& interval)
		: stripCount(strip_count),
		  time(time),
		  interval(interval)
	{
	}

	void printTestStripInfo(LiquidCrystal& lcd) const;
};
