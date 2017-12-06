#include <iostream>
#include "network.h"
#include "genetics.h"
#include "evolution.h"
#include "debug.h"
#include <stdlib.h>

using namespace std;

int main(){
    //TODO 
    //1. Make a rng in NEAT.cpp to be used by all of NEAT
    //2. Speciation
    //3. Add different node types (sigmoid, add, diff, etc.)
    //

      initNeat();
      printf("Random: %f\n", (double) rand() / RAND_MAX);
      run();

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
