#pragma once
#include <vector>
#include <list>
#include <iostream>
#include "RandomFunctions.h"
class Individ
{
	int marimeADN;
	std::vector<int> permutare;
	double fitness = 0;
public:

	Individ();
	Individ(int size);

	void GenerareRandom();
	std::vector<int> Convert();

	int GetSize();

	double GetFitness();
	void SetFitness(double val);

	std::vector<int>::iterator begin();
	std::vector<int>::iterator end();

	int& operator[](int index);

};

