#include "GeneticAlgorithm.h"
#include "RandomFunctions.h"
#include "CitesteGraf.h"

double GA(Graf* g, int nbGenerations, int popSize,
	double mutateChance, double crossingOverP,
	FitnessFunction((*fitness)),
	EvaluateFunction((*eval)),
	SelectFunction((*select)),
	MutateFunction((*mutate)),
	CrossOverPop((*crossPop))
)
{
	int nrLaFel = 0;
	std::vector<Individ> populatie(popSize);
	Individ aux(g->Marimea());
	for (int i = 0; i < popSize; ++i)
	{
		aux.GenerareRandom();
		populatie[i] = aux;
	}

	eval(populatie, g, fitness);
	
	double bestFitness = -INFINITY;
	double bestValue = INFINITY;


	for (int gen = 0; gen < nbGenerations; ++gen)
	{
		std::cout << "Generatia #" << gen << "\n";
		

		std::sort(populatie.begin(), populatie.end(), [](Individ& I1,Individ& I2) {
			return I1.GetCost() < I2.GetCost();
		});

		


		std::cout << "Best fitness and cost : " << populatie[0].GetFitness() << " " << pow(populatie[0].GetCost(), 1./1.) << "\n";

		/*if (populatie[0].GetFitness() > bestFitness)
		{
			bestFitness = populatie[0].GetFitness();
			bestValue = populatie[0].GetCost();
		}*/
		nrLaFel++;

		if (populatie[0].GetCost() < bestValue)
		{
			bestFitness = populatie[0].GetFitness();
			bestValue = populatie[0].GetCost();
			nrLaFel = 1;
		}

		/*Eu data trecuta am facut elitismul cu primii 2 oameni cei mai buni... si fu suficient
		* daca consideram ca trebuie mai mult o sa facem noi frumi dupi aici
		*/
		
		Individ Best1 = populatie[0];
		Individ Best2 = populatie[1];

		/*double elitismRate = 0.01;
		int nrPastrati = populatie.size() * elitismRate;
		std::cout << "Pastram atatia : " << nrPastrati << "\n";
		std::vector<Individ> pastrati;

		for (int i = 0; i < nrPastrati; ++i)
		{
			Individ copie = populatie[i];
			pastrati.push_back(copie);
		}*/

		select(populatie, popSize);
		
		double maxMut = mutateChance;
		double modifiedMutChance = std::min(mutateChance * pow(1.01,(nrLaFel)/10), maxMut);
		std::cout << "Sansa de mutatie:" << modifiedMutChance;
		std::vector<Individ> toAdd;
		for (auto& individ : populatie)
		{
			auto copie = individ;
			auto copie2 = copie;
			mutate(individ, modifiedMutChance);
		
			
			//toAdd.push_back(copie);
		}
		for (auto& c : toAdd)
		{
			populatie.push_back(c);
		}

		//break
		//std::cout << "aici";
		/*for (auto& pastrat : pastrati)
		{
			populatie.push_back(pastrat);
		}*/
		
		//magia 
		//std::cout << "aici";

		populatie.push_back(Best1);
		populatie.push_back(Best2);

		eval(populatie, g, fitness);

		//std::cout << "aici";
		std::sort(populatie.begin(), populatie.end(), [](Individ& I1, Individ& I2) {
			return I1.GetFitness() > I2.GetFitness();
		});
		//std::cout << "aici";

		crossPop(populatie, crossingOverP, g);
		//std::cout << "aici";
	
		eval(populatie, g, fitness);


	}

	return bestValue;

}


FitnessFunction(FitnessLaPutere)
{
	auto permutare = X.Convert();
	double costTotal = 0;
	for (int i = 1; i < permutare.size(); ++i)
	{
		costTotal += g->CostulMuchiei(permutare[i - 1], permutare[i]);
	}
	costTotal += g->CostulMuchiei(permutare[permutare.size() - 1], permutare[0]);
	if (costTotal < 39)
	{
		/*std::cout << "AULEO GICA CE AI FACUT\n";
		for (auto& i : permutare)
		{
			std::cout << i << " ";
		}
		std::cout << "\n";*/
	}
	X.SetFitness(pow(1/costTotal, 1.75));
	X.SetCost(costTotal);
}

