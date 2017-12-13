#include "evolution.h"
#include <cstring>
#include "NEAT.h"

using namespace std;

vector<Gene *>* breedNetworks(vector<Gene*>* net1, vector<Gene*>* net2, bool net1HigherFitness){
    vector<Gene*>* outputNet = new vector<Gene*>();


    Gene* net1Gene = getNextLargestInnovation(net1, -1);
    Gene* net2Gene = getNextLargestInnovation(net2, -1);

    for(Gene * gene : *(net1)){
        if(gene->innovationNumber == -1){
            Gene* outputGene = new Gene;
            copyGene(outputGene, gene);
            outputNet->push_back(outputGene);
        }
    }

    Gene* output;
    while(net1Gene != NULL && net2Gene != NULL){
        int net1Innovation = net1Gene->innovationNumber;
        int net2Innovation = net2Gene->innovationNumber;
        output = new Gene;

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
            if(!net1HigherFitness){
                outputNet->push_back(output);
            }
            net2Gene = getNextLargestInnovation(net2, net2Gene->innovationNumber);
            if(net1Gene == NULL || net2Gene == NULL){
                break;
            }
            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;
        }
        else if(net1Innovation < net2Innovation){
            copyGene(output, net1Gene);
            if(net1HigherFitness){
                outputNet->push_back(output);
            }
            net1Gene = getNextLargestInnovation(net1, net1Gene->innovationNumber);
            if(net1Gene == NULL || net2Gene == NULL){
                break;
            }
            net1Innovation = net1Gene->innovationNumber;
            net2Innovation = net2Gene->innovationNumber;
        }
    }
    vector<Gene*>* largerGenePool;
    Gene* largerGenePoolGene = NULL;
    int innovation;
    if(net1HigherFitness){
        //printf("Getting extra gene from parent1\n");
        largerGenePool = net1;
        largerGenePoolGene = net1Gene;
        if(net1Gene != NULL)
            innovation = net1Gene->innovationNumber;
    }else if(!net1HigherFitness){
        //printf("Getting extra gene from parent2\n");
        largerGenePool = net2;
        largerGenePoolGene = net2Gene;
        if(net2Gene != NULL)
            innovation = net2Gene->innovationNumber;
    }else{
        //printf("No extra genes to get\n");
    }
    while(largerGenePoolGene != NULL){
        Gene * output = new Gene;
        copyGene(output, largerGenePoolGene);
        //memcpy(output, largerGenePoolGene, sizeof(largerGenePoolGene));
        outputNet->push_back(output);
        innovation = largerGenePoolGene->innovationNumber;
        largerGenePoolGene = getNextLargestInnovation(largerGenePool, innovation);
    }
    for(int i = 0; i < 5; i++){
        addMutations(*(outputNet));
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

void addMutations(vector<Gene*> &genome){
    default_random_engine generator;
    normal_distribution<double> distribution(0, .15);
    for(int i = 0; i < genome.size(); i++){
       double multiplyer = distribution(generator);
       float val = (double) rand() / RAND_MAX;
       if(val <= WEIGHT_CHANGE_MUTATION_CHANCE){
           genome.at(i)->weightValue += multiplyer;
       } 
    }
    if(((double) rand() / RAND_MAX) <= STRUCTURAL_MUTATION_CHANCE){
        vector<int> nodeIDs;
        for(int i = 0; i < genome.size(); i++){
            int src = genome.at(i)->sourceNeuronID;
            int dst = genome.at(i)->destinationNeuronID;
            //printf("Network contains nodes %d, %d\n", src, dst);
            if(find(nodeIDs.begin(), nodeIDs.end(), src) == nodeIDs.end()){
                nodeIDs.push_back(src);
            } 
            if(find(nodeIDs.begin(), nodeIDs.end(), dst) == nodeIDs.end()){
                nodeIDs.push_back(dst);
            } 

        }
        int attempts = 0;
        float randomValue = (double) rand() / RAND_MAX;
        //printf("Value is %f\n", randomValue);
        if(randomValue <= ADD_CONNECTION_MUTATION_CHANCE){
            //printf("Connection mutation\n");
            Gene* gene = new Gene;
            int sourceNode;
            int destinationNode;
            while(attempts < MAX_MUTATION_ATTEMPTS){
                attempts++;
                sourceNode = (nodeIDs.at(((double) rand() / (RAND_MAX)) * nodeIDs.size()));
                destinationNode = (nodeIDs.at(((double) rand() / (RAND_MAX)) * nodeIDs.size()));
                if(sourceNode == destinationNode || sourceNode == -1 || destinationNode == -1)
                    continue;
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
            if(attempts == MAX_MUTATION_ATTEMPTS){
        //        printf("Failed to mutate, ran out of attempts, Add_Connection\n");
                return;
            }
            gene->sourceNeuronID = sourceNode;
            gene->destinationNeuronID = destinationNode;
            gene->weightValue = 1;
            gene->enabled = true;
            gene->innovationNumber = getNextInnovation();
            genome.push_back(gene);
        }else{
            //printf("Node mutation\n");
            Gene* geneToModify;
            Gene* newGene = new Gene;
            while(attempts < MAX_MUTATION_ATTEMPTS){
                attempts++;
                geneToModify = genome.at(genome.size() * (double) rand() / RAND_MAX);
                if(geneToModify->type == GENE_TYPE_NORMAL){
                    break; 
                }
            }
            if(attempts == MAX_MUTATION_ATTEMPTS){
         //       printf("Failed to mutate, ran out of attempts, Add_Node\n");
                return;
            }
            int nextNode = 0;
            for(int i = 0; i < nodeIDs.size();i++){
                if(nodeIDs.at(i) >= nextNode){
                    nextNode = nodeIDs.at(i);
                }
            }
            nextNode++;

            newGene->sourceNeuronID = nextNode;
            newGene->destinationNeuronID = geneToModify->destinationNeuronID;
            double multiplyer = distribution(generator);
            newGene->weightValue *= multiplyer;
            newGene->enabled = true;
            newGene->innovationNumber = getNextInnovation();
            genome.push_back(newGene);

            newGene = new Gene;
            newGene->sourceNeuronID = geneToModify->sourceNeuronID;
            newGene->destinationNeuronID = nextNode;
            //printf("Mutation: Nodes are %d, %d, %d\n", nextNode, geneToModify->sourceNeuronID, geneToModify->destinationNeuronID);
//            for(int i = 0; i < genome.size(); i++){
//                Gene* gene = genome.at(i);
//                printf("Gene inno %d, from %d, to %d\n", gene->innovationNumber, gene->sourceNeuronID, gene->destinationNeuronID);
//            }
            int i;
//            cin >> i;
            newGene->weightValue = geneToModify->weightValue;
            newGene->innovationNumber = getNextInnovation();
            newGene->enabled = true;
            genome.push_back(newGene);

            geneToModify->enabled = false;
        }
    }
}


void copyGene(Gene * dest, Gene* src){
    dest->sourceNeuronID = src->sourceNeuronID;
    dest->destinationNeuronID = src->destinationNeuronID;
    dest->weightValue = src->weightValue;
    dest->innovationNumber = src->innovationNumber;
    dest->enabled = src->enabled;
    dest->type = src->type;
}
