#include <iostream>
#include "network.h"
#include "genetics.h"
#include "evolution.h"

using namespace std;

void run(){
    vector<Gene*> net1genome;
    vector<Gene*> net2genome;

    vector<int> inputs = {
        1, 2,3
    };
    vector<int> outputs = {
        4
    };

    Gene * gene = new Gene; 
//    gene->sourceNeuronID = 1;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=1;
//    gene->enabled=true;
//    net1genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 2;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=2;
//    gene->enabled=false;
//    net1genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 3;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=3;
//    gene->enabled=true;
//    net1genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 2;
//    gene->destinationNeuronID = 5;
//    gene->weightValue=1;
//    gene->innovationNumber=4;
//    gene->enabled=true;
//    net1genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 5;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=5;
//    gene->enabled=true;
//    net1genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 5;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=5;
//    gene->enabled=true;
//    net1genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 1;
//    gene->destinationNeuronID = 5;
//    gene->weightValue=1;
//    gene->innovationNumber=8;
//    gene->enabled=true;
//    net1genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 1;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=1;
//    gene->enabled=true;
//    net2genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 2;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=2;
//    gene->enabled=false;
//    net2genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 3;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=3;
//    gene->enabled=true;
//    net2genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 2;
//    gene->destinationNeuronID = 5;
//    gene->weightValue=1;
//    gene->innovationNumber=4;
//    gene->enabled=true;
//    net2genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 5;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=5;
//    gene->enabled=false;
//    net2genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 5;
//    gene->destinationNeuronID = 6;
//    gene->weightValue=1;
//    gene->innovationNumber=6;
//    gene->enabled=true;
//    net2genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 6;
//    gene->destinationNeuronID = 4;
//    gene->weightValue=1;
//    gene->innovationNumber=7;
//    gene->enabled=true;
//    net2genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 3;
//    gene->destinationNeuronID = 5;
//    gene->weightValue=1;
//    gene->innovationNumber=9;
//    gene->enabled=true;
//    net2genome.push_back(gene);
//
//    gene = new Gene; 
//    gene->sourceNeuronID = 1;
//    gene->destinationNeuronID = 6;
//    gene->weightValue=1;
//    gene->innovationNumber=10;
//    gene->enabled=true;
//    net2genome.push_back(gene);
    
    gene = new Gene; 
    gene->sourceNeuronID = 1;
    gene->destinationNeuronID = -1;
    gene->weightValue=1;
    gene->innovationNumber=-1;
    gene->enabled=true;
    gene->type = GENE_TYPE_INPUT;
    net1genome.push_back(gene);
    
    gene = new Gene; 
    gene->sourceNeuronID = 2;
    gene->destinationNeuronID = -1;
    gene->weightValue=1;
    gene->innovationNumber=-1;
    gene->enabled=true;
    gene->type = GENE_TYPE_INPUT;
    net1genome.push_back(gene);
    
    gene = new Gene; 
    gene->sourceNeuronID = 3;
    gene->destinationNeuronID = -1;
    gene->weightValue=1;
    gene->innovationNumber=-1;
    gene->enabled=true;
    gene->type = GENE_TYPE_INPUT;
    net1genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 4;
    gene->destinationNeuronID = -1;
    gene->weightValue=1;
    gene->innovationNumber=-1;
    gene->enabled=true;
    gene->type = GENE_TYPE_OUTPUT;
    net1genome.push_back(gene);
    
    gene = new Gene; 
    gene->sourceNeuronID = 1;
    gene->destinationNeuronID = -1;
    gene->weightValue=1;
    gene->innovationNumber=-1;
    gene->enabled=true;
    gene->type = GENE_TYPE_INPUT;
    net2genome.push_back(gene);
    
    gene = new Gene; 
    gene->sourceNeuronID = 2;
    gene->destinationNeuronID = -1;
    gene->weightValue=1;
    gene->innovationNumber=-1;
    gene->enabled=true;
    gene->type = GENE_TYPE_INPUT;
    net2genome.push_back(gene);
    
    gene = new Gene; 
    gene->sourceNeuronID = 3;
    gene->destinationNeuronID = -1;
    gene->weightValue=1;
    gene->innovationNumber=-1;
    gene->enabled=true;
    gene->type = GENE_TYPE_INPUT;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 4;
    gene->destinationNeuronID = -1;
    gene->weightValue=1;
    gene->innovationNumber=-1;
    gene->enabled=true;
    gene->type = GENE_TYPE_OUTPUT;
    net2genome.push_back(gene);

    int p = 5;

    vector<Gene*>* result = breedNetworks(&net1genome, &net2genome); 

    Network* net = convertGenesToNetwork(1, *(result));
    vector<Gene*> netToGenes = convertNetworkToGenes(net);


    vector<float> in = {
        1, 2,3
    };

    net->inputs = in;
    net->update();
    vector<float> out = net->outputs;

    for(int i = 0; i < out.size(); i++){
        printf("%f\n", out.at(i));
    }

    for(int i = 0; i < result->size(); i++){
        Gene * gene = result->at(i);
        printf("Inno: %d, From %d, To %d, weight %f, enabled %d\n", gene->innovationNumber, gene->sourceNeuronID, gene->destinationNeuronID, gene->weightValue, gene->enabled);
    }
}
