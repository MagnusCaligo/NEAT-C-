#ifndef GENETICS_H
#define GENETICS_H
#include <iostream>
#include <vector>
#include "network.h"
#include <algorithm>

using namespace std;

typedef struct Gene{
    int sourceNeuronID;
    int destinationNeuronID;
    float weightValue;
    int innovationNumber;
    bool enabled;
    vector<int>* inputNeuronIDs;
    vector<int>* outputNeuronIDs;

} Gene;

vector<Gene*> convertNetworkToGenes(Network *net);
vector<Gene*> walkThroughTree(Neuron * ner); 
Network * convertGenesToNetwork(vector<Gene *> genes);

#endif
