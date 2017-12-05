#include "genetics.h"

using namespace std;


vector<Gene*> convertNetworkToGenes(Network *net){
    vector<Gene *> outputGenes; 
    for(Neuron *outputNeuron : net->outputNeurons){
        vector<Gene *> genes = walkThroughTree(outputNeuron);
        outputGenes.insert(outputGenes.end(), genes.begin(), genes.end());
    }
    for(Gene * gene : outputGenes){
        for(Neuron *ner : net->inputNeurons){
            gene->inputNeuronIDs->push_back(ner->ID);
        }
        for(Neuron *ner : net->outputNeurons){
            gene->outputNeuronIDs->push_back(ner->ID);
        }
    }

    return outputGenes;
}

vector<Gene *> walkThroughTree(Neuron* destinationNeuron){
    vector<Gene*> outputGenes;
    if(destinationNeuron->alreadyConverted == true){
        return outputGenes;
    }
    for(AxonNeuronPair * lowerPair : destinationNeuron->inputs){
        vector<Gene *> out = walkThroughTree(lowerPair->neuron);
        outputGenes.insert(outputGenes.end(), out.begin(), out.end());

        Gene * gene = (Gene *) malloc(1 * sizeof(Gene));
        gene->sourceNeuronID = lowerPair->neuron->ID;
        gene->destinationNeuronID = destinationNeuron->ID;
        gene->weightValue = lowerPair->weight;
        gene->enabled = lowerPair->enabled;
        gene->innovationNumber = lowerPair->innovationNumber;
        outputGenes.push_back(gene);
    }
    destinationNeuron->alreadyConverted = true;
}


Network * convertGenesToNetwork(vector<Gene*> genes){
    Network *network = (Network *) malloc(1 * sizeof(Network));
    vector<Neuron *>* allNeurons = &(network->allNeurons); 
    for(Gene* gene : genes){
        int sourceID = gene->sourceNeuronID;
        int destID = gene->destinationNeuronID;

        Neuron *sourceNeuron = NULL;
        Neuron *destNeuron = NULL;

        for(Neuron * ner : *(allNeurons)){
            if(ner->ID == sourceID)
                sourceNeuron = ner;
            else if(ner->ID == destID)
                destNeuron = ner;
        }

        if(sourceNeuron == NULL){
            sourceNeuron = new Neuron(sourceID);
            allNeurons->push_back(sourceNeuron);
            if(find(gene->inputNeuronIDs->begin(), gene->inputNeuronIDs->end(), sourceID) != gene->inputNeuronIDs->end()){
                sourceNeuron->type = 0;
                network->inputNeurons.push_back(sourceNeuron);
            }
        }
        if(destNeuron == NULL){
            destNeuron = new Neuron(destID);
            allNeurons->push_back(destNeuron);
            if(find(gene->outputNeuronIDs->begin(), gene->outputNeuronIDs->end(), destID) != gene->outputNeuronIDs->end()){
                destNeuron->type = 1;
                network->outputNeurons.push_back(destNeuron);
            }
        }
        AxonNeuronPair* pair = new AxonNeuronPair();
        pair->neuron = sourceNeuron; 
        pair->weight = gene->weightValue;
        pair->enabled = gene->enabled;
        pair->innovationNumber = gene->innovationNumber;
        destNeuron->inputs.push_back(pair);
        network->hiddenLayerNeurons.push_back(pair);
    }
    return network;
}
