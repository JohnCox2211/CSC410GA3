#include "population.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// class constructor (creates empty pop.)
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

// class destructor (frees memory)
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

//creates pop. of popSize, each genome has nGenes of genes
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

// sets the target genome (image) used for fitness eval.
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

// // selects best 2 as parents based on fitness
void population::selectParents(){
	if(targetGenome == NULL || nIndividuals < 2) return;

    double best1 = individuals[0].calcOverallFitness(targetGenome, imageSize);
    double best2 = individuals[1].calcOverallFitness(targetGenome, imageSize);

    parentIndex1 = 0;
    parentIndex2 = 1;

    // ensures best1 is smaller
    if(best2 < best1){
        double tempFit = best1;
        best1 = best2;
        best2 = tempFit;

        int tempIndex = parentIndex1;
        parentIndex1 = parentIndex2;
        parentIndex2 = tempIndex;
    }

    for(int i = 0; i < nIndividuals; i++){
        double fit = individuals[i].calcOverallFitness(targetGenome, imageSize);
        
        if(fit < best1){
            best2 = best1;
            parentIndex2 = parentIndex1;

            best1 = fit;
            parentIndex1 = i;
        }
        else if(fit < best2){
            best2 = fit;
            parentIndex2 = i;
        }
    }

    parentsSelected = true;
}

// crossover points
// set num of crossover points for reproduction
void population::setnCrossover(int nCrossover){
	if(nCrossover > 0){
        this->nCrossover = nCrossover;
    }
}

// gets the num of crossover points
int population::getnCrossover(){
	return nCrossover;
}

// set mutation rate for all genomes (images)
void population::setMutation(double mRate){
	if(mRate >= 0.0 && mRate <= 1.0){
        this->mRate = mRate;

        for(int i =0; i < nIndividuals; i++){
            individuals[i].setmRate(mRate);
        }
    }
}

// generates new population using selected parents
void population::generateNewPop(){
	if(!parentsSelected) return;

    genome* newPop = new genome[nIndividuals];

    genome& p1 = individuals[parentIndex1];
    genome& p2 = individuals[parentIndex2];

    int nGenes = imageSize;

    for(int i = 0; i < nIndividuals; i++){
        newPop[i].allocate(nGenes);

        int crossoverPoint = rand() % nGenes;

        for(int g = 0; g < nGenes; g++){
            if(g < crossoverPoint){
                newPop[i].setPixel(g, p1.getPixel(g));
            }
            else {
                newPop[i].setPixel(g, p2.getPixel(g));
            }
        }

        newPop[i].setmRate(mRate);
        newPop[i].mutate();
    }

    delete[] individuals;
    individuals = newPop;
}

// calc. avg. fitness of entire population 
double population::calcOverallFitnessPop(){
    if(targetGenome == NULL) return -1.0;

    double total = 0.0;

    for(int i = 0; i < nIndividuals; i++){
        total += individuals[i].calcOverallFitness(targetGenome, imageSize);
    }

    return total/nIndividuals;
}

// PRINT FUNCTIONS
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

    for(int i = 0; i < nIndividuals; i++){
        cout << "individual " << i << ":" << endl;
        individuals[i].print();
    }
}