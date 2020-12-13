#pragma once
#include "Graf.h"
#include <vector>
#include <utility>
#include <cmath>
/*
* Graf Euclidian adica alea cu weight type EUC_2D
* si la fiecare nod tinem minte coordonatele si calculam Costul Muchiei cu formula magica
* de distanta
*/
class GrafEuclidian : public Graf
{
	std::vector <std::pair<double, double>> coordonateNoduri;
	int nrNoduri = 0;

public:

	GrafEuclidian(int size);

	void PuneCoordonateLaNod(int nod, std::pair<double, double> coords);

	double CostulMuchiei(int i, int j) override;

	int Marimea() override;
};

