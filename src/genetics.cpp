#include "genetics.h"

using namespace std;

Gene::Gene(int geneType, int sourceNeuron){
    if(geneType == GENE_TYPE_NORMAL){
        throw "Gene constructor is only used for input and output neurons";
    }
    sourceNeuronID = sourceNeuron;
    destinationNeuronID = -1;
    innovationNumber = -1;
    enabled = 1;
    weightValue = 1;
    type = geneType;
    
}

Gene::Gene(){
    
}



vector<Gene*> convertNetworkToGenes(Network *net){
    vector<Gene *> outputGenes; 
    vector<int> currentlyCalculating;
    for(AxonNeuronPair* pair : net->hiddenLayerNeurons){
//        printf("making new pair, source ID %d, destination ID %d\n", pair->neuron->ID, pair->destNeuron->ID);
//        printf("Before Converting %d, %d\n", pair->neuron->ID, pair->destNeuron->ID);
        Gene *gene = new Gene;
        gene->sourceNeuronID = pair->neuron->ID;
        gene->destinationNeuronID = pair->destNeuron->ID;
        gene->innovationNumber = pair->innovationNumber;
        gene->enabled = pair->enabled;
        gene->weightValue = pair->weight;
        outputGenes.push_back(gene);
    }
//    for(Neuron *outputNeuron : net->outputNeurons){
//        vector<Gene *> genes = walkThroughTree(outputNeuron, currentlyCalculating);
//        outputGenes.insert(outputGenes.end(), genes.begin(), genes.end());
//    }
    for(Neuron *ner : net->inputNeurons){
        Gene* gene = new Gene();
        gene->sourceNeuronID = ner->ID;
        gene->destinationNeuronID = -1;
        gene->weightValue = 1;
        gene->enabled = true;
        gene->innovationNumber = -1;
        gene->type = GENE_TYPE_INPUT;
        outputGenes.push_back(gene);
    }

    for(Neuron *ner : net->outputNeurons){
        Gene* gene = new Gene();
        gene->sourceNeuronID = ner->ID;
        gene->destinationNeuronID = -1;
        gene->weightValue = 1;
        gene->enabled = true;
        gene->innovationNumber = -1;
        gene->type = GENE_TYPE_OUTPUT;
        outputGenes.push_back(gene);
    }
    return outputGenes;
}

vector<Gene *> walkThroughTree(Neuron* destinationNeuron, vector<int>& currentlyCalculating){
    vector<Gene*> outputGenes;
    if(destinationNeuron->alreadyConverted == true){
        return outputGenes;
    }
    if(find(currentlyCalculating.begin(), currentlyCalculating.end(), destinationNeuron->ID) != currentlyCalculating.end()){
        return outputGenes;
    }
    currentlyCalculating.push_back(destinationNeuron->ID);
    for(AxonNeuronPair * lowerPair : destinationNeuron->inputs){
        vector<Gene *> out = walkThroughTree(lowerPair->neuron, currentlyCalculating);
        outputGenes.insert(outputGenes.end(), out.begin(), out.end());

        Gene * gene = new Gene(); 
        gene->sourceNeuronID = lowerPair->neuron->ID;
        gene->destinationNeuronID = destinationNeuron->ID;
        gene->weightValue = lowerPair->weight;
        gene->enabled = lowerPair->enabled;
        gene->innovationNumber = lowerPair->innovationNumber;
        outputGenes.push_back(gene);
    }
    destinationNeuron->alreadyConverted = true;
    currentlyCalculating.erase(remove(currentlyCalculating.begin(), currentlyCalculating.end(), destinationNeuron->ID), currentlyCalculating.end());
    return outputGenes;
}


Network * convertGenesToNetwork(int networkID, vector<Gene*> genes){
    Network *network = new Network(networkID); 
    vector<Neuron *>* allNeurons = &(network->allNeurons); 
    for(Gene* gene : genes){
        if(gene->type == GENE_TYPE_NORMAL){
            int sourceID = gene->sourceNeuronID;
            int destID = gene->destinationNeuronID;

            //printf("Converting: %d, %d\n", sourceID, destID);

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
            }
            if(destNeuron == NULL){
                destNeuron = new Neuron(destID);
                allNeurons->push_back(destNeuron);
            }
            AxonNeuronPair* pair = new AxonNeuronPair();
            pair->neuron = sourceNeuron; 
            pair->weight = gene->weightValue;
            pair->enabled = gene->enabled;
            pair->innovationNumber = gene->innovationNumber;
            destNeuron->inputs.push_back(pair);
            pair->destNeuron = destNeuron;
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
               neuron = new Neuron(gene->sourceNeuronID);
               allNeurons->push_back(neuron);
           }
           neuron->type = 0;
           network->inputNeurons.push_back(neuron);

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
               neuron = new Neuron(gene->sourceNeuronID);
               allNeurons->push_back(neuron);
           }
           neuron->type = 2;
           network->outputNeurons.push_back(neuron);
        }
    }
    return network;
}
