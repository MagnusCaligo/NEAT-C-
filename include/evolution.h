#ifndef EVOLUTION_H
#define EVOLUTION_U
#include <iostream>
#include <vector>
#include "network.h"
#include "genetics.h"
#include <climits>

using namespace std;

vector<Gene*>* breedNetworks(vector<Gene*>* net1genome, vector<Gene*>* net2genome);
void addMutation(vector<Gene*>* genome);
Gene* getNextLargestInnovation(vector<Gene*>* network, int currentInnovation);
void copyGene(Gene* dest, Gene* src);

#endif
