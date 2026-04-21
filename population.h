#include "genome.h"

class population{
public:
    population();  // class constructor (creates empty pop.)
    ~population(); // class destructor (frees memory)

    void generatePopulation(int popSize, int nGenes); // creates pop. of popSize, each genome has nGenes of genes
	void setTarget(Pixel* target, int imageSize);     // sets the target genome (image) used for fitness eval.
	void selectParents();                             // selects best 2 as parents based on fitness

	void setnCrossover(int nCrossover);               // set num of crossover points for reproduction
	int getnCrossover();                              // gets the num of crossover points

	void setMutation(double mRate);                   // set mutation rate for all genomes

	void generateNewPop();                            // generates new population using selected parents

    double calcOverallFitnessPop();                   // calc. avg. fitness of entire population

	void printParents();                              // prints parents 
	void printPopulation();                           // prints population


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