#include "GrafEuclidian.h"


GrafEuclidian::GrafEuclidian(int size)
{
	coordonateNoduri = std::vector<std::pair<double, double>>(size + 1);
	nrNoduri = size;
}

void GrafEuclidian::PuneCoordonateLaNod(int nod, std::pair<double, double> coords)
{
	coordonateNoduri[nod] = coords;
}

double GrafEuclidian::CostulMuchiei(int i, int j)
{
	std::pair<double, double> ICoords = coordonateNoduri[i];
	std::pair<double, double> JCoords = coordonateNoduri[j];

	double distance = sqrt((JCoords.first - ICoords.first) * (JCoords.first - ICoords.first)
		+ (JCoords.second - ICoords.second) * (JCoords.second - ICoords.second));
	return distance;
}

int GrafEuclidian::Marimea()
{
	return nrNoduri;
}