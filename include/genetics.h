#ifndef GENETICS_H
#define GENETICS_H
#include <iostream>
#include <vector>
#include "network.h"
#include <algorithm>

#define GENE_TYPE_NORMAL 0
#define GENE_TYPE_INPUT 1
#define GENE_TYPE_OUTPUT 2

using namespace std;

typedef struct Gene{
    int sourceNeuronID;
    int destinationNeuronID;
    float weightValue;
    int innovationNumber;
    bool enabled;
    int type = GENE_TYPE_NORMAL;
    Gene();
    Gene(int type, int sourceNeuron);

} Gene;

vector<Gene*> convertNetworkToGenes(Network *net);
vector<Gene*> walkThroughTree(Neuron * ner, vector<int>& currentlyCalculating); 
Network * convertGenesToNetwork(int networkID, vector<Gene *> genes);

#endif
