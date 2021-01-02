#pragma once
#include "Graf.h"
#include "RandomFunctions.h"
#include <iostream>

double simpleInitialize(Graf* fun);

double simpleModify(double Tn, double t, double T0);

double logModify(double Tn, double t, double T0);

double naturalModify(double Tn, double t, double T0);


/*Asemanator ca la GA, am pus asa cu parametrii optionali ca sa ne fie usor de customizat*/
float SA(Graf* fun,
	double(*initializeTemperature)(Graf* fun) = simpleInitialize,
	double(*modifyTemperature)(double Tn, double t, double T0) = simpleModify,
	int repetitions = 100);
