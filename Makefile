program: genome.o population.o main.o
	g++ -o program genome.o population.o main.o

genome.o: genome.h genome.cpp
	g++ -c genome.cpp

population.o: population.h population.cpp genome.h
	g++ -c population.cpp

main.o: main.cpp population.h genome.h
	g++ -c main.cpp


# TESTS *********************************************

testGenome: genome.o testGenome.o
	g++ -o testProgram genome.o testGenome.o

testPopulation: genome.o population.o testPopulation.o
	g++ -o testPopulation genome.o population.o testPopulation.o

testGenome.o: testGenome.cpp genome.h
	g++ -c testGenome.cpp

testPopulation.o: testPopulation.cpp population.h genome.h
	g++ -c testPopulation.cpp


clean:
	rm -f *.o program testGenome testPopulation