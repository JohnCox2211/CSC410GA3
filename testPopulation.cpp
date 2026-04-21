#include "population.h"
#include "cassert"
#include "iostream"
using namespace std;

// create dummy target
Pixel* makeTarget(int size){
    Pixel* target = new Pixel[size];
    for(int i = 0; i < size; i++){
        target[i] = {0,0,0};
    }

    return target;
}

// test population creation
void testGeneratePopulation(){
  population pop;
  pop.generatePopulation(5, 10);

  pop.printPopulation();

  cout << "testGeneratePopulation passed" << endl;
}

// test setting target
void testSetTarget(){
  population pop;
  Pixel* target = makeTarget(10);

  pop.setTarget(target, 10);

  delete[] target;

  cout << "testSetTarget passed" << endl;
}

// MAIN **********************************

int main(){
    cout << "POPULATION TESTS..." << endl;

    testGeneratePopulation();
    testSetTarget();
    //need to implement
    /*
    testSelectParents();
    testSetMutation();
    testCrossover();
    testGenerateNewPop();
    testCalcOverallFitnessPop();
    testFitnessNoTarget();
    */

    cout << "All population tests passed" << endl;
    return 0;
}