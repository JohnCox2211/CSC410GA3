#include "genome.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// constructor
genome::genome(){
	genes = NULL;
	nGenes = 0;
	mRate = 0.0; // mutation rate
}

// Destructer
genome::~genome(){
	deallocate();
}

// memory allocation
void genome::allocate(int nGenes){
	if(genes != NULL){
		deallocate();
	}
	
	if(nGenes <= 0) return;

	genes = new Pixel[nGenes];
	this->nGenes = nGenes;

	// init pixels
	for (int i = 0; i < nGenes; i++){
		genes[i].red = 0;
		genes[i].green = 0;
		genes[i].blue = 0;
	}
}

// free memory
void genome::deallocate(){
	if(genes == NULL) return;

	delete[] genes;
	genes = NULL;
	nGenes = 0;
}

// random RGB values
void genome::randomize(){
	for (int i = 0; i < nGenes; i++){
		genes[i].red = rand() % 256;
        	genes[i].green = rand() % 256;
        	genes[i].blue = rand() % 256;
	}
}

//setters
void genome::setRed(int index, int value){
	if(index >= 0 && index < nGenes){
		genes[index].red = value;
	}
}

void genome::setGreen(int index, int value){
        if(index >= 0 && index < nGenes){
                genes[index].green = value;
        }
}

void genome::setBlue(int index, int value){
        if(index >= 0 && index < nGenes){
                genes[index].blue = value;
        }
}


// getters
int genome::getRed(int index){
        if(index >= 0 && index < nGenes){
                return genes[index].red;
        }
	return -1;
}

int genome::getGreen(int index){
        if(index >= 0 && index < nGenes){
                return genes[index].green;
        }
        return -1;
}

int genome::getBlue(int index){
        if(index >= 0 && index < nGenes){
                return genes[index].blue;
        }
        return -1;
}

//print genes
void genome::print() {
    for (int i = 0; i < nGenes; i++) {
        cout << "Pixel " << i << ": ("
             << genes[i].red << ", "
             << genes[i].green << ", "
             << genes[i].blue << ")" << endl;
    }
}


// GA 2 FUNCTIONS ***************************

// mutation rate setter & getter
void genome::setmRate(double val){
	if(val >= 0.0 && val <= 1.0){
		mRate = val;
	}
}

double genome::getmRate(){
	return mRate;
}


// mutates a single pixel
void genome:: mutateGene(int index){
	if(index < 0 || index >= nGenes) return;

	double ran;

	// red
	ran = (double)rand() / RAND_MAX; // random num 0 - 1
	if(ran < mRate){
		genes[index].red = rand() % 256; // mutate if rate < ran
	}

	// green
	ran = (double)rand() / RAND_MAX; // random num 0 - 1
	if(ran < mRate){
		genes[index].green = rand() % 256; // mutate if rate < ran
	}

	// blue
	ran = (double)rand() / RAND_MAX; // random num 0 - 1
	if(ran < mRate){
		genes[index].blue = rand() % 256; // mutate if rate < ran
	}
} 

// mutate every pixel (entire genome)
void genome::mutate(){
	for(int i = 0; i < nGenes; i++){
		mutateGene(i);
	}
}

// calc diff between a pixel and a target pixel
double genome::calcGeneFitness(int index, Pixel targetPixel){
	if(index < 0 || index >= nGenes) return 0.0; // validate index

	//absolute difference of each color
	double redDiff = abs(genes[index].red - targetPixel.red);
	double greenDiff = abs(genes[index].green - targetPixel.green);
	double blueDiff = abs(genes[index].blue - targetPixel.blue);
	
	double avgDiff = (redDiff + greenDiff + blueDiff) / 3.0; // average difference of RGB

	// return normalized difference as percentage
	return avgDiff / 256;
}

// calc overall fitness of genome vs target image
double genome::calcOverallFitness(Pixel* target, int nPixels){
	if(nPixels != nGenes || target == NULL) return -1.0; // validate input

	//total diff accross all pixels/colors
	double totalDiff = 0.0;

	for(int i = 0; i < nGenes; i++){
		// abs diff for each RGB
		totalDiff += abs(genes[i].red - target[i].red);
		totalDiff += abs(genes[i].green - target[i].green);
		totalDiff += abs(genes[i].blue - target[i].blue);
	}
	// avg diff across all pixels/RGB
	double avgDiff = totalDiff / (3.0 * nGenes);

	// return normalized difference as percentage
	return avgDiff / 256;
}

// set pixel at given index to new val
void genome::setPixel(int index, Pixel newPixel){
	if(index < 0 || index >= nGenes) return; // validate index

	//validate each color is in allowed range
	if(newPixel.red < 0 || newPixel.red > 255) return;
	if(newPixel.green < 0 || newPixel.green > 255) return;
	if(newPixel.blue < 0 || newPixel.blue > 255) return;

	genes[index] = newPixel; // assign new pixel value
}

// gets pixel at given index, returns a default if invalid
Pixel genome::getPixel(int index){
	Pixel p = {0, 0, 0}; // default pixel

	// validate if index in bounds & return
	if(index >= 0 && index < nGenes){
		return genes[index];
	}

	return p;
}

