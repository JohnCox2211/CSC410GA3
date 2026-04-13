#include "genome.h"

class population{
public:
    population();
    ~population();

    void generatePopulation(int popSize, int nGenes); // 
	void setTarget(Pixel* target, int imageSize); //
	void selectParents(); //

	void setnCrossover(int nCrossover); //
	int getnCrossover(); //

	void setMutation(double mRate); //

	void generateNewPop(int useRoulette); //

    double calcOverallFitness();

	void printParents(); //
	void printPopulation(); //


private:
    genome* individuals;  // dynamic array of genomes (the population)
    int nIndividuals;     // num of genomes in pop

    Pixel* targetGenome;  // target image pixels for fitness comparison
    int imageSize;        // num pixels in target image

    int parentIndex1;     // index of best parent in pop
    int parentIndex2;     // index of 2nd best parent in pop
    bool parentsSelected; // indicates whether parents were selected

    int nCrossover;       // num of crossover points used in reproduction
    double mRate;         // mutation rate applied to each genome 
};