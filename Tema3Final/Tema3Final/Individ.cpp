#include "Individ.h"

Individ::Individ()
	:marimeADN(0)
{}

Individ::Individ(int size, bool generateRandom)
	:marimeADN(size)
{
	permutare = std::vector<int>(marimeADN);
	if (generateRandom)
	{
		GenerareRandom();
		/*for (auto& i : permutare)
		{
			std::cout << i << " ";
		}*/
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

double Individ::GetCost()
{
	return costDrum;
}
void Individ::SetCost(double val)
{
	costDrum = val;
}


void Individ::GenerareRandom()
{
	for (int i = 0; i < marimeADN - 1; ++i)
	{
		this->permutare[i] = randomInt(1, marimeADN - i);
	}
}

void Individ::ConvertFromNormalPermutation(std::vector<int> &normalPerm)
{
	std::list<int> listaAjutatoare;
	for (int i = 1; i <= marimeADN; i++)
	{
		listaAjutatoare.push_back(i);
	}

	for (int i = 0 ; i < normalPerm.size() - 1; ++i)
	{
		int index = 0;
		for (auto it = listaAjutatoare.begin(); it != listaAjutatoare.end(); ++it)
		{
			index++;
			if (*it == normalPerm[i])
			{
				this->permutare[i] = index;
				listaAjutatoare.erase(it);
				break;
			}
		}
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


void Individ::Print() const
{
	//int counter = 0;
	for (int i = 0; i < marimeADN - 1; ++i)
	{
		std::cout << permutare[i] << " ";
	}
	std::cout << "\n";
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