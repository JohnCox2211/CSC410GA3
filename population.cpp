#include "population.h"
#include <iostream>
#include <cstdlib>
using namespace std;

//constructor
population::population(){
    individuals = NULL;      // dynamic array of genomes (the population)
    nIndividuals = 0;        // num of genomes in pop

    targetGenome = NULL;     // target image pixels for fitness comparison
    imageSize = 0;           // num pixels in target image

    parentIndex1 = -1;       // index of best parent in pop
    parentIndex2 = -1;       // index of 2nd best parent in pop
    parentsSelected = false; // indicates whether parents were selected

    nCrossover = 1;          // num of crossover points used in reproduction
    mRate = 0.0;             // mutation rate applied to each genome 
}

// destructor
population::~population(){
    if(individuals != NULL){
        delete[] individuals;
        individuals = NULL;
    }

    if(targetGenome != NULL){
        delete[] targetGenome;
        targetGenome = NULL;
    }

    nIndividuals = 0;
}

// create population
void population::generatePopulation(int popSize, int nGenes){
	if(individuals != NULL){
        delete[] individuals;
    }

    individuals = new genome[popSize];
    nIndividuals = popSize;

    for(int i = 0; i < popSize; i++){
        individuals[i].allocate(nGenes);
        individuals[i].randomize();
        individuals[i].setmRate(mRate);
    }
}

// set target image
void population::setTarget(Pixel* target, int imageSize){
	if(targetGenome != NULL){
        delete[] targetGenome;
    }

    this->imageSize = imageSize;
    targetGenome = new Pixel[imageSize];

    for(int i = 0; i < imageSize; i++){
        targetGenome[i] = target[i];
    }
}

// select best 2 parents
void population::selectParents(){
	if(targetGenome == NULL || nIndividuals == 0) return;

    double best1;
    double best2;

    parentIndex1 = -1;
    parentIndex2 = -1;

    for(int i = 0; i < nIndividuals; i++){
        double fit = individuals[i].calcOverallFitness(targetGenome, imageSize);
        
        if(fit < best1){
            best2 = best1;
            parentIndex2 = parentIndex1

            best1 = fit;
            parentIndex1 = i;
        }
        else if{
            best2 = fit;
            parentIndex2 = i;
        }
    }

    parentsSelected = true;
}

// crossover points
// sets crossover
void population::setnCrossover(int nCrossover){
	if(nCrossover > 0){
        this->nCrossover = nCrossover;
    }
}

// gets crossover
int population::getnCrossover(){
	return nCrossover;
}

// 
void population::setMutation(double mRate){
		return -1;
}

// 
void population::generateNewPop(int useRoulette){
		return -1;
}

// prints parents
void population::printParents(){
	if(!parentsSelected){
        cout << "No parents set" << endl;
        return;
    }

    cout << "Parent 1 (index " << parentIndex1 << "):" << endl;
    individuals[parentIndex1].print();

    cout << "Parent 2 (index " << parentIndex2 << "):" << endl;
    individuals[parentIndex2].print();
}

// prints population
void population::printPopulation(){
	cout << "Population size: " << nIndividuals << endl;
    cout << "Crossover points: " << nCrossover << endl;
	cout << "Mutation rate: " << mRate << endl;

    for(int i = 0; i < nIndividuals; i++)
        cout << "individual " << i << ":" << endl;
        individuals[i].print();
    }
}