#include "genome.h"

class population {
private:
    genome** individuals;
    genome::Pixel* targetGenome;
    int nIndividuals, p1, p2, nCrossover;
    void crossover(int idx, int iOffspring);
public:
    population();
    ~population();
    void generate_population(int popSize, int nGenes);
    void set_target(genome::Pixel* target, int imageSize);
    void select_parents();
    void set_nCrossover(int nCrossover);
    int get_nCrossover();
    void set_mutation(double mRate);
    void generate_new_population(int useRoulette);
    double calculate_overall_fitness();
    void print_parents();
    void print_population();
};

