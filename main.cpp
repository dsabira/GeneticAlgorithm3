#include "population.h"
#include <iostream> 
#include <cmath>
using namespace std;

int main() {
    
    population myPop;

    myPop.generate_population(10, 3);

    myPop.set_nCrossover(2);

    genome::Pixel* target = new genome::Pixel[3];

    target[0].red = 124;
    target[0].green = 25;
    target[0].blue = 0;

    target[1].red = 254;
    target[1].green = 56;
    target[1].blue = 186;

    target[2].red = 86;
    target[2].green = 128;
    target[2].blue = 189;
    
    myPop.set_target(target, 3);

    myPop.set_mutation(0.6);

    for (int i = 0; i < 20; i++) {
        myPop.generate_new_population(0);
        double fitness = myPop.calculate_overall_fitness();
        cout << "Fitness " << i << ": " << fitness << endl;
        myPop.print_parents();
    }

    return 0;
}

