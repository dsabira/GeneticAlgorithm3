class genome {
public:
     struct Pixel {//customized structure for storing RGB values of pixel
        int red;
        int blue;
        int green;
    };
    genome();
    ~genome();
    void allocate(int nGenes);
    void deallocate();
    void randomize();
    void set_red(int index, int value);
    int get_red(int index);
    void set_blue(int index, int value);
    int get_blue(int index);
    void set_green(int index, int value);
    int get_green(int index);
    void print();
    void set_mRate(double val);
    double get_mRate();
    void mutate_gene(int index);
    void mutate();
    double calculate_gene_fitness(int index, Pixel targetPixel);
    double calculate_overall_fitness(Pixel* target, int nPixels);
    void set_pixel(int index, Pixel newPixel);
    Pixel get_pixel(int index);
    int get_ngenes();
private:
    Pixel* genes;//pointer for dynamic array of pixel structs 
    int nGenes;//size of array
    double mRate;
};

