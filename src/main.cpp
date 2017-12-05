#include <iostream>
#include "network.h"
#include "genetics.h"
#include "evolution.h"

using namespace std;

int main(){

//    Neuron input1(1);
//    Neuron input2(2);
//    Neuron outputNeuron(3);
//
//    input1.type = 0;
//    input2.type = 0;
//    outputNeuron.type = 1;
//
//    AxonNeuronPair pair1;
//    AxonNeuronPair pair2;
//
//    pair1.weight = 10.0f;
//    pair2.weight = 12.f;
//
//    pair1.setNeuron(&input1);
//    pair2.setNeuron(&input2);
//
//    outputNeuron.inputs.push_back(&pair1);
//    outputNeuron.inputs.push_back(&pair2);
//
//
//    Network net(3);
//
//    net.inputNeurons.push_back(&input1);
//    net.inputNeurons.push_back(&input2);
//    net.outputNeurons.push_back(&outputNeuron);
//
//    net.allNeurons.push_back(&input1);
//    net.allNeurons.push_back(&input2);
//    net.allNeurons.push_back(&outputNeuron);
//
//    net.hiddenLayerNeurons.push_back(&pair1);
//    net.hiddenLayerNeurons.push_back(&pair2);

    vector<Gene*> net1genome;
    vector<Gene*> net2genome;

    vector<int> inputs = {
        1, 2,3
    };
    vector<int> outputs = {
        4
    };

    Gene * gene = new Gene; 
    gene->sourceNeuronID = 1;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=1;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net1genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 2;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=2;
    gene->enabled=false;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net1genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 3;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=3;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net1genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 2;
    gene->destinationNeuronID = 5;
    gene->weightValue=1;
    gene->innovationNumber=4;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net1genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 5;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=5;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net1genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 5;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=5;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net1genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 1;
    gene->destinationNeuronID = 5;
    gene->weightValue=1;
    gene->innovationNumber=8;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net1genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 1;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=1;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 2;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=2;
    gene->enabled=false;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 3;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=3;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 2;
    gene->destinationNeuronID = 5;
    gene->weightValue=1;
    gene->innovationNumber=4;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 5;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=5;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 5;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=5;
    gene->enabled=false;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 5;
    gene->destinationNeuronID = 6;
    gene->weightValue=1;
    gene->innovationNumber=6;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 6;
    gene->destinationNeuronID = 4;
    gene->weightValue=1;
    gene->innovationNumber=7;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 3;
    gene->destinationNeuronID = 5;
    gene->weightValue=1;
    gene->innovationNumber=9;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    gene = new Gene; 
    gene->sourceNeuronID = 1;
    gene->destinationNeuronID = 6;
    gene->weightValue=1;
    gene->innovationNumber=10;
    gene->enabled=true;
    gene->inputNeuronIDs = &inputs;
    gene->outputNeuronIDs = &outputs;
    net2genome.push_back(gene);

    for(int i = 0; i < net1genome.size(); i++){
        printf("Each one is %d\n", net1genome.at(i)->sourceNeuronID);
    }

    vector<Gene*>* result = breedNetworks(&net1genome, &net2genome); 
    printf("Size: %d\n", result->size());
    for(int i = 0; i < result->size(); i++){
        Gene * gene = result->at(i);
        printf("Inno: %d, From %d, To %d\n", gene->innovationNumber, gene->sourceNeuronID, gene->destinationNeuronID);
    }




    //net.inputs = inputs;
    //net.update();
    //vector<float> outputs = net.outputs;

    //for(int i = 0; i < outputs.size(); i++){
    //    cout << outputs.at(i) << ",";
    //}
    //cout << endl;

    //vector<Gene *> genes = convertNetworkToGenes(&net);
    //printf("Size: %d\n", genes.size());
    //for(int i = 0; i < genes.size(); i++){
    //    Gene * gene = genes.at(i);
    //    printf("Gene %d: Source: %d, Destionation %d, weight: %d\n", i+1, gene->sourceNeuronID, gene->destinationNeuronID, (int) gene->weightValue);
    //}

    //Network *newNet = convertGenesToNetwork(genes);
    //newNet->inputs = inputs;
    //newNet->update();
    //outputs.clear();
    //outputs = newNet->outputs;

    //for(int i = 0; i < outputs.size(); i++){
    //    cout << outputs.at(i) << ",";
    //}

    //for(int i = 0; i < genes.size(); i++){
    //    free(genes.at(i));
    //}

}
