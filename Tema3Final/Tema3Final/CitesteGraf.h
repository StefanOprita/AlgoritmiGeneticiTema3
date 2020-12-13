#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Graf.h"
#include "GrafEuclidian.h"
#include "GrafMatriceAdiacenta.h"
#include <string>
#include <fstream>
#include <iostream>
class CitesteGraf
{
public:
	CitesteGraf(const CitesteGraf& other) = delete;
	CitesteGraf& operator=(const CitesteGraf& other) = delete;

	static CitesteGraf& Get();

	static Graf* CitesteDinFisier(std::string);
private:
	std::vector<std::string> SeparaInCuvinte(std::string s, std::string delimitatori);
	Graf* CitesteGrafEuclidian(std::ifstream& input, int dimensiune);
	Graf* CitesteGrafCuMatrice(std::ifstream& input, int dimensiune);
	Graf* Internal_CitesteDinFisier(std::string);
	CitesteGraf();
};

