#pragma once
#include "Graf.h"
#include "RandomFunctions.h"
#include <iostream>

double simpleInitialize(Graf* fun);

double simpleModify(double Tn, double t, double T0);

double logModify(double Tn, double t, double T0);

double naturalModify(double Tn, double t, double T0);

void inverse(std::vector<int> &vecin,  int i, int j);

void insert(std::vector<int> &vecin, int i, int j);

void swap_orase(std::vector<int> &vecin, int i, int j);
/*Asemanator ca la GA, am pus asa cu parametrii optionali ca sa ne fie usor de customizat*/
float SA(Graf* fun,
	double(*initializeTemperature)(Graf* fun) = simpleInitialize,
	double(*modifyTemperature)(double Tn, double t, double T0) = simpleModify,
	int repetitions = 100);