FitnessFunction(FitnessNormal)
{
	/*De implementat magia fitnessului*/
	//std::cout << "Pentru acest vector minunat: ";
	//X.Print();

	auto permutare = X.Convert();
	//std::cout << "Permutarea sa reala este : ";
	//for (auto& p : permutare)
	//{
	//	std::cout << p << " ";
	//}
	//std::cout << "\n";
	double costTotal = 0;
	for (int i = 1; i < permutare.size(); ++i)
	{
		//std::cout << "Intre nodurile " << permutare[i - 1] << " " << permutare[i] << "=";
		//std::cout << g->CostulMuchiei(permutare[i - 1], permutare[i]) << "\n";
		costTotal += g->CostulMuchiei(permutare[i - 1], permutare[i]);
	}

	costTotal += g->CostulMuchiei(permutare[permutare.size() - 1], permutare[0]);
		 
	X.SetFitness(pow(-costTotal, 1));
	X.SetCost(costTotal);
}

EvaluateFunction(EvaluareFancy)
{
	for (auto& individ : v)
	{
		fit(individ, g);
	}

	double max = -INFINITY;
	double min = INFINITY;

	for (auto& individ : v)
	{
		if (individ.GetCost() > max) max = individ.GetCost();
		if (individ.GetCost() < min) min = individ.GetCost();
	}

	for (auto& individ : v)
	{
		individ.SetFitness((max - individ.GetCost()) / (max - min) + 0.01);
	}


}

EvaluateFunction(EvaluareNormala)
{
	for(auto &individ : v)
	{
		fit(individ, g);
	}
}

CrossingOver(OX)
{
	Individ C1(P1.GetSize() + 1, false);
	Individ C2(P1.GetSize() + 1, false);

	std::vector<int> permP1 = P1.Convert();
	std::vector<int> permP2 = P2.Convert();

	std::vector<int> permC1(P1.GetSize() + 1);
	std::vector<int> permC2(P1.GetSize() + 1);

	for (int i = 0; i < permC1.size(); ++i)
	{
		permC1[i] = -1;
		permC2[i] = -1;
	}

	int taiere1 = randomInt(0, permC1.size() - 1);
	int taiere2;
	do {
		taiere2 = randomInt(0, permC1.size() - 1);
	} while (taiere1 == taiere2);
	if (taiere1 > taiere2) std::swap(taiere1, taiere2);

	taiere1 = 3;
	taiere2 = 6;

	std::set<int> adaugatC1;
	std::set<int> adaugatC2;

	for (int i = taiere1; i <= taiere2; ++i)
	{
		permC1[i] = permP1[i];
		adaugatC1.insert(permP1[i]);
		permC2[i] = permP2[i];
		adaugatC2.insert(permP2[i]);
	}

	int index = (taiere2 + 1) % permP1.size();
	int indexP2 = index;
	while (index != taiere1)
	{
		while (adaugatC1.find(permP2[indexP2]) != adaugatC1.end())
		{
			indexP2 = (indexP2 + 1) % permP1.size();
		}

		permC1[index] = permP2[indexP2];
		adaugatC1.insert(permP2[indexP2]);
		index = (index + 1) % permP1.size();
	}

	index = (taiere2 + 1) % permP2.size();
	int indexP1 = index;
	while (index != taiere1)
	{
		while (adaugatC2.find(permP1[indexP1]) != adaugatC2.end())
		{
			indexP1 = (indexP1 + 1) % permP2.size();
		}

		permC2[index] = permP1[indexP1];
		adaugatC2.insert(permP1[indexP1]);
		index = (index + 1) % permP2.size();
	}

	C1.ConvertFromNormalPermutation(permC1);
	C2.ConvertFromNormalPermutation(permC2);

	offspring.push_back(C1);
	offspring.push_back(C2);


}

CrossingOver(CX)
{
	auto findPos = [](std::vector<int>& v, int f)
	{
		for (int i = 0; i < v.size(); ++i)
			if (v[i] == f) return i;
		return -1;
	};

	Individ C1(P1.GetSize() + 1, false);
	Individ C2(P1.GetSize() + 1, false);

	std::vector<int> permP1 = P1.Convert();
	std::vector<int> permP2 = P2.Convert();

	std::vector<int> permC1(P1.GetSize() + 1);
	std::vector<int> permC2(P1.GetSize() + 1);

}

