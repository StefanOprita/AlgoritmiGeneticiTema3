#include "Individ.h"

Individ::Individ()
	:marimeADN(0)
{}

Individ::Individ(int size)
	:marimeADN(size)
{
	permutare = std::vector<int>(marimeADN);
	GenerareRandom();
	for (auto& i : permutare)
	{
		std::cout << i << " ";
	}
}


double Individ::GetFitness()
{
	return fitness;
}
void Individ::SetFitness(double val)
{
	fitness = val;
}


void Individ::GenerareRandom()
{
	for (int i = 0; i < marimeADN - 1; ++i)
	{
		this->permutare[i] = randomInt(1, marimeADN - i);
	}
}

std::vector<int> Individ::Convert()
{
	std::list<int> listaAjutatoare;
	for (int i = 1; i <= marimeADN; i++)
	{
		listaAjutatoare.push_back(i);
	}
	std::vector<int> permutareReala(marimeADN);
	for (int i = 0; i < marimeADN - 1; ++i)
	{
		int poz = permutare[i];
		int aux = 1;
		for (auto it = listaAjutatoare.begin(); it != listaAjutatoare.end(); ++it)
		{
			if (aux == poz)
			{
				permutareReala[i] = *it;
				listaAjutatoare.erase(it);
				break;
			}
			aux++;
		}
	}
	permutareReala[marimeADN - 1] = listaAjutatoare.front();
	return permutareReala;
}



std::vector<int>::iterator  Individ::begin()
{
	return permutare.begin();
}
std::vector<int>::iterator Individ::end()
{
	return permutare.end();
}

int& Individ::operator[](int index)
{
	return permutare[index];
}

int Individ::GetSize()
{
	return marimeADN - 1;
}