#pragma once
#include "Graf.h"
class GrafMatriceAdiacenta : public Graf
{
	double matriceAdianceta[1000][1000];
	int nrNoduri;
public:

	GrafMatriceAdiacenta(int size);

	void PuneInMatrice(int i, int j, double cost);
	double CostulMuchiei(int i, int j) override;
	int Marimea() override;
};