CrossingOver(AEX)
{
	auto findPos = [](std::vector<int>& v, int f)
	{
		//std::cout << "Am de cautat : " << f << "\n";
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			if (*it == f)
			{
				//std::cout << "uite am gasit valoarea " << f << "\n";
				return it;
			}
		}
		return v.end();
	};
	Individ C1(P1.GetSize() + 1, false);
	Individ C2(P1.GetSize() + 1, false);

	std::vector<int> permP1 = P1.Convert();
	std::vector<int> permP2 = P2.Convert();

	std::vector<int> permC1(P1.GetSize() + 1);
	std::vector<int> permC2(P1.GetSize() + 1);

	std::vector<int> vizitate(permP1.size());

	for (int i = 1; i <= permP1.size(); ++i)
	{
		vizitate[i - 1] = i;
	}
	permC1[0] = permP1[0];
	permC1[1] = permP1[1];
	vizitate.erase(findPos(vizitate, permC1[0]));
	vizitate.erase(findPos(vizitate, permC1[1]));
	for (int index = 1; index < permC1.size() - 1; ++index)
	{
		int candidat = -1;
		if (index % 2 == 1)
		{
			auto it = findPos(permP2, permC1[index]);
			std::advance(it, 1);
			if (it == permP2.end())
			{
				it = permP2.begin();
			}
			candidat = *it;
	
		}
		else
		{
			auto it = findPos(permP1, permC1[index]);
			std::advance(it, 1);
			if (it == permP1.end())
			{
				it = permP1.begin();
			}
			candidat = *it;
		
		}
	
		if (findPos(vizitate, candidat) == vizitate.end())
		{
			
			int rd = randomInt(0, vizitate.size() - 1);
			candidat = vizitate[rd];
		}
		permC1[index + 1] = candidat;
	
		vizitate.erase(findPos(vizitate, candidat));

	}
	
	std::vector<int> vizitate1(permP2.size());
	for (int i = 1; i <= permP2.size(); ++i)
	{
		vizitate1[i - 1] = i;
	}
	permC2[0] = permP2[0];
	permC2[1] = permP2[1];
	vizitate1.erase(findPos(vizitate1, permC2[0]));
	vizitate1.erase(findPos(vizitate1, permC2[1]));
	for (int index = 1; index < permC2.size() - 1; ++index)
	{
		int candidat = -1;
		if (index % 2 == 1)
		{
			auto it = findPos(permP1, permC2[index]);
			std::advance(it, 1);
			if (it == permP1.end())
			{
				it = permP1.begin();
			}
			candidat = *it;
		}
		else
		{
			auto it = findPos(permP2, permC2[index]);
			std::advance(it, 1);
			if (it == permP2.end())
			{
				it = permP2.begin();
			}
			candidat = *it;

		}

		if (findPos(vizitate1, candidat) == vizitate1.end())
		{

			int rd = randomInt(0, vizitate1.size() - 1);
			candidat = vizitate1[rd];
		}
		permC2[index + 1] = candidat;

		vizitate1.erase(findPos(vizitate1, candidat));
	}

	C1.ConvertFromNormalPermutation(permC1);
	C2.ConvertFromNormalPermutation(permC2);
	offspring.push_back(C1);
	offspring.push_back(C2);


}

