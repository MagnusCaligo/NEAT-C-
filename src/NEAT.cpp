#include "NEAT.h"

using namespace std;

void initNeat(){
    srand(time(NULL));
}

int getNextInnovation(){
    innovationNumber++;
    return innovationNumber-1;
}


NEAT::NEAT(int in, int out){
    if(in <= 0 || out <= 0){
        throw runtime_error("Number of inputs and outputs must be greater than 0\n");
        exit(-1);
    }
    numOfNetworkInputs = in;
    numOfNetworkOutputs = out;

}

int NEAT::addOrganism(){
    numOfOrganisms++;
    idAndFitness.push_back(make_tuple(numOfOrganisms-1, -1));
    vector<Gene*> genes;
    for(int i = 0; i < numOfNetworkInputs; i++){
        Gene* gene = new Gene(GENE_TYPE_INPUT, i);
        genes.push_back(gene);
    }
    for(int i = 0; i < numOfNetworkOutputs; i++){
        Gene* gene = new Gene(GENE_TYPE_OUTPUT, i + numOfNetworkInputs);
        genes.push_back(gene);
    }


    Network* net = convertGenesToNetwork(numOfOrganisms -1, genes);
    networks.push_back(net);
    return numOfOrganisms -1;

}

vector<float> NEAT::inputOrganismNetworkInputs(int id, vector<float> inputs){
    vector<float> outputValues;
    Network* network = findNetwork(id);
    if(network == NULL){
        throw runtime_error("Could not find network in inputOrganismNetworkInputs");
    }
    if(inputs.size() != numOfNetworkInputs){
        throw runtime_error("Inputs count mismatch");
    }
    network->inputs = inputs;
    network->update();
    return network->outputs;
}

Network* NEAT::findNetwork(int id){
    for(int i = 0; i < networks.size(); i++){
        if(networks.at(i)->ID == id){
            return networks.at(i);
        }
    }
    return NULL;
}

void NEAT::inputOrganismFitness(int id, float fit){
    for(int i = 0; i < idAndFitness.size(); i++){
        if(get<0>(idAndFitness.at(i)) == id){
            get<1>(idAndFitness.at(i)) = fit;
            return;
        }
    }
}

void NEAT::nextEpoch(){
   vector<Network*> newNetworks;
   int newSize = numOfOrganisms/2;
   sort(idAndFitness.begin(), idAndFitness.end(), [] (const tuple<int, float>& a, const tuple<int,float>&b){
           return get<1>(a) > get<1>(b);
           });
//   for(int i = 0; i < idAndFitness.size(); i++){
//       printf("Organism %d, fitness %f\n", get<0>(idAndFitness.at(i)),get<1>(idAndFitness.at(i)));
//   }
   Network net = *(networks.at(0));
   printf("Net size %d, net connections %d\n", net.allNeurons.size(), net.hiddenLayerNeurons.size());
   usleep(150000);
   while(newNetworks.size() < numOfOrganisms){ 
       Network* parent1 = networks.at((double) rand() / RAND_MAX * newSize);
       Network* parent2 = networks.at((double) rand() / RAND_MAX * newSize);
       vector<Gene *> genome1 = convertNetworkToGenes(parent1);
       vector<Gene *> genome2 = convertNetworkToGenes(parent2);
       vector<Gene *>* childGenome = breedNetworks(&genome1, &genome2);
       Network* net = convertGenesToNetwork(newNetworks.size(), *(childGenome));
       free(childGenome);
       newNetworks.push_back(net);
   } 
   for(int i = 0; i < networks.size(); i++){
       free(networks.at(i));
   }
   networks.erase(networks.begin(), networks.end());
   networks = newNetworks;
}

Network* NEAT::getBestNetwork(){
   sort(idAndFitness.begin(), idAndFitness.end(), [] (const tuple<int, float>& a, const tuple<int,float>&b){
           return get<1>(a) > get<1>(b);
           });

   return findNetwork(get<0>(idAndFitness.at(0)));
}
