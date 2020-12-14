#include "GeneticAlgorithm.h"

void GA(Graf* g, int nbGenerations, int popSize,
	double mutateChance, double crossingOverP,
	FitnessFunction((*fitness)),
	EvaluateFunction((*eval)),
	SelectFunction((*select)),
	MutateFunction((*mutate)),
	CrossOverPop((*crossPop))
)
{

	/*De implementat marele algoritm genetic*/
}

FitnessFunction(FitnessNormal)
{
	/*De implementat magia fitnessului*/
}

EvaluateFunction(EvaluareNormala)
{
	/*De implemenatat magia evaluarii populatiei*/
}

SelectFunction(RoataNorocului)
{
	/*De implementat roata norocului*/
}

MutateFunction(MutatieNormala)
{
	/*de implementat o mutatie*/
}

CrossingOver(CrossOverNormal)
{
	/*De implementat un crossOver*/
}

CrossOverPop(CrossOverPopNormal)
{
	/*De implementat un crossOver pe populatie*/
}