CrossingOver(PartiallyMappedCrossover)
{
	//std::cout << "mor aici: " << P1.GetSize() << " " << P2.GetSize() << "\n";
	Individ C1(P1.GetSize() + 1, false);
	Individ C2(P2.GetSize() + 1, false);

	std::vector<int> permP1 = P1.Convert();
	std::vector<int> permP2 = P2.Convert();

	std::vector<int> permC1(P1.GetSize() + 1);
	std::vector<int> permC2(P1.GetSize() + 1);

	
	for (int i = 0; i < permC1.size(); ++i)
	{
		permC1[i] = -1;
		permC2[i] = -1;
	}

	int taiere1 = randomInt(0, permC1.size() - 1);
	int taiere2;
	do {
		taiere2 = randomInt(0, permC1.size() - 1);
	} while (taiere1 == taiere2);
	if (taiere1 > taiere2) std::swap(taiere1, taiere2);
	//std::cout << "Punctele de taiere:" << taiere1 << " " << taiere2 << "\n";
	std::map<int, int> map12;
	std::map<int, int> map21;
	std::set<int> adaugateC1;
	std::set<int> adaugateC2;
	for (int i = taiere1; i <= taiere2; ++i)
	{
		permC1[i] = permP2[i];
		adaugateC1.insert(permC1[i]);
		permC2[i] = permP1[i];
		adaugateC2.insert(permC2[i]);
		map12[permP1[i]] = permP2[i];
		map21[permP2[i]] = permP1[i];
	}



	for (int i = 0; i < permC1.size(); ++i)
	{
		if (permC1[i] == -1)
		{
			int old = adaugateC1.size();
			adaugateC1.insert(permP1[i]);
			if (old == adaugateC1.size())
			{
				bool ok = false;
				int problematic = permP1[i];
				while (!ok)
				{
					ok = true;
					problematic = map21[problematic];
					int old = adaugateC1.size();
					adaugateC1.insert(problematic);
					if (old == adaugateC1.size())
						ok = false;
				}
				permC1[i] = problematic;
			}
			else
			{
				permC1[i] = permP1[i];
			}
		}
	}

	for (int i = 0; i < permC2.size(); ++i)
	{
		if (permC2[i] == -1)
		{
			int old = adaugateC2.size();
			adaugateC2.insert(permP2[i]);
			if (old == adaugateC2.size())
			{
				bool ok = false;
				int problematic = permP2[i];
				while (!ok)
				{
					ok = true;
					problematic = map12[problematic];
					int old = adaugateC2.size();
					adaugateC2.insert(problematic);
					if (old == adaugateC2.size())
						ok = false;
				}
				permC2[i] = problematic;
			}
			else
			{
				permC2[i] = permP2[i];
			}
		}
	}

	C1.ConvertFromNormalPermutation(permC1);
	C2.ConvertFromNormalPermutation(permC2);

	offspring.push_back(C1);
	offspring.push_back(C2);
}

SelectFunction(SelectiaTurneu)
{
	int adaugati = 0;
	int k = popSize * 0.5;
	int j = popSize * 0.25;
	std::vector<Individ> nouaPopulatie;
	while (adaugati < popSize)
	{
		std::set<int> chosenForShaolinBattle;
		while (chosenForShaolinBattle.size() < k)
		{
			int r = randomInt(0, populatie.size() - 1);
			chosenForShaolinBattle.insert(r);
		}
		std::vector<Individ> theChosenOnes;
		for (auto& index : chosenForShaolinBattle)
		{
			theChosenOnes.push_back(populatie[index]);
		}
		std::sort(theChosenOnes.begin(), theChosenOnes.end(), [](Individ& I1, Individ& I2) {
			return I1.GetFitness() > I2.GetFitness();
		});

		for (int i = 0; i < j && adaugati < popSize; ++i)
		{
			nouaPopulatie.push_back(theChosenOnes[i]);
			++adaugati;
		}
	}
	populatie = nouaPopulatie;
}

SelectFunction(RoataNoroculuiLimitata)
{
	double fitnessTotal = 0;
	for (auto& individ : populatie)
	{
		fitnessTotal += individ.GetFitness();
	}
	std::vector<double> procentajeAdunate(populatie.size());
	procentajeAdunate[0] = populatie[0].GetFitness() / fitnessTotal;

	for (int i = 1; i < populatie.size(); ++i)
	{
		procentajeAdunate[i] = procentajeAdunate[i - 1] + populatie[i].GetFitness() / fitnessTotal;
	}

	std::vector<Individ> nouaPopulatie(popSize);

	std::map<int, int> adaugiri;
	
	for (int i = 0; i < popSize; ++i)
	{
	
		int indexFound;
		do {
			float r = randomFloat(0, 1);
			for (indexFound = 0; indexFound < procentajeAdunate.size(); ++indexFound)
			{
				if (r < procentajeAdunate[indexFound]) break;
			}
		} while (adaugiri[indexFound] >= 10);
		adaugiri[indexFound]++;
		nouaPopulatie[i] = populatie[indexFound];
	}

	int maxim = 0;
	for (auto &m : adaugiri)
	{
		if (m.second > maxim) maxim = m.second;
	}
	std::cout << "Adaugiri maxime : " << maxim << "\n";
	populatie = nouaPopulatie;
}

