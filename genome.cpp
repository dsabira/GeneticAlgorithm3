#include "genome.h"

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

genome::genome() {//constructor that sets to default values
    genes = NULL;
    nGenes = 0;
    mRate = 0;
}

genome::~genome() {//desctructor calls deallocate() when object is deleted
    deallocate();
}

void genome::allocate(int nGenes) {//creates array of pixels with the size of nGenes
    if (genes != NULL) {//if genes are not NULL, need to deallocate
        deallocate();
    }
    genes = new Pixel[nGenes];//creating array of pixels with default values of pixel colors as 0s
    this->nGenes = nGenes; //saving the new size of the array
}

void genome::deallocate() {//defaulting back genes and nGenes
    delete[] genes;
    genes = NULL;
    nGenes = 0;
}

void genome::randomize() {//randomizing RGB values for pixel array
    std::srand(std::time(nullptr));
    for (int i=0;i<nGenes;i++) {
        genes[i].red = rand() % 256; //so that we always have values between 0-256
        genes[i].blue = rand() % 256;
        genes[i].green = rand() % 256;

    }
}

void genome::set_red(int index, int value) {//setters for RGB values of pixel from array
    genes[index].red = value;
}

void genome::set_blue(int index, int value) {
    genes[index].blue = value;
}

void genome::set_green(int index, int value) {
    genes[index].green = value;
}

int genome::get_red(int index) {//gets RGB values of pixel from array
    return genes[index].red;
}

int genome::get_blue(int index) {
    return genes[index].blue;
}

int genome::get_green(int index) {
    return genes[index].green;
}

void genome::print() {//prints pixels in a readable format
    for (int i = 0;i<nGenes;i++) {
        cout << genes[i].red << ", " << genes[i].green << ", " << genes[i].blue << endl;
    }
}    

void genome::set_mRate(double val) {
    if (val > 0 && val < 1) { // value should be betwwen 0 and 1
        this->mRate = val;
    }
}

double genome::get_mRate() {
    return this->mRate;
}

void genome::mutate_gene(int index) {
    std:srand(std::time(nullptr));
    double gen_red = (double) rand() / RAND_MAX; // random value between 0 and 1
    if (gen_red < this->mRate) { // mutate red with mRate % possbility
        genes[index].red = rand() % 256;
    }
    double gen_blue = (double) rand() / RAND_MAX;
    if (gen_blue < this->mRate) { // mutate blue with mRate % possibility
        genes[index].blue = rand() % 256;
    }
    double gen_green = (double) rand() / RAND_MAX;
    if (gen_green < this->mRate) { // mutate green with mrate % possibility
        genes[index].green = rand() % 256;
    }
}

void genome::mutate() {
    for (int i=0;i<nGenes;i++) { // call mutate function for all genes
        mutate_gene(i);
    }
}

double genome::calculate_gene_fitness(int index, Pixel targetPixel) {

    // calculate difference percentage for each color
    double diff_red = (double) abs(genes[index].red - targetPixel.red) / 255;
    double diff_green = (double) abs(genes[index].green - targetPixel.green) / 255;
    double diff_blue = (double) abs(genes[index].blue - targetPixel.blue) / 255;

    return (diff_red + diff_green + diff_blue) / 3; // take average
}

double genome::calculate_overall_fitness(Pixel* target, int nPixels) {
    if (nPixels == nGenes) { // check if nPixels is the same as nGenes
        double sumErrors = 0.0;
        for (int i = 0;i<nPixels;i++) { // check fitness for each gene
            double error = calculate_gene_fitness(i,target[i]);
            sumErrors = sumErrors + error;
        }
        return sumErrors / nPixels; // take average
    } else {
        return -1.0;
    }
}

void genome::set_pixel(int index, Pixel newPixel) {
    if (index >= 0 && index < nGenes) { // validate that index is within bounds
        if (newPixel.red >= 0 && newPixel.red <= 255 && newPixel.green >= 0 && newPixel.green <= 255 && newPixel.blue >= 0 && newPixel.blue <= 255) { // validate that each color is between 0 and 255
            genes[index] = newPixel;
        }
    }
}

genome::Pixel genome::get_pixel(int index) {
    return genes[index];
}

int genome::get_ngenes() {
    return this->nGenes;
}

