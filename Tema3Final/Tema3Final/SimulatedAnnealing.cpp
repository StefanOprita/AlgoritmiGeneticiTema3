#include "SimulatedAnnealing.h"
#include "Individ.h"

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

void inverse(std::vector<int> & vecin, int i, int j)
{
	std::vector<int> aux;
	aux = vecin;
	std::swap(aux[i], aux[j]);
	int x = i;
	int y = j;
	int ii = 0;
	while(ii!=(j-i)/2)
	{
		x++;
		y--;
		std::swap(aux[x], aux[y]);
		ii++;
	}
	vecin = aux;
}

void insert(std::vector<int> &vecin, int i, int j)
{
	std::vector<int> aux;
	aux = vecin;
	aux[i] = vecin[j];
	for (int ii = i+1; ii < j+1; ii++)
		aux[ii] = vecin[ii - 1];
	vecin = aux;
}

void swap_orase(std::vector<int> &vecin, int i, int j)
{
	std::swap(vecin[i], vecin[j]);
}


float SA(Graf* fun,
	double(*initializeTemperature)(Graf* fun),
	double(*modifyTemperature)(double Tn, double t, double T0),
	int repetitions)
{
	/*Implementare de simulated annealing*/
	float cost_muchie=0, best_cost=INFINITY, cost_vecin=0;
	float cost_candidat_min;
	Individ i(fun->Marimea());
	Individ i_vecin(fun->Marimea());
	i_vecin = i;
	
	auto v =i.Convert();
	for (int i = 0; i < v.size() - 1; i++)
	{
		//std::cout << i << " " << i + 1 << " " << fun->CostulMuchiei(v[i], v[i + 1]) << "\n";
		cost_muchie += fun->CostulMuchiei(v[i], v[i + 1]);
	}
	cost_muchie += fun->CostulMuchiei(v[v.size() - 1], v[0]);

	auto v_vecin = i_vecin.Convert();
	cost_candidat_min = cost_muchie;
	best_cost = cost_candidat_min;
	std::cout << best_cost << "\n";

	double T = 100;
	int t = 0;
	do
	{
		int k = 0;
		do
		{
			k++;
			float r = randomFloat(0, 1,IntervalEnd::Closed,IntervalEnd::Opened);

			int poz_i, poz_j;
			poz_i = rand() % (v.size() - 1); 
			poz_j = rand() % (v.size() - 1);
			
			//std::cout << "Pozitiile "<<poz_i << " " << poz_j << "\n";
			if (poz_i != poz_j)
			{
				if (poz_i > poz_j)
					std::swap(poz_i, poz_j);
				std::vector<int> candidat1;
				std::vector<int> candidat2;
				std::vector<int> candidat3;
				float cost_candidat1 = 0, cost_candidat2 = 0, cost_candidat3 = 0;

				candidat1 = v_vecin;
				candidat2 = v_vecin;
				candidat3 = v_vecin;

				inverse(candidat1, poz_i, poz_j);
				insert(candidat2, poz_i, poz_j);
				swap_orase(candidat3, poz_i, poz_j);

				for (int i = 0; i < v_vecin.size() - 1; i++)
				{
					cost_candidat1 += fun->CostulMuchiei(candidat1[i], candidat1[i + 1]);
					cost_candidat2 += fun->CostulMuchiei(candidat2[i], candidat2[i + 1]);
					cost_candidat3 += fun->CostulMuchiei(candidat3[i], candidat3[i + 1]);
				}
				cost_candidat1 += fun->CostulMuchiei(candidat1[candidat1.size() - 1], candidat1[0]);
				cost_candidat2 += fun->CostulMuchiei(candidat2[candidat2.size() - 1], candidat2[0]);
				cost_candidat3 += fun->CostulMuchiei(candidat3[candidat3.size() - 1], candidat3[0]);

				cost_candidat_min = std::min(cost_candidat1, cost_candidat2);
				cost_candidat_min = std::min(cost_candidat_min, cost_candidat3);
				if (cost_candidat1 == cost_candidat_min)
					v_vecin = candidat1;
				else if (cost_candidat2 == cost_candidat_min)
					v_vecin = candidat2;
				else
					v_vecin = candidat3;
				//std::cout << "Costuri vecini candidati " << cost_candidat1 << " " << cost_candidat2 << " " << cost_candidat3 << "\n";

			}
			else
			{
				v_vecin = v;
				cost_candidat_min = cost_muchie;
			}


			i_vecin.ConvertFromNormalPermutation(v_vecin);
	
			/*
			std::cout << "VECTORUL I_VECIN " << " \n";
			for (int i = 0; i < i_vecin.GetSize(); i++)
				std::cout << i_vecin[i] << " ";
			std::cout << "\n";
			std::cout << "VECTORUL V_VECIN " << " \n";
			for (int i = 0; i < v_vecin.size(); i++)
				std::cout << v_vecin[i] << " ";
			std::cout << "\n";*/

			best_cost = std::min(best_cost, cost_candidat_min);

			if (cost_candidat_min < cost_muchie)
			{
				cost_muchie = cost_candidat_min;
				i = i_vecin;
			}
			else if (r < exp(-abs(cost_muchie - cost_candidat_min) / T))
			{
				cost_muchie = cost_candidat_min;
				i = i_vecin;
			}
			std::cout << cost_candidat_min << " " << cost_muchie << " " << best_cost << " \n";
		} while (k != repetitions);
		//std::cout << "Temperatura = "<<T << "\n";
		T = modifyTemperature(T, t, 100);
		t++;

	} while (T > 10e-8);
	return best_cost;
	
}