SelectFunction(RoataNorocului)
{
	double fitnessTotal = 0;
	for (auto& individ : populatie)
	{
		fitnessTotal += individ.GetFitness();
	}
	std::vector<double> procentajeAdunate(populatie.size());
	procentajeAdunate[0] = populatie[0].GetFitness() / fitnessTotal;

	for (int i = 1; i < populatie.size(); ++i)
	{
		procentajeAdunate[i] = procentajeAdunate[i - 1] + populatie[i].GetFitness() / fitnessTotal;
	}
	
	std::vector<Individ> nouaPopulatie(popSize);

	for (int i = 0; i < popSize; ++i)
	{
		float r = randomFloat(0, 1);
		int indexFound;
		for (indexFound = 0; indexFound < procentajeAdunate.size(); ++indexFound)
		{
			if (r < procentajeAdunate[indexFound]) break;
		}
		nouaPopulatie[i] = populatie[indexFound];
	}


	populatie = nouaPopulatie;
}

MutateFunction(InversionMutation)
{
	float doIt = randomFloat(0, 1);
	if (doIt > Pm) return;

	auto perm = X.Convert();
	int p1 = 0, p2 = 0;
	do {
		p1 = randomInt(0, perm.size() - 1);
		p2 = randomInt(0, perm.size() - 1);
		if (p1 > p2) std::swap(p1, p2);
	} while (p1 == p2);
	for (int i = 0; i < (p2 - p1 + 1) / 2; ++i)
	{
		std::swap(perm[p1 + i], perm[p2 - i]);
	}
	X.ConvertFromNormalPermutation(perm);
}

MutateFunction(MutatieRandom)
{
	int nr = 0;
	for (int i = 0; i < X.GetSize(); ++i)
	{
		double r = randomFloat(0, 1);
		if (r > Pm) continue;
		nr++;
		/*X[i] = (X[i] + 1) % (X.GetSize() + 1 - i);
		if (X[i] == 0) X[i] = X.GetSize() + 1 - i;*/
		X[i] = randomInt(1, X.GetSize() + 1 - i);
	}
	//std::cout << nr << "\n"
}

MutateFunction(MutatiePerGena)
{
	//std::cout << Pm << "\n";
	int nr = 0;
	for (int i = 0; i < X.GetSize(); ++i)
	{
		double r = randomFloat(0, 1);
		if (r > Pm) continue;
		nr++;
		X[i] = (X[i] + 1) % (X.GetSize() + 1 - i);
		if (X[i] == 0) X[i] = X.GetSize() + 1 - i;
		//X[i] = randomInt(1, X.GetSize() + 1 - i);
	}
	//std::cout << nr << "\n";

}

MutateFunction(MutatieNormala)
{

	double r = randomFloat(0, 1);
	if (r > Pm) return;

	int poz_mutatie;
	poz_mutatie = randomInt(0, X.GetSize() - 1);
	/*std::cout << "Pozitia la care se face mutatia " << poz_mutatie << " si valoarea de pe poz respectiva " << X[poz_mutatie] << "\n";
	for (int i = 0; i <= X.GetSize(); i++)
		std::cout << X[i] << " ";*/
	//std::cout << "\n" << " DUPA MUTATIE" << "\n";
	X[poz_mutatie] = (X[poz_mutatie] + 1) % (X.GetSize() + 1 - poz_mutatie);
	if (X[poz_mutatie] == 0) X[poz_mutatie] = X.GetSize() + 1 - poz_mutatie;

	/*for (int i = 0; i <= X.GetSize(); i++)
		std::cout << X[i] << " ";*/
	//std::cout << "\n";

}


CrossingOver(CrossingOverMedie)
{
	Individ C1(P1.GetSize() + 1, false);
	Individ C2(P1.GetSize() + 1, false);

	double coef1 = (P1.GetFitness()) / (P1.GetFitness() + P2.GetFitness());

	double coef2 = 1 - coef1;

	for (int i = 0; i < P1.GetSize(); ++i)
	{
		C1[i] = (P1[i] * coef1 + P2[i] * coef2);
		C2[i] = (P1[i] * coef2 + P2[i] * coef1);
	}

	offspring.push_back(C1);
	offspring.push_back(C2);
}

