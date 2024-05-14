#pragma once

struct Interval
{
	double divisor;
	const char* label;
	const char* fullLabel;
};

const Interval intervals[] = {
	{1, "1/12", "twelfths"},
	{2, "1/6", "sixths"},
	{4, "1/3", "thirds"},
	{12, "1", "whole"},
};

// ceil(12^(n/3))

double getTime(int numTwelthStops);
int getStep(double time);
int getIntervalIndex(Interval interval);
