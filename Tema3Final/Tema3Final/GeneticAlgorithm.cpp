#include "GeneticAlgorithm.h"
#include "RandomFunctions.h"
#include "CitesteGraf.h"
std::vector<Individ> Generatie;
void GA(Graf* g, int nbGenerations, int popSize,
	double mutateChance, double crossingOverP,
	FitnessFunction((*fitness)),
	EvaluateFunction((*eval)),
	SelectFunction((*select)),
	MutateFunction((*mutate)),
	CrossOverPop((*crossPop))
)
{
	Generatie = std::vector<Individ>(popSize);
	for (int i = 0; i < popSize; ++i)
	{
		Individ indi(g->Marimea());
		Generatie.push_back(indi);
	}

}

FitnessFunction(FitnessNormal)
{
	/*De implementat magia fitnessului*/
}

EvaluateFunction(EvaluareNormala)
{
	/*De implemenatat magia evaluarii populatiei*/
}

SelectFunction(RoataNorocului)
{
	/*De implementat roata norocului*/
}

MutateFunction(MutatieNormala)
{
	int poz_mutatie;
	poz_mutatie = randomInt(0, X.GetSize());
	std::cout << "Pozitia la care se face mutatia " << poz_mutatie << " si valoarea de pe poz respectiva " << X[poz_mutatie]<<"\n";
	for (int i = 0; i <= X.GetSize(); i++)
		std::cout << X[i] << " ";
	std::cout << "\n"<<" DUPA MUTATIE"<<"\n";
	X[poz_mutatie] = (X[poz_mutatie] + 1) % (X.GetSize()+2-poz_mutatie);
	if (X[poz_mutatie] == 0)
		X[poz_mutatie] = 1;
	for (int i = 0; i <= X.GetSize(); i++)
		std::cout << X[i] << " ";
	std::cout << "\n";

}

CrossingOver(CrossOverNormal)
{
	//punctul de taiere
	int pct_taiere;
	pct_taiere = randomInt(0, P1.GetSize());
	Individ C1;
	Individ C2;

	//dupa punctul de taiere ne uitam in dreapta in caz de valoarea respectiva exista si in stanga
	//se pune in copil urmatoarea cea mai mare valoare (care nu se gaseste in stanga)


	/*De implementat un crossOver*/
}

CrossOverPop(CrossOverPopNormal)
{
	/*De implementat un crossOver pe populatie*/
}