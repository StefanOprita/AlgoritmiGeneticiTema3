#include "GrafMatriceAdiacenta.h"


GrafMatriceAdiacenta::GrafMatriceAdiacenta(int size)
	:nrNoduri(size)
{

}

void GrafMatriceAdiacenta::PuneInMatrice(int i, int j, double cost)
{
	matriceAdianceta[i][j] = cost;
}
double GrafMatriceAdiacenta::CostulMuchiei(int i, int j)
{
	return matriceAdianceta[i][j];
}
int GrafMatriceAdiacenta::Marimea()
{
	return nrNoduri;
}
