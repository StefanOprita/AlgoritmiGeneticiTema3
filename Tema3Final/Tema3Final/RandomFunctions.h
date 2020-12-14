#pragma once
#include <random>
enum class IntervalEnd {
	Closed, Opened
};

double randomFloat(const double lower, const double upper, IntervalEnd left = IntervalEnd::Closed, IntervalEnd right = IntervalEnd::Closed);

int randomInt(int lower, int upper);