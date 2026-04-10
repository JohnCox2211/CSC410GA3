program: genome.o main.o
	g++ -o program genome.o main.o

genome.o: genome.h genome.cpp
	g++ -c genome.cpp

main.o: main.cpp
	g++ -c main.cpp

test: genome.o testGenome.o
	g++ -o testProgram genome.o testGenome.o

testGenome.o: testGenome.cpp genome.h
	g++ -c testGenome.cpp

clean:
	rm -f *.o program testProgram