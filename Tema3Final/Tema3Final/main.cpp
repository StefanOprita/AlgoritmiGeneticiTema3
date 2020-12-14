#include <iostream>
#include "CitesteGraf.h"
#include "RandomFunctions.h"
#include "Individ.h"
#include "GeneticAlgorithm.h"
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
	Graf* g = CitesteGraf::CitesteDinFisier("./sourcesSymmetricTSP/berlin52.tsp");
	
	std::cout << g->Marimea() << "\n";
	std::cout << g->CostulMuchiei(1, 50) << "\n";

	Graf* g2 = CitesteGraf::CitesteDinFisier("./sourcesAssymetricTSP/br17.atsp");

	std::cout << g2->Marimea() << "\n";
	std::cout << g2->CostulMuchiei(1, 2) << "\n";


	Individ test(4);
	
	auto v = test.Convert();
	std::cout << "\n";

	for (auto& e : v)
	{
		std::cout << e << " ";
	}

	std::cout << "\n";

	/*de asemenea, poti face si  test[index]  ca sa accesezi (sau sa modifici) o bucata din el
	are si functia getSize care returneaza care elemente sunt in permutarea sa speciala 
	(Adica cat i-ai dat tu, 4, minus 1 ca nu are sens sa tinem minte ultima bucata ca mereu o
	sa fie 1)
	*/

	system("Pause");
}