CrossingOver(CrossOverParImpar)
{
	int pct_taiere;
	pct_taiere = randomInt(0, P1.GetSize());
	/*Punem al doilea parametru false ca sa nu mai generam random (vezi in Individ.h)*/
	Individ C1(P1.GetSize() + 1, false);
	Individ C2(P1.GetSize() + 1, false);


	//std::cout << "Tai aici " << pct_taiere << "\n";

	//dupa punctul de taiere ne uitam in dreapta in caz de valoarea respectiva exista si in stanga
	//se pune in copil urmatoarea cea mai mare valoare (care nu se gaseste in stanga)

	int blockSize = P1.GetSize() / (P1.GetSize()/2);

	for (int i = 0; i < P1.GetSize(); ++i)
	{
		int blockIndex = i / blockSize;
	

		if (blockIndex % 2 == 0)
		{
			C1[i] = P1[i];
			C2[i] = P2[i];
		}
		else {
			C1[i] = P2[i];
			C2[i] = P1[i];
		}
	}

	offspring.push_back(C1);
	offspring.push_back(C2);
}

CrossingOver(CrossOverNormal)
{
	for (int rep = 0; rep < 1; ++rep)
	{
		//punctul de taiere
		int pct_taiere;
		pct_taiere = randomInt(0, P1.GetSize());
		/*Punem al doilea parametru false ca sa nu mai generam random (vezi in Individ.h)*/
		Individ C1(P1.GetSize() + 1, false);
		Individ C2(P1.GetSize() + 1, false);


		//std::cout << "Tai aici " << pct_taiere << "\n";

		//dupa punctul de taiere ne uitam in dreapta in caz de valoarea respectiva exista si in stanga
		//se pune in copil urmatoarea cea mai mare valoare (care nu se gaseste in stanga)


		for (int i = 0; i < P1.GetSize(); ++i)
		{
			if (i <= pct_taiere)
			{
				C1[i] = P1[i];
				C2[i] = P2[i];
			}
			else {
				C1[i] = P2[i];
				C2[i] = P1[i];
			}
		}

		offspring.push_back(C1);
		offspring.push_back(C2);
		/*De implementat un crossOver*/
	}
}


/*
* Crossing-Overul care adauga la populatie copilasii
*/

