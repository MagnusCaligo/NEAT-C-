#include "genetics.h"

using namespace std;


vector<Gene*> convertNetworkToGenes(Network *net){
    vector<Gene *> outputGenes; 
    for(Neuron *outputNeuron : net->outputNeurons){
        vector<Gene *> genes = walkThroughTree(outputNeuron);
        outputGenes.insert(outputGenes.end(), genes.begin(), genes.end());
    }
    for(Neuron *ner : net->inputNeurons){
        Gene* gene = new Gene;
        gene->sourceNeuronID = ner->ID;
        gene->destinationNeuronID = -1;
        gene->weightValue = 1;
        gene->enabled = true;
        gene->innovationNumber = -1;
        gene->type = GENE_TYPE_INPUT;
        outputGenes.push_back(gene);
    }

    for(Neuron *ner : net->outputNeurons){
        Gene* gene = new Gene;
        gene->sourceNeuronID = ner->ID;
        gene->destinationNeuronID = -1;
        gene->weightValue = 1;
        gene->enabled = true;
        gene->innovationNumber = -1;
        gene->type = GENE_TYPE_INPUT;
        outputGenes.push_back(gene);
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

        Gene * gene = new Gene; 
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
    Network *network = new Network(1); 
    vector<Neuron *>* allNeurons = &(network->allNeurons); 
    for(Gene* gene : genes){
        if(gene->type == GENE_TYPE_NORMAL){
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
        }else if(gene->type == GENE_TYPE_INPUT){
           bool alreadyExists = false;
           Neuron *neuron;
           for(Neuron *ner : *(allNeurons)){
               if(ner->ID == gene->sourceNeuronID){
                   alreadyExists = true;
                   neuron = ner;
                   break;
               }
           } 
           if(alreadyExists == false){
               Neuron *neuron = new Neuron(gene->sourceNeuronID);
               allNeurons->push_back(neuron);
           }
           network->outputNeurons.push_back(neuron);

        }else if(gene->type == GENE_TYPE_OUTPUT){
           bool alreadyExists = false;
           Neuron *neuron;
           for(Neuron *ner : *(allNeurons)){
               if(ner->ID == gene->sourceNeuronID){
                   alreadyExists = true;
                   neuron = ner;
                   break;
               }
           } 
           if(alreadyExists == false){
               Neuron *neuron = new Neuron(gene->sourceNeuronID);
               allNeurons->push_back(neuron);
           }
           network->outputNeurons.push_back(neuron);
        }
    }
    return network;
}
