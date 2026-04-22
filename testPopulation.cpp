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

// test parent selection
void testSelectParents(){
  population pop;
  pop.generatePopulation(5, 10);

  Pixel* target = makeTarget(10);
  pop.setTarget(target, 10);

  pop.selectParents();

  // ensure no crash and parents exist
  pop.printParents();

  delete[] target;

  cout << "testSelectParents passed" << endl;
}

// test mutation setter
void testSetMutation(){
  population pop;
  pop.generatePopulation(4, 8);

  pop.setMutation(0.5);

  // invalid, should not change
  pop.setMutation(2.0);

  cout << "testSetMutation passed" << endl;
}

// tests crossover setter/getter
void testCrossover(){
  population pop;

  pop.setnCrossover(3);
  assert(pop.getnCrossover() == 3);

  //invalid should not change

  pop.setnCrossover(-1);
  assert(pop.getnCrossover() == 3);

  cout << "testCrossover passed" << endl;
}

// test generating new population
void testGenerateNewPop(){
  population pop;
  pop.generatePopulation(6, 12);

  Pixel* target = makeTarget(12);
  pop.setTarget(target, 12);

  pop.selectParents();
  pop.generateNewPop();

  pop.printPopulation();

  delete[] target;

  cout << "testGenerateNewPop passed" << endl;
}

// test overall fitness
void testCalcOverallFitnessPop(){
  population pop;
  pop.generatePopulation(4, 6);

  Pixel* target = makeTarget(6);
  pop.setTarget(target, 6);

  double fitness = pop.calcOverallFitnessPop();

  assert(fitness >= 0.0);

  delete[] target;

  cout << "testCalcOverallFitnessPop passed" << endl;
}

//test fitness with no target
void testFitnessNoTarget(){
  population pop;
  pop.generatePopulation(3, 5);

  double fitness = pop.calcOverallFitnessPop();

  assert(fitness == -1.0);

  cout << "testFitnessNoTarget passed" << endl;
}

// MAIN **********************************

int main(){
    cout << "POPULATION TESTS..." << endl;

    testGeneratePopulation();
    testSetTarget();
    testSelectParents();
    testSetMutation();
    testCrossover();
    testGenerateNewPop();
    testCalcOverallFitnessPop();
    testFitnessNoTarget();

    cout << "All population tests passed" << endl;
    return 0;
}