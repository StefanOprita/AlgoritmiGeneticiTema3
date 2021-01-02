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
	double costDrum = 0;
public:

	Individ();
	/*
	* Constructorul magic al Individului
	* Al doilea parametru ii zice daca sa genereze random sau nu vectorul
	* mai mult e pus ca sa nu pierdem timp sa generam pentru copilasi, ca oricum punem peste ei
	* altceva
	*/
	Individ(int size, bool generateRandom = true);

	void GenerareRandom();
	std::vector<int> Convert();

	void ConvertFromNormalPermutation(std::vector<int> &normalPerm);

	/*
	Returneaza marimeADN - 1
	*/
	int GetSize();

	double GetFitness();
	void SetFitness(double val);

	double GetCost();
	void SetCost(double val);

	void Print() const;

	std::vector<int>::iterator begin();
	std::vector<int>::iterator end();

	int& operator[](int index);

};

