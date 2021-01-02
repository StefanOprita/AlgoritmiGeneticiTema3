#include <iostream>
#include "CitesteGraf.h"
#include "RandomFunctions.h"
#include "Individ.h"
#include "GeneticAlgorithm.h"
#include "SimulatedAnnealing.h"

#include <chrono>
#include <utility>
#define NOW std::chrono::high_resolution_clock::now();
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

	/*std::vector<std::string> listaDeFacutPesteNoaptePls;
	listaDeFacutPesteNoaptePls.push_back("rbg403");
	//listaDeFacutPesteNoaptePls.push_back("rbg358");
		//listaDeFacutPesteNoaptePls.push_back("rbg323");
	listaDeFacutPesteNoaptePls.push_back("ft70");
		//listaDeFacutPesteNoaptePls.push_back("ft53");
	listaDeFacutPesteNoaptePls.push_back("ftv44");
		//listaDeFacutPesteNoaptePls.push_back("ftv38");
	listaDeFacutPesteNoaptePls.push_back("ftv35");
		//listaDeFacutPesteNoaptePls.push_back("ftv33");
		//listaDeFacutPesteNoaptePls.push_back("br17");
	

	for (auto& fisier : listaDeFacutPesteNoaptePls)
	{
		std::string Path = "./sourcesAssymetricTSP/" + fisier + ".atsp";
		Graf* g = CitesteGraf::CitesteDinFisier(Path);

		std::string output_st = "./" + fisier + "_rezultate.txt";
		std::ofstream out(output_st);
		for (int i = 0; i < 30; ++i)
		{
			auto t1 = NOW;
			out << GA(g) << " ";
			auto t2 = NOW;
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

			out << double(duration) / 1000000. << "\n";

		}
	}
	*/

    /*Graf* g = CitesteGraf::CitesteDinFisier("./sourcesAssymetricTSP/ftv38.atsp");
	

	GA(g);

	std::vector<int> p1 = { 5, 1, 7, 8, 4, 9, 6, 2, 3 };
	std::vector<int> p2 = { 3, 6, 2, 5, 1, 9, 8, 4, 7 };

	Individ P1(p1.size(), false);
	Individ P2(p2.size(), false);

	P1.ConvertFromNormalPermutation(p1);
	P2.ConvertFromNormalPermutation(p2);

	std::vector<Individ> aux;
	HGreX(P1, P2, aux, g);*/

	/*int pm = 0.01;
	int nr = 0;
	for (int i = 0; i < 100; ++i)
	{
		float r = randomFloat(0, 1);
		if (r <= pm) nr++;
	}
	
	std::cout << (float)nr / 100;*/
	
	Graf* g = CitesteGraf::CitesteDinFisier("./sourcesAssymetricTSP/ft53.atsp");
	std::cout << SA(g, simpleInitialize, simpleModify, 30);


	system("Pause");
}