#ifndef NEAT_H
#define NEAT_H

#include <iostream>
#include "genetics.h"
#include <stdlib.h>
#include <time.h>
#include <tuple>
#include "evolution.h"
#include <unistd.h>

#define WEIGHT_CHANGE_MUTATION_CHANCE 0.9
#define STRUCTURAL_MUTATION_CHANCE 0.01
#define ADD_CONNECTION_MUTATION_CHANCE .5
#define MAX_MUTATION_ATTEMPTS 10000


using namespace std;

static int innovationNumber;
void initNeat();
int getNextInnovation();

class NEAT{
    public:
        int addOrganism();
        vector<float> inputOrganismNetworkInputs(int organismID, vector<float> inputs);
        void inputOrganismFitness(int id, float input);
        void nextEpoch();
        NEAT(int in, int out);
        Network* getBestNetwork();
        float getFitnessOfNetwork(int id);
    

    private:
        int numOfOrganisms= 0;
        int numOfNetworkInputs = -1;
        int numOfNetworkOutputs = -1;
        vector<Network*> networks;
        vector<tuple<int, float>> idAndFitness; 

        Network* findNetwork(int i);


};
#endif