CrossingOver(HGreX)
{
	auto findPos = [](std::vector<int>& v, int f)
	{
		//std::cout << "Am de cautat : " << f << "\n";
		for (auto it = v.begin(); it != v.end(); ++it)
		{
			if (*it == f)
			{
				//std::cout << "uite am gasit valoarea " << f << "\n";
				return it;
			}
		}
		return v.end();
	};
	Individ C1(P1.GetSize() + 1, false);
	Individ C2(P1.GetSize() + 1, false);

	std::vector<int> permP1 = P1.Convert();
	std::vector<int> permP2 = P2.Convert();

	std::vector<int> permC1(P1.GetSize() + 1);
	std::vector<int> permC2(P1.GetSize() + 1);

	std::vector<int> vizitate(permP1.size());

	for (int i = 1; i <= permP1.size(); ++i)
	{
		vizitate[i - 1] = i;
	}
	int startingPoint = randomInt(1, P1.GetSize());
	permC1[0] = startingPoint;
	vizitate.erase(findPos(vizitate, startingPoint));
	for (int index = 0; index < permC1.size() - 1; ++index)
	{
		std::vector<int> potentiali;
		auto it = findPos(permP1, permC1[index]);
		std::advance(it, 1);
		if (it == permP1.end())
		{
			it = permP1.begin();
		}
		if(findPos(vizitate, *it) != vizitate.end())
			potentiali.push_back(*it);
		it = findPos(permP2, permC1[index]);
		std::advance(it, 1);
		if (it == permP2.end())
		{
			it = permP2.begin();
		}
		if (findPos(vizitate, *it) != vizitate.end())
			potentiali.push_back(*it);
		int minim = -1;
		int alesul = -1;
		for (auto& e : potentiali)
		{
			if (minim == -1 || g->CostulMuchiei(permC1[index], e) < minim)
			{
				minim = g->CostulMuchiei(permC1[index], e);
				alesul = e;
			}
		}
		if (minim != -1)
		{
			permC1[index + 1] = alesul;
			vizitate.erase(findPos(vizitate, alesul));
		}
		else {
			int alegeri = 5;
			std::vector<int> candidatiRandom(alegeri);
			std::vector<int> copiuta = vizitate;
			for (int i = 0; i < std::min((int)vizitate.size(), alegeri); ++i)
			{
				int r = randomInt(0, copiuta.size() - 1);
				auto it = copiuta.begin();
				std::advance(it, r);
				candidatiRandom[i] = *it;
				copiuta.erase(it);
			}

			for (auto& e : candidatiRandom)
			{
				if (e == 0) break;
				if (minim == -1 || g->CostulMuchiei(permC1[index], e) < minim)
				{
					minim = g->CostulMuchiei(permC1[index], e);
					alesul = e;
				}
			}
			permC1[index + 1] = alesul;
			vizitate.erase(findPos(vizitate, alesul));
		}
	}

	std::vector<int> vizitate1(permP2.size());

	for (int i = 1; i <= permP2.size(); ++i)
	{
		vizitate1[i - 1] = i;
	}
	startingPoint = randomInt(1, P2.GetSize());
	permC2[0] = startingPoint;
	vizitate1.erase(findPos(vizitate1, startingPoint));
	for (int index = 0; index < permC2.size() - 1; ++index)
	{
		std::vector<int> potentiali;
		auto it = findPos(permP1, permC2[index]);
		std::advance(it, 1);
		if (it == permP1.end())
		{
			it = permP1.begin();
		}
		if (findPos(vizitate1, *it) != vizitate1.end())
			potentiali.push_back(*it);
		it = findPos(permP2, permC2[index]);
		std::advance(it, 1);
		if (it == permP2.end())
		{
			it = permP2.begin();
		}
		if (findPos(vizitate1, *it) != vizitate1.end())
			potentiali.push_back(*it);
		int minim = -1;
		int alesul = -1;
		for (auto& e : potentiali)
		{
			if (minim == -1 || g->CostulMuchiei(permC2[index], e) < minim)
			{
				minim = g->CostulMuchiei(permC2[index], e);
				alesul = e;
			}
		}
		if (minim != -1)
		{
			permC2[index + 1] = alesul;
			vizitate1.erase(findPos(vizitate1, alesul));
		}
		else {
			int alegeri = 5;
			std::vector<int> candidatiRandom(alegeri);
			std::vector<int> copiuta = vizitate1;

			for (int i = 0; i < std::min((int)vizitate1.size(), alegeri); ++i)
			{
				int r = randomInt(0, copiuta.size() - 1);
				auto it = copiuta.begin();
				std::advance(it, r);
				candidatiRandom[i] = *it;
			
				copiuta.erase(it);
			}
		
			for (auto& e : candidatiRandom)
			{
				if (e == 0) break;
				if (minim == -1 || g->CostulMuchiei(permC2[index], e) < minim)
				{
					minim = g->CostulMuchiei(permC2[index], e);
					alesul = e;
				}
			}
			permC2[index + 1] = alesul;
			vizitate1.erase(findPos(vizitate1, alesul));
		}
	}



	C1.ConvertFromNormalPermutation(permC1);
	C2.ConvertFromNormalPermutation(permC2);
	offspring.push_back(C1);
	offspring.push_back(C2);

	
}

