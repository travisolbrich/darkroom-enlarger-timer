#pragma once

struct Interval
{
  int interval;
  const char *label;
  const char *fullLabel;
};

const Interval intervals[] = {
    {1, "1/12", "twelfth"},
    {2, "1/6", "sixth"},
    {4, "1/3", "third"},
    {12, "1", "whole"},
};

double getTime(int step);
int getStep(double time);
int getIntervalIndex(Interval interval);