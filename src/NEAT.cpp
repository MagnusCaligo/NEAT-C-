#include "NEAT.h"

using namespace std;

void initNeat(){
    srand(time(NULL));
}

int getNextInnovation(){
    innovationNumber++;
    return innovationNumber-1;
}
