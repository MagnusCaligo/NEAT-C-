#ifndef NEAT_H
#define NEAT_H

#include <iostream>
#include "genetics.h"
#include <stdlib.h>
#include <time.h>

#define STRUCTURAL_MUTATION_CHANCE 0.1
#define ADD_CONNECTION_MUTATION_CHANCE 0.5
#define MAX_MUTATION_ATTEMPTS 10000

#define GENE_TYPE_NORMAL 0
#define GENE_TYPE_INPUT 1
#define GENE_TYPE_OUTPUT 2

using namespace std;

static int innovationNumber;
void initNeat();
int getNextInnovation();


#endif
