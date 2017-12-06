#include "evolution.h"
#include <cstring>

using namespace std;

vector<Gene *>* breedNetworks(vector<Gene*>* net1, vector<Gene*>* net2){
    vector<Gene*>* outputNet = new vector<Gene*>();


    Gene* net1Gene = getNextLargestInnovation(net1, 0);
    Gene* net2Gene = getNextLargestInnovation(net2, 0);

    bool genesInNet1 = (net1Gene->innovationNumber > 0);
    bool genesInNet2 = (net2Gene->innovationNumber > 0);

    int net1Innovation = net1Gene->innovationNumber;
    int net2Innovation = net2Gene->innovationNumber;



    Gene* output;
    for(;;){
        output = new Gene;
        //output = (Gene *) malloc(1 * sizeof(Gene));
        if(net1Innovation == net2Innovation){
            double val = (double) rand() / (RAND_MAX);
            if(val > .5){
                copyGene(output, net1Gene);
            }else{
                copyGene(output, net2Gene);
            }

            outputNet->push_back(output);

            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;

            net1Gene = getNextLargestInnovation(net1, net1Gene->innovationNumber);
            net2Gene = getNextLargestInnovation(net2, net2Gene->innovationNumber);

            


            if(net1Gene == NULL || net2Gene == NULL){
                break;
            }
            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;

        }
        else if(net1Innovation > net2Innovation){
            copyGene(output, net2Gene);
            //memcpy(output, net2Gene, sizeof(net2Gene));
            outputNet->push_back(output);
            net2Gene = getNextLargestInnovation(net2, net2Gene->innovationNumber);
            if(net1Gene == NULL || net2Gene == NULL){
                break;
            }
            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;
        }
        else if(net1Innovation < net2Innovation){
            copyGene(output, net1Gene);
            outputNet->push_back(output);
            net1Gene = getNextLargestInnovation(net1, net1Gene->innovationNumber);
            if(net1Gene == NULL || net2Gene == NULL){
                break;
            }
            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;
        }



    }
    vector<Gene*>* largerGenePool = new vector<Gene*>();
    Gene* largerGenePoolGene;
    int innovation;
    if(net1->size() >= net2->size()){
        largerGenePool = net1;
        largerGenePoolGene = net1Gene;
        innovation = net1Gene->innovationNumber;
    }else{
        largerGenePool = net2;
        largerGenePoolGene = net2Gene;
        innovation = net2Gene->innovationNumber;
    }
    
    while(largerGenePoolGene != NULL){
        Gene * output = new Gene;
        copyGene(output, largerGenePoolGene);
        //memcpy(output, largerGenePoolGene, sizeof(largerGenePoolGene));
        outputNet->push_back(output);
        innovation = largerGenePoolGene->innovationNumber;
        largerGenePoolGene = getNextLargestInnovation(largerGenePool, innovation);
    }

    addMutations(*(outputNet));
    return outputNet;
}

Gene* getNextLargestInnovation(vector<Gene*>* net, int currentInnovation){
    Gene* currentGene = NULL;
    int innovation = INT_MAX;
    for(int i = 0; i < net->size(); i++){
        if(net->at(i)->innovationNumber > currentInnovation && 
                    net->at(i)->innovationNumber < innovation){
            currentGene = net->at(i);
            innovation = currentGene->innovationNumber;
        }
    }
    return currentGene;
}

void addMutations(vector<Gene*> &genome){
    default_random_engine generator;
    normal_distribution<double> distribution(1.0, .15);
    for(int i = 0; i < genome.size(); i++){
       double multiplyer = distribution(generator);
       genome.at(i)->weightValue *= multiplyer;
    }
    if(((double) rand() / RAND_MAX) <= STRUCTURAL_MUTATION_CHANCE || true){
        vector<int> nodeIDs;
        for(int i = 0; i < genome.size(); i++){
            int src = genome.at(i)->sourceNeuronID;
            int dst = genome.at(i)->destinationNeuronID;
            if(find(nodeIDs.begin(), nodeIDs.end(), src) == nodeIDs.end()){
                nodeIDs.push_back(src);
            } 
            if(find(nodeIDs.begin(), nodeIDs.end(), dst) == nodeIDs.end()){
                nodeIDs.push_back(dst);
            } 

        }
        int sourceNode;
        int destinationNode;
        int attempts = 0;
        while(attempts < MAX_MUTATION_ATTEMPTS){
            attempts++;
            sourceNode = (nodeIDs.at(((double) rand() / (RAND_MAX)) * nodeIDs.size()));
            destinationNode = (nodeIDs.at(((double) rand() / (RAND_MAX)) * nodeIDs.size()));
            if(sourceNode == destinationNode)
                continue;
            printf("Source: %d Destion: %d\n", sourceNode, destinationNode);
            bool alreadyContains = false;
            for(int i = 0; i < genome.size(); i++){
                if(genome.at(i)->sourceNeuronID == sourceNode && genome.at(i)->destinationNeuronID == destinationNode){
                    alreadyContains = true;
                    break;
                } 
            }
            if(alreadyContains)
                continue;
            break;
        }
        if(((double) rand() / RAND_MAX) <= ADD_CONNECTION_MUTATION_CHANCE){
            Gene* gene = new Gene;
        }else{
        }
    }
}


void copyGene(Gene * dest, Gene* src){
    dest->sourceNeuronID = src->sourceNeuronID;
    dest->destinationNeuronID = src->destinationNeuronID;
    dest->weightValue = src->weightValue;
    dest->innovationNumber = src->innovationNumber;
    dest->inputNeuronIDs = src->inputNeuronIDs;
    dest->outputNeuronIDs = src->outputNeuronIDs;
    dest->enabled = src->enabled;
}
