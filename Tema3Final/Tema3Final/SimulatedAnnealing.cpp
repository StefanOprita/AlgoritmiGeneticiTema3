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

/*Asemanator ca la GA, am pus asa cu parametrii optionali ca sa ne fie usor de customizat*/
float SA(Graf* fun,
	double(*initializeTemperature)(Graf* fun),
	double(*modifyTemperature)(double Tn, double t, double T0),
	int repetitions)
{
	/*Implementare de simulated annealing*/
	float cost_muchie=0, best_cost=INFINITY, cost_vecin=0;
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

	double T = 1000;
	int t = 0;
	do
	{
		int k = 0;
		do
		{
			k++;
			float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r = randomFloat(0, 1,IntervalEnd::Closed,IntervalEnd::Opened);
			cost_vecin = 0;

			int poz_mutatie;
			poz_mutatie = rand() % (v.size() - 1); 

			
			//std::cout << "Pozitie mutatie " << poz_mutatie <<" cu valoarea "<<i_vecin[poz_mutatie]<< " ,iar dupa ";

			/*for (int i = 0; i < i_vecin.GetSize(); i++)
			{
				i_vecin[i] = (i_vecin[i] + 1) % (i_vecin.GetSize() + 2 - i);
				if (i_vecin[i] == 0)
					i_vecin[i] = 1;
			}*/

			/*i_vecin[poz_mutatie] = (i_vecin[poz_mutatie] + 1) % (i_vecin.GetSize() + 2 - poz_mutatie);
			if (i_vecin[poz_mutatie] == 0)
				i_vecin[poz_mutatie] = 1;*/

			i_vecin[poz_mutatie] = randomInt(1, i_vecin.GetSize() + 1 - poz_mutatie);
			//std::cout << i_vecin[poz_mutatie] << "\n";
			v_vecin= i_vecin.Convert();
			/*for (int i = 0; i < v_vecin.size(); i++)
				std::cout << v_vecin[i] << " ";
			std::cout << "\n";*/
			for (int i = 0; i < v_vecin.size() - 1; i++)
				cost_vecin += fun->CostulMuchiei(v_vecin[i], v_vecin[i + 1]);

			cost_vecin += fun->CostulMuchiei(v_vecin[v_vecin.size() - 1], v_vecin[0]);
			std::cout << cost_vecin << " " << cost_muchie << " "<<best_cost<<" \n";

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
		std::cout << "Temperatura = "<<T << "\n";
		T = modifyTemperature(T, t, 100);
		t++;

	} while (T > 10e-8);
	return best_cost;
	
}