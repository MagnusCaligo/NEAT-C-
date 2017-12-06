#ifndef NEAT_H
#define NEAT_H

#include <iostream>
#include "genetics.h"
#include "network.h"
#include "evolution.h"
#include <stdlib.h>
#include <time.h>

#define STRUCTURAL_MUTATION_CHANCE 0.1
#define ADD_CONNECTION_MUTATION_CHANCE 0.5
#define MAX_MUTATION_ATTEMPTS 10000

using namespace std;


void initNeat();


#endif
