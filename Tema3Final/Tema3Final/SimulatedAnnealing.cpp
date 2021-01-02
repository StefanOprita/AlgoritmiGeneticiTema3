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
	double alfa = 0.0008;
	double e = exp(-alfa * t);
	return e * T0;
}

std::vector<int> VecinInverse(std::vector<int>& v)
{
	std::vector<int> vecinu = v;
	int  i, j;
	i = randomInt(0, v.size() - 1);
	do {
		j = randomInt(0, v.size() - 1);
	} while (i == j);

	if (i > j) std::swap(i, j);

	for(int dist = 0 ; dist < (j - i + 1)/2; ++dist)
	{
		std::swap(vecinu[i + dist], vecinu[j - dist]);
	}
	return vecinu;
}

std::vector<int> VecinInsert(std::vector<int>& v)
{
	std::vector<int> vecinu = v;
	int  i, j;
	i = randomInt(0, v.size() - 1);
	do {
		j = randomInt(0, v.size() - 1);
	} while (i == j);

	if (i > j) std::swap(i, j);

	vecinu[i] = v[j];
	for (int index = i + 1; index <= j; ++index)
	{
		vecinu[index] = v[index - 1];
	}
	return vecinu;
}

std::vector<int> VecinSwap(std::vector<int>& v)
{
	std::vector<int> vecinu = v;
	int  i, j;
	i = randomInt(0, v.size() - 1);
	do {
		j = randomInt(0, v.size() - 1);
	} while (i == j);

	if (i > j) std::swap(i, j);

	std::swap(vecinu[i], vecinu[j]);
	return vecinu;
}

double calculareValoare(std::vector<int> &permutare, Graf *fun)
{
	/*for (int i = 0; i < v_vecin.size(); i++)
		std::cout << v_vecin[i] << " ";
	std::cout << "\n";*/
	double cost = 0;
	for (int i = 0; i < permutare.size() - 1; i++)
		cost += fun->CostulMuchiei(permutare[i], permutare[i + 1]);

	cost += fun->CostulMuchiei(permutare[permutare.size() - 1], permutare[0]);
	return cost;
}


/*Asemanator ca la GA, am pus asa cu parametrii optionali ca sa ne fie usor de customizat*/
float SA(Graf* fun,
	double(*initializeTemperature)(Graf* fun),
	double(*modifyTemperature)(double Tn, double t, double T0),
	int repetitions)
{
	/*Implementare de simulated annealing*/
	double cost_muchie = 0;
	double best_cost = INFINITY;
	double cost_vecin = 0;
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
	cost_vecin = cost_muchie;
	best_cost = cost_vecin;
	std::cout << best_cost << "\n";

	double T = 100;
	int t = 0;
	do
	{
		int k = 0;
		do
		{
			k++;
			//float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			//r = randomFloat(0, 1,IntervalEnd::Closed,IntervalEnd::Opened);
			//cost_vecin = 0;

			//int poz_mutatie;
			//poz_mutatie = randomInt(0, i_vecin.GetSize() - 1); 

			//
			////std::cout << "Pozitie mutatie " << poz_mutatie <<" cu valoarea "<<i_vecin[poz_mutatie]<< " ,iar dupa ";

			///*i_vecin[poz_mutatie] = (i_vecin[poz_mutatie] + 1) % (i_vecin.GetSize() + 2 - poz_mutatie);
			//if (i_vecin[poz_mutatie] == 0)
			//	i_vecin[poz_mutatie] = 1;*/

			////i_vecin[poz_mutatie] = randomInt(1, i_vecin.GetSize() + 1 - poz_mutatie);
			////std::cout << i_vecin[poz_mutatie] << "\n";
			//v_vecin= i_vecin.Convert();
			///*for (int i = 0; i < v_vecin.size(); i++)
			//	std::cout << v_vecin[i] << " ";
			//std::cout << "\n";*/
			//for (int i = 0; i < v_vecin.size() - 1; i++)
			//	cost_vecin += fun->CostulMuchiei(v_vecin[i], v_vecin[i + 1]);

			//cost_vecin += fun->CostulMuchiei(v_vecin[v_vecin.size() - 1], v_vecin[0]);

			i_vecin = i;


			float r = randomFloat(0, 1, IntervalEnd::Closed, IntervalEnd::Opened);

			auto perm = i_vecin.Convert();

			auto perm1 = VecinInverse(perm);
			auto perm2 = VecinSwap(perm);
			auto perm3 = VecinInsert(perm);

			double value1 = calculareValoare(perm1, fun);
			double value2 = calculareValoare(perm2, fun);
			double value3 = calculareValoare(perm3, fun);

			double minimValue = std::min(value1, std::min(value2, value3));
			
			if (minimValue == value1) i_vecin.ConvertFromNormalPermutation(perm1);
			if (minimValue == value2) i_vecin.ConvertFromNormalPermutation(perm2);
			if (minimValue == value3) i_vecin.ConvertFromNormalPermutation(perm3);

			cost_vecin = minimValue;

			best_cost = std::min(best_cost, cost_vecin);

			if (cost_vecin < cost_muchie)
			{
				cost_muchie = cost_vecin;

				//individul devine vecin
				i = i_vecin;

			}
			else if (r < exp(-abs(cost_muchie - cost_vecin) / T))
			{
				cost_muchie = cost_vecin;
				i = i_vecin;
			}
		} while (k != repetitions);
		std::cout << "Cel mai bun cost pana acum : " << best_cost << "\n";
		std::cout << "Temperatura = "<< T << "\n";
		T = modifyTemperature(T, t, 100);
		t++;

	} while (T > 10e-8);
	return best_cost;
}