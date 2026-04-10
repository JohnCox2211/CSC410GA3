struct Pixel {
	int red;
	int green;
	int blue;
};

class genome{
public:
	genome();
	~genome();
	void allocate(int nGenes);
	void deallocate();
	void randomize();

	//setters
	void setRed(int index, int value);
	void setGreen(int index, int value);
	void setBlue(int index, int value);

	//getters
	int getRed(int index);
	int getGreen(int index);
	int getBlue(int index);

	void print(); // for display

	void setmRate(double val); // set mutation rate 0 - 1
	double getmRate(); // return current mutation rate

	void mutateGene(int index); // mutates singe pixel at give index
	void mutate(); // mutates all pixels 

	// calc single pixel fitness vs target, returns normalized avg RGB diff or -1.0
	double calcGeneFitness(int index, Pixel targetPixel);  
	// calc overall fitness for genome vs target pixels, 
	//returns normalized avg RGB diff across all genes or -1.0 for invalid
	double calcOverallFitness(Pixel* target, int nPixels);

	void setPixel(int index, Pixel newPixel); //set given pixel RGB vals
	Pixel getPixel(int index); // returns pixel at given index or (0, 0, 0) if invalid index


	// NEW FUNCTIONS******************************************

	void generatePopulation(int popSize, int nGenes); // 
	void setTarget(Pixel* target, int imageSize); //
	void selectParents(); //

	void setnCrossover(int nCrossover); //
	int getnCrossover(); //

	void setMutation(double mRate); //

	void generateNewPop(int useRoulette); //

	void printParents(); //
	void printPopulation(); //

	// calcOverallFitness implemented in GA2

private:
	Pixel* genes;
	int nGenes;
	double mRate; // mutation rate

	//NEW VARIABLES ***********************
};

