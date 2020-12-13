#include "CitesteGraf.h"

CitesteGraf::CitesteGraf()
{

}

CitesteGraf& CitesteGraf::Get()
{
	static CitesteGraf instanta;
	return instanta;
}

Graf* CitesteGraf::CitesteDinFisier(std::string caleSpreFisier)
{
	return CitesteGraf::Get().Internal_CitesteDinFisier(caleSpreFisier);
}

Graf* CitesteGraf::Internal_CitesteDinFisier(std::string caleSpreFisier)
{
	std::ifstream input(caleSpreFisier.c_str());

	std::string linie;

	/*Citim primele 3 linii care sunt inutile*/
	std::getline(input, linie);
	std::getline(input, linie);
	std::getline(input, linie);

	/* Citesc dimensiunea linia cu dimensiunea*/
	std::getline(input, linie);
	std::cout.flush();
	int index = linie.find(" ");
	int dimensiune = std::stoi(linie.substr(index));

	/*Citesc tipul de graf(cum is date costurile muchiilor)*/
	std::getline(input, linie);
	std::string tip = linie.substr(linie.find(" ") + 1);
	


	if (tip == "EUC_2D")
	{
		//mai trebuie sa citim o linie inutila
		std::getline(input, linie);
		return CitesteGrafEuclidian(input, dimensiune);
	}
	if (tip == "EXPLICIT")
	{
		//citim o linie care zice cum is date... eu in cele pe care le-am gasit, erau toate FULL_MATRIX
		std::getline(input, linie);
		std::getline(input, linie);
		return CitesteGrafCuMatrice(input, dimensiune);
	}

	return nullptr;
}


Graf* CitesteGraf::CitesteGrafCuMatrice(std::ifstream& input, int dimensiune)
{
	GrafMatriceAdiacenta* graf = new GrafMatriceAdiacenta(dimensiune);
	std::string linie;

	int i = 1, j = 1;

	while (std::getline(input, linie))
	{
		if (linie == "EOF") break;
		linie = linie.substr(linie.find_first_not_of(" "));
		std::vector<std::string> cuvinte;

		char* aux = new char[linie.size() + 1];
		strcpy(aux, linie.c_str());
		char* p = strtok(aux, " ");
		while (p)
		{
			if (strlen(p) > 0)
			{
				cuvinte.push_back(p);
			}
			p = strtok(NULL, " ");
		}

		for (auto& cuv : cuvinte)
		{
			graf->PuneInMatrice(i, j, std::stod(cuv));
			j++;
			if (j > dimensiune)
			{
				i++;
				j = 1;
			}
		}
	}
	return graf;
}

Graf* CitesteGraf::CitesteGrafEuclidian(std::ifstream& input, int dimensiune)
{
	GrafEuclidian* graf = new GrafEuclidian(dimensiune);

	std::string linie;
	while (std::getline(input, linie))
	{
		if (linie == "EOF") break;
		//std::cout << linie << "\n";
		auto cuvinte = SeparaInCuvinte(linie, " ");
		//std::cout << cuvinte.size() << "atatea gasite\n";
		int nod = std::stoi(cuvinte[0]);
		graf->PuneCoordonateLaNod(nod, { std::stod(cuvinte[1]), std::stod(cuvinte[2]) });
	}

	return graf;
}

std::vector<std::string> CitesteGraf::SeparaInCuvinte(std::string s, std::string delimitator)
{
	std::vector<std::string> cuvinte;
	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimitator)) != std::string::npos) {
		token = s.substr(0, pos);
		//std::cout << token << "\n";
		cuvinte.push_back(token);
		s.erase(0, pos + delimitator.length());
	}
	cuvinte.push_back(s);
	return cuvinte;
}