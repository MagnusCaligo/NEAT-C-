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
   //newSize = 3;
   sort(idAndFitness.begin(), idAndFitness.end(), [] (const tuple<int, float>& a, const tuple<int,float>&b){
           return get<1>(a) > get<1>(b);
           });
 // for(int i = 0; i < idAndFitness.size(); i++){
 //      printf("Organism %d, fitness %f\n", get<0>(idAndFitness.at(i)),get<1>(idAndFitness.at(i)));
 //  }
   Network net = *(networks.at(0));
   float fitness = 0;
   for(int i = 0; i < idAndFitness.size(); i++){
       if(get<0>(idAndFitness.at(i)) == net.ID){
           fitness = get<1>(idAndFitness.at(i));
           break;
       }
   }
   printf("Network with hightest fitness %d, value was %f\n", net.ID, fitness);
   while(newNetworks.size() < numOfOrganisms){ 
       int value1 = ((double) rand() /RAND_MAX) * newSize;
       int value2 = ((double) rand() /RAND_MAX) * newSize;
       Network* parent1 = networks.at(value1);
       Network* parent2 = networks.at(value2);
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
       for(int i = 0; i < genome1.size(); i++){
           Gene* gene = genome1.at(i);
           //printf("Parent 1: Innovations %d, from %d, to %d\n", gene->innovationNumber, gene->sourceNeuronID, gene->destinationNeuronID);
       }
       for(int i = 0; i < genome2.size(); i++){
           Gene* gene = genome2.at(i);
           //printf("Parent 2: Innovations %d, from %d, to %d\n", gene->innovationNumber, gene->sourceNeuronID, gene->destinationNeuronID);
       }
       vector<Gene *>* childGenome = breedNetworks(&genome1, &genome2);
       Network* net = convertGenesToNetwork(newNetworks.size(), *(childGenome));
       free(childGenome);
       if(fitness1 > -3 || fitness2 > -3){
           //printf("Child has %d nodes, %d connections\n", net->allNeurons.size(), net->hiddenLayerNeurons.size());
            int val;
            //cin >> val;
       }

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
