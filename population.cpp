#include "population.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

population::population() {
    individuals = NULL;
    targetGenome = NULL;
    nIndividuals = 0;
    nCrossover = 1; // default nCrossover as 1;
    p1 = -1;
    p2 = -1;
}

population::~population() {
    if (individuals != NULL) { // free memory
        delete[] individuals;
        individuals = NULL;
        nIndividuals = 0;
    }
    if (targetGenome != NULL) {
        delete[] targetGenome;
        targetGenome = NULL;
    }
}

void population::generate_population(int popSize, int nGenes) {
    individuals = new genome*[popSize]; // create array of genome objects
    nIndividuals = popSize;

    for (int i = 0;i < popSize;i++) {
        individuals[i] = new genome ();
        individuals[i]->allocate(nGenes); // create base pixel array for genome
        individuals[i]->randomize(); // randomize pixel array
    }
}

void population::set_target(genome::Pixel* target, int imageSize) {
    this->targetGenome = new genome::Pixel[imageSize]; // create pixel array

    // Iterate over target pixel array
    for (int i = 0; i < imageSize; i++) {
        // copy RGB values from input target
        targetGenome[i].red = target[i].red;
        targetGenome[i].green = target[i].green;
        targetGenome[i].blue = target[i].blue;
    }
}

void population::select_parents() {

    // Initialize to max possible value for fitness
    double best1 = 1.0;
    double best2 = 1.0;

    int best1_idx = 0;
    int best2_idx = 0;

    // Iterate over individuals
    // Find first and second minimum
    for (int i = 0; i < this->nIndividuals;i++) {
        int nPixels = individuals[i]->get_ngenes();
        
        // calculate fitness for current genome
        double cur_fitness = individuals[i]->calculate_overall_fitness(targetGenome, nPixels);
        
        // if current value is larger than first minimun
        if (cur_fitness <= best1) {
            best1_idx = i;
            best1 = cur_fitness;
        }

        // if current value is between first minum and second minimum
        if (cur_fitness <= best2 && cur_fitness >= best1 && i != best1_idx) {
            best2_idx = i;
            best2 = cur_fitness;
        }
    }

    // save found minimums
    this->p1 = best1_idx;
    this->p2 = best2_idx;
}

void population::set_nCrossover(int nCrossover) {
    this->nCrossover = nCrossover;    
}

int population::get_nCrossover() {
    return this->nCrossover;
}

void population::set_mutation(double mRate) {
    for (int i = 0;i < this->nIndividuals;i++) {
        individuals[i]->set_mRate(mRate);   
    }
}

void population::crossover(int idx, int iOffspring) {
    int nGenes = individuals[idx]->get_ngenes();
    // there will be nCrossover + 1 partitions
    // we will divide genome to partitions with the same length
    // however the last partition can be a bit longer if division is uneven
    int length = (int) (nGenes / (this->nCrossover + 1)); // length of partitions

    int l = 0; // left boundary
    int r = l + length - 1; // right boundary

    int cur_parent = this->p1; // variable to indicate which parent will share genes for current partition

    if (iOffspring == 1) { // swap starting parent for next offspring
        cur_parent = this->p1;
    } else if (iOffspring == 2) {
        cur_parent = this->p2;
    }


    while (r < nGenes) { // finish when right boundary is beyond nGenes
        for (int i = l; i <= r; i++) { // iterate over current partition
           // change gene of current individual to parent's gene
           individuals[idx]->set_pixel(i, individuals[cur_parent]->get_pixel(i));
        }
        l = r + 1; // left bound is shifted to right bound for next partition
        if  (r == nGenes - 1) { // if right bound has evenly ended at the last gene terminate the cycle
            r++;
        }
        else if (r + length > nGenes) { // if right bound has ended unevenly assign right bound to last gene
            r = nGenes - 1;
            // no need to swap parent because it is still the same partition
        } else { // otherwise just increment right bound to length of partition
            r += length;
            // also swap parents who will share the genes
            if (cur_parent == p1) {
                cur_parent = p2;
            } else if (cur_parent == p2) {
                cur_parent = p1;
            }
        }
    }
}

void population::generate_new_population(int useRoulette) {
    if(useRoulette == 1) {
            //TODO
    } else {
        select_parents(); // determine two best fitting individuals
        int iOffspring = 1; // variable to count crossover offsprings
        for (int i = 0;i < nIndividuals;i++) {
            if (i != this->p1 && i != this->p2) { // p1 and p2 will be intact in the next gen 
                if (iOffspring <= 2) { // will be only 2 crossover offsprings
                    crossover(i, iOffspring); // do crossover for current individual
                    iOffspring++;
                } else {
                    individuals[i]->mutate(); // mutate other individuals
                }
            }
        }
    }
}

double population::calculate_overall_fitness() {
    double sumErrors = 0.0;

    // sum up the average fitness for each individuals
    for (int i = 0; i < nIndividuals; i++) {
        int nPixels = individuals[i]->get_ngenes();
        double fitness = individuals[i]->calculate_overall_fitness(this->targetGenome, nPixels);
        sumErrors += fitness;
    }
    // return average
    return sumErrors / nIndividuals;
}

void population::print_parents() {
    if (p1 == -1 && p2 == -1) {
        cout << "no parents yet set" << endl;
    } else {
        cout << "Parent 1: " << p1 << endl;
        cout << "Parent 2: " << p2 << endl;
    }
}

void population::print_population() {
    cout << "Crossover points: " << nCrossover << endl;
    for (int i = 0; i < nIndividuals; i++) {
        cout << "Individual " << i << endl;
        cout << "mRate: " << individuals[i]->get_mRate() << endl;
        cout << "[";
        for (int j = 0; j < individuals[i]->get_ngenes(); j++) {
            cout << "{";
            cout << individuals[i]->get_red(j) << ",";
            cout << individuals[i]->get_green(j) << ",";
            cout << individuals[i]->get_blue(j) << "}";
        }
        cout << "]" << endl;
        cout << "-------------" << endl;
    }
}

