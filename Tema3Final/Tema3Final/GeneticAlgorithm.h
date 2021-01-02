#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include "Graf.h"
#include "Individ.h"

/*
	Eu zic ca e mai bine sa facem cu macro-uri 
	ca sa nu stam sa scriem de fiecare data signatura functiilor
	(vezi mai jos cum am definit GA)
*/


/*Functia de fitness: primeste un Individ si un Graf peste care sa fie evaluat
* iar valoarea sa de fitness este setata cu X.SetFitness(valoare)
*/
#define	FitnessFunction(name) void name(Individ& X, Graf* g)

/*Primeste vectorul de populatie, Graful peste care sa fie evaluata si functia cu care sa fie
* evaluati.
*/
#define	EvaluateFunction(name) void name(std::vector<Individ> &v, Graf *g, FitnessFunction((*fit)))

/*Primeste populatia curenta si o modifica cu roata norocului*/
#define	SelectFunction(name) void name(std::vector<Individ> &populatie, int popSize)

/*Face mutatia*/
#define	MutateFunction(name) void name(Individ &X, double Pm)

/*Functia de cross-over : primeste doi indivizi care sunt parintii, un vector de offstring
 iar copilasii facuti de parinti sunt pusi in vectorul de offstring, atat
*/
#define CrossingOver(name) void name(Individ &P1, Individ &P2, std::vector<Individ> &offspring, Graf* g)

/*
	Functia de CrossOverPop va face toata nebunia aia cu sortarea dupa un nr random 
	si apoi facem crossOver peste ei... obtinem la final un vector de offstring
	ce contine toti copilasii facuti si pe urma facem ce vrem cu ei: acoperim parintii cu ei etc
	eu zic ca cel mai bine e sa adaugam copii la populatie (asa am avut eu cele mai bune rezultate)
*/
#define CrossOverPop(name) void name(std::vector<Individ> &populatie, double Pc, Graf *g)


//asa am definit functiile, folosind macro-urile
FitnessFunction(FitnessNormal);

FitnessFunction(FitnessLaPutere);

EvaluateFunction(EvaluareNormala);

EvaluateFunction(EvaluareFancy);

SelectFunction(RoataNorocului);

SelectFunction(SelectiaTurneu);

SelectFunction(RoataNoroculuiLimitata);

MutateFunction(MutatieNormala);

MutateFunction(MutatiePerGena);

MutateFunction(MutatieRandom);

MutateFunction(InversionMutation);

CrossingOver(CrossOverNormal);

CrossingOver(CrossOverParImpar);

CrossingOver(PartiallyMappedCrossover);

CrossingOver(CX);

CrossingOver(OX);

CrossingOver(AEX);

CrossingOver(HGreX);

CrossingOver(CrossingOverMedie);

CrossOverPop(CrossOverPopNedistructiv);

CrossOverPop(CrossOverPopDistructiv);

CrossOverPop(CrossOverFitnessBased);

CrossOverPop(CrossOverPopNormal);

FitnessFunction(FitnessCris);

/*
	O sa zici ca e o nebunie aici dar eu zic ca e bine sa facem asa
	Ca sa fie usor de customizat Algoritmul
	Cand vrei sa testezi o noua functie de fitness poti pur si simplu sa schimbi
	din definitia de mai jos sa nu mai fie FitnessNormal sa fie FitnessulMeu
*/
double GA(Graf* g, int nbGenerations = 2000, int popSize = 100,
	double mutateChance = 0.01, double crossingOverP = 1,
	FitnessFunction((*fitness)) = FitnessNormal,
	EvaluateFunction((*eval)) = EvaluareFancy,
	SelectFunction((*select)) = SelectiaTurneu,
	MutateFunction((*mutate)) = MutatiePerGena,
	CrossOverPop((*crossPop)) =  CrossOverFitnessBased
);




