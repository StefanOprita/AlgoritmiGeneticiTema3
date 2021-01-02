#include <iostream>
#include "CitesteGraf.h"
#include "RandomFunctions.h"
#include "Individ.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"
int main()
{
	/*
	O sa folosim o clasa abstracta Graf. Cand umblam cu ele, le facem pointeri
	Ideea e ca sunt multe moduri in care pot sa fie citite grafurile astea magice
	(cum ai vazut si tu)
	Am facut Singletonul CitesteGraf care poate sa citeasca un fisier dat ca parametru(vezi exemplu mai jos)
	El  deschide fisierul, isi da seama magic ce fel de graf este (momentan am facut cu distanta efectiva
	intr-un plan 2d si matrice de adiacenta magica) si returneaza un pointer la graful ala
	Am facut doua clase care mostenesc clasa Graf pentru cele doua tipuri de citiri mentionate mai sus
	Clasa Abstracta are functia CostuMulchiei(nod i, nod j) care returneaza costul muchiei ij
	si Marimea() care spune cate noduri sunt
	O sa ne folosim de asta in algoritmul genetic... nu ne trebuie mai mult pana la urma
	Trebuie sa stim pur si simplu cate noduri sunt si care e costul unei muchii
	*/

	/*Exemplu cu costul unei muchii fiind distanta in planul euclidian 2D*/
	Graf* g = CitesteGraf::CitesteDinFisier("./sourcesAssymetricTSP/br17.atsp");
	std::cout << "Nenea Berlin: " << "\n";
	std::cout <<"Marimea "<< g->Marimea() << "\n";
	std::cout <<"Costul muchiei "<< g->CostulMuchiei(1, 50) << "\n";

	std::cout << "Simulated Annealing:  ";
	std::cout<< SA(g, simpleInitialize, simpleModify, 30);

	/*Graf* g2 = CitesteGraf::CitesteDinFisier("./sourcesAssymetricTSP/br17.atsp");

	std::cout << g2->Marimea() << "\n";
	std::cout << g2->CostulMuchiei(1, 2) << "\n";

	std::cout << "Individ" << "\n";
	Individ test(8);
	std::cout << "test2   ";
	Individ test2(8);
	test2 = test;


	auto v = test.Convert();
	std::cout << "\n";

	for (auto& e : v)
	{
		std::cout <<e << " ";
	}

	auto v2 = test.Convert();
	std::cout << "\n"<<"Cele din 2   ";

	for (auto& e : v2)
	{
		std::cout << e << " ";
	}*/
	
	/*std::cout << "\n"<<v.size()<<"\n";
	for (int i = 0; i < v.size()-1; i++)
		std::cout <<i<<" "<<i+1<<" "<< g->CostulMuchiei(v[i], v[i + 1])<<"\n";*/

	/*std::cout << "\n";
	MutatieNormala(test, 0.01);
	MutateFunction(MutatieNormala);
	 v = test.Convert();
	std::cout << "\n";

	for (auto& e : v)
	{
		std::cout << e << " ";
	}*/
	

	/*de asemenea, poti face si  test[index]  ca sa accesezi (sau sa modifici) o bucata din el
	are si functia getSize care returneaza care elemente sunt in permutarea sa speciala 
	(Adica cat i-ai dat tu, 4, minus 1 ca nu are sens sa tinem minte ultima bucata ca mereu o
	sa fie 1)
	*/

	system("Pause");
}