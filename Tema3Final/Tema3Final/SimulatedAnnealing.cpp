#include "SimulatedAnnealing.h"

double simpleInitialize(Graf* fun)
{
	return 10;
}

double simpleModify(double Tn, double t, double T0)
{
	return 0.999 * Tn;
}

double logModify(double Tn, double t, double T0)
{
	return T0 / log(t + 1);
}

/*asta e cea mai buna functie din experimentel emele*/
double naturalModify(double Tn, double t, double T0)
{
	double alfa = 0.0005;
	double e = exp(-alfa * t);
	return e * T0;
}

/*Asemanator ca la GA, am pus asa cu parametrii optionali ca sa ne fie usor de customizat*/
void SA(Graf* f,
	double(*initializeTemperature)(Graf* fun),
	double(*modifyTemperature)(double Tn, double t, double T0),
	int repetitions)
{
	/*Implementare de simulated annealing*/
}