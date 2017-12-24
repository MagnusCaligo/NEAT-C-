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
   //newSize = 5;
   sort(idAndFitness.begin(), idAndFitness.end(), [] (const tuple<int, float>& a, const tuple<int,float>&b){
           return get<1>(a) > get<1>(b);
           });
   Network *net = getBestNetwork();
   float fitness = get<1>(idAndFitness.at(0));
   if(haveBestNetwork == false || fitness > bestFitness){
       printf("Got a new best network!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
       bestGenome = convertNetworkToGenes(net);
       bestFitness = fitness;
       haveBestNetwork = true;
   } 
   networks.at(newSize - 2) = convertGenesToNetwork(networks.at(newSize-2)->ID, bestGenome); 
   for(int i = 0; i < idAndFitness.size(); i++){
       if(get<0>(idAndFitness.at(i)) == networks.at(newSize-2)->ID){
           get<1>(idAndFitness.at(i)) = bestFitness;
           break;
       }
   }
   printf("Network with hightest fitness %d, value was %f\n", net->ID, fitness);

   while(newNetworks.size() < numOfOrganisms){ 
       int value1 = ((double) rand() /RAND_MAX) * newSize;
       int value2 = ((double) rand() /RAND_MAX) * newSize;
       Network* parent1 = networks.at(value1);
       Network* parent2 = networks.at(value2);
       //printf("Breeding: Parents have structure (%d, %d) and (%d, %d)\n", parent1->allNeurons.size(), parent1->hiddenLayerNeurons.size(), parent2->allNeurons.size(), parent2->hiddenLayerNeurons.size());
       float fitness1 = 0;
       float fitness2 = 0;
       for(int i = 0; i < idAndFitness.size(); i++){
           if(get<0>(idAndFitness.at(i)) == parent1->ID){
               fitness1= get<1>(idAndFitness.at(i));
           }
           if(get<0>(idAndFitness.at(i)) == parent2->ID){
               fitness2= get<1>(idAndFitness.at(i));
           }
       }
//       //printf("Parent fitness was %f, and %f\n", fitness1, fitness2);
//       for(int i = 0; i < parent1->allNeurons.size(); i++){
//           Neuron* neuron = parent1->allNeurons.at(i);
//           for(int p = 0; p < neuron->inputs.size(); p++){
//               printf("Size %d\n", neuron->inputs.size());
//               printf("Connection from %d to %d on parent %d\n", neuron->ID, neuron->inputs.at(p)->neuron->ID, parent1->ID);
//               int m;
//               if(neuron->ID != 3){
//                   //cin >> m;
//               }
//           }
//       }
//       for(int i = 0; i < parent2->allNeurons.size(); i++){
//           Neuron* neuron = parent2->allNeurons.at(i);
//           for(int p = 0; p < neuron->inputs.size(); p++){
//               printf("Size %d\n", neuron->inputs.size());
//               printf("Connection from %d to %d on parent %d\n", neuron->ID, neuron->inputs.at(p)->neuron->ID, parent2->ID);
//               int m;
//               if(neuron->ID != 3){
//                   //cin >> m;
//               }
//           }
//       }
       int val;
       //cin >> val;
       vector<Gene *> genome1 = convertNetworkToGenes(parent1);
       vector<Gene *> genome2 = convertNetworkToGenes(parent2);

       bool net1HigherFitness = getFitnessOfNetwork(parent1->ID) > getFitnessOfNetwork(parent2->ID);

       vector<Gene *>* childGenome = breedNetworks(&genome1, &genome2, net1HigherFitness);
       Network* net = convertGenesToNetwork(newNetworks.size(), *(childGenome));
       //printf("Child has structure (%d, %d)\n", net->allNeurons.size(), net->hiddenLayerNeurons.size());
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

float NEAT::getFitnessOfNetwork(int id){
    for(int i = 0; i < idAndFitness.size(); i++){
        if(get<0>(idAndFitness.at(i)) == id){
            return get<1>(idAndFitness.at(i));
        }
    }
    return -1;
}