CrossOverPop(CrossOverFitnessBased)
{
	int nbToCross = populatie.size() * Pc ;
	std::vector<Individ> copilasi;

	for (int i = 0; i < nbToCross; i += 2)
	{
	
		int rd = randomInt(1, 2);

		CrossingOver((*functia)) = HGreX;
		switch (rd)
		{
		case 1: functia = AEX; break;
		case 2: functia = HGreX; break;
		default:
			break;
		}
		functia = HGreX;

		functia(populatie[i], populatie[i + 1], copilasi, g);
		functia(populatie[i], populatie[i + 1], copilasi, g);
		functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);
		//functia(populatie[i], populatie[i + 1], copilasi, g);

		//PartiallyMappedCrossover(populatie[i], populatie[i + 1], copilasi, g);
		//OX(populatie[i], populatie[i + 1], copilasi, g);
		//CrossingOverMedie(populatie[i], populatie[i + 1], copilasi, g);


		//CrossingOverMedie()
		
	}
	/*double fitnessTotal = 0;
	for (auto& individ : populatie)
	{
		fitnessTotal += individ.GetFitness();
	}
	std::vector<double> procentajeAdunate(populatie.size());
	procentajeAdunate[0] = populatie[0].GetFitness() / fitnessTotal;

	for (int i = 1; i < populatie.size(); ++i)
	{
		procentajeAdunate[i] = procentajeAdunate[i - 1] + populatie[i].GetFitness() / fitnessTotal;
	}
	


	for (int i = 0; i < nbToCross; ++i)
	{
		int indexFound1;
		int indexFound2;
		do {
			float r1 = randomFloat(0, 1);
			float r2 = randomFloat(0, 1);
			
			for (indexFound1 = 0; indexFound1 < procentajeAdunate.size(); ++indexFound1)
			{
				if (r1 < procentajeAdunate[indexFound1]) break;
			}
			for (indexFound2 = 0; indexFound2 < procentajeAdunate.size(); ++indexFound2)
			{
				if (r2 < procentajeAdunate[indexFound2]) break;
			}
		} while (indexFound1 == indexFound2);

		CrossingOverMedie(populatie[indexFound1], populatie[indexFound2], copilasi, g);
	}*/



	for (auto& c : copilasi)
	{
		populatie.push_back(c);
	}
}

CrossOverPop(CrossOverPopDistructiv)
{
	std::vector<std::pair<float, int>> procentajeRandom(populatie.size());

	for (int index = 0; index < procentajeRandom.size(); ++index)
	{
		procentajeRandom[index].first = randomFloat(0, 1);
		procentajeRandom[index].second = index;
	}

	std::sort(procentajeRandom.begin(), procentajeRandom.end(), [](std::pair<float, int>& a, std::pair<float, int>& b) {
		return a.first < b.first;
		});

	int ultimulAcceptat = -1;
	for (int i = 0; i < procentajeRandom.size(); ++i)
	{
		if (procentajeRandom[i].first >= Pc) break;
		//ultimulAcceptat = i;
		ultimulAcceptat = i;
	}


	std::vector<Individ> copilasi;

	for (int i = 0; i < ultimulAcceptat; i += 2)
	{
		int indexP1 = procentajeRandom[i].second;
		int indexP2 = procentajeRandom[i].second;
		CrossOverNormal(populatie[indexP1], populatie[indexP2], copilasi, g);
		populatie[indexP1] = copilasi[copilasi.size() - 2];
		populatie[indexP2] = copilasi[copilasi.size() - 1];
		
	}

	std::cout << "Numarul de copilasi : " << copilasi.size() << "\n";

	/*for (auto& c : copilasi)
	{
		populatie.push_back(c);
	}*/
}

CrossOverPop(CrossOverPopNedistructiv)
{
	std::vector<std::pair<float, int>> procentajeRandom(populatie.size());

	for (int index = 0; index < procentajeRandom.size(); ++index)
	{
		procentajeRandom[index].first = randomFloat(0, 1);
		procentajeRandom[index].second = index;
	}

	std::sort(procentajeRandom.begin(), procentajeRandom.end(), [](std::pair<float, int>& a, std::pair<float, int>& b) {
		return a.first < b.first;
		});

	int ultimulAcceptat = -1;
	for (int i = 0; i < procentajeRandom.size(); ++i)
	{
		if (procentajeRandom[i].first >= Pc) break;
		//ultimulAcceptat = i;
		ultimulAcceptat = i;
	}


	std::vector<Individ> copilasi;

	for (int i = 0; i < ultimulAcceptat; i += 2)
	{
		int indexP1 = procentajeRandom[i].second;
		int indexP2 = procentajeRandom[i].second;
		CrossOverNormal(populatie[indexP1], populatie[indexP2], copilasi, g);


	}

	std::cout << "Numarul de copilasi : " << copilasi.size() << "\n";

	for (auto& c : copilasi)
	{
		populatie.push_back(c);
	}
}


CrossOverPop(CrossOverPopNormal)
{
	/*De implementat un crossOver pe populatie*/
}

