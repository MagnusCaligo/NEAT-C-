#ifndef EVOLUTION_H
#define EVOLUTION_U
#include <iostream>
#include <vector>
#include "network.h"
#include "genetics.h"
#include "NEAT.h"
#include <climits>
#include <stdlib.h>
#include <random>
#include <time.h>

using namespace std;

vector<Gene*>* breedNetworks(vector<Gene*>* net1genome, vector<Gene*>* net2genome);
void addMutations(vector<Gene*>* genome);
Gene* getNextLargestInnovation(vector<Gene*>* network, int currentInnovation);
void copyGene(Gene* dest, Gene* src);

#endif
