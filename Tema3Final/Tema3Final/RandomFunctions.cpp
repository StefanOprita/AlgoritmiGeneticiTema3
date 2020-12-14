#include "RandomFunctions.h"

double randomFloat(const double lower, const double upper, IntervalEnd left, IntervalEnd right)
{
	if (lower > upper)
	{
		throw "Error: the second argument of randomFloat must be bigger then than the first argument!";
	}
	std::random_device generator;
	std::uniform_real_distribution<double> distribution(lower, upper);
	double  result;
	do {
		result = distribution(generator);
	} while ((result == lower && left == IntervalEnd::Opened) || (result == upper && right == IntervalEnd::Opened));
	return result;
}

int randomInt(int lower, int upper)
{
	if (lower > upper)
	{
		throw "Error: the second argument of randomInt must be bigger then than the first argument!";
	}

	std::random_device generator;
	std::uniform_int_distribution<int> distribution(lower, upper);
	return distribution(generator);
}