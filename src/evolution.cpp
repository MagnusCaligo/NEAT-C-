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
        output = (Gene*) malloc(1* sizeof(net1Gene));
        if(net1Innovation == net2Innovation){
            copyGene(output, net1Gene);
            output->inputNeuronIDs = new vector<int>();
            output->outputNeuronIDs = new vector<int>();
        for(int i = 0; i < net1->size(); i++){
            printf("Here %d\n", net1->at(i)->sourceNeuronID);
        }

            outputNet->push_back(output);

            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;

            net1Gene = getNextLargestInnovation(net1, net1Gene->innovationNumber);
            net2Gene = getNextLargestInnovation(net2, net2Gene->innovationNumber);

            


            if(net1Gene == NULL || net2Gene == NULL)
                break;
            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;

        }
        if(net1Innovation > net2Innovation){
            copyGene(output, net2Gene);
            //memcpy(output, net2Gene, sizeof(net2Gene));
            outputNet->push_back(output);
            printf("Innovation %d, %d\n", net2Gene->innovationNumber, output->innovationNumber);
            printf("Case 2: From %d to %d\n", net2Gene->sourceNeuronID, net2Gene->destinationNeuronID);
            net2Gene = getNextLargestInnovation(net2, net2Gene->innovationNumber);
            if(net1Gene == NULL || net2Gene == NULL)
                break;
            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;
        }
        if(net1Innovation < net2Innovation){
            copyGene(output, net1Gene);
            //memcpy(output, net1Gene, sizeof(net1Gene));
            outputNet->push_back(output);
            net1Gene = getNextLargestInnovation(net1, net1Gene->innovationNumber);
            if(net1Gene == NULL || net2Gene == NULL)
                break;
            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;
        }


    }
    free(output);
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
        Gene * output = (Gene *) malloc(1 * sizeof(largerGenePoolGene));
        copyGene(output, largerGenePoolGene);
        //memcpy(output, largerGenePoolGene, sizeof(largerGenePoolGene));
        outputNet->push_back(output);
        innovation = largerGenePoolGene->innovationNumber;
        largerGenePoolGene = getNextLargestInnovation(largerGenePool, innovation);
    }

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


void copyGene(Gene * dest, Gene* src){
    dest->sourceNeuronID = src->sourceNeuronID;
    dest->destinationNeuronID = src->destinationNeuronID;
    dest->weightValue = src->weightValue;
    dest->innovationNumber = src->innovationNumber;
    //dest->inputNeuronIDs = new vector<int>();
    //*(dest->inputNeuronIDs) = *(src->inputNeuronIDs);
    //dest->outputNeuronIDs = new vector<int>();
    //*(dest->outputNeuronIDs) = *(src->outputNeuronIDs);
    //memcpy(dest->outputNeuronIDs, src->inputNeuronIDs, sizeof(*(src->inputNeuronIDs)));
    dest->enabled = src->enabled;
}
