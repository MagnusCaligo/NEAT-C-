#include <iostream>
#include "network.h"

using namespace std;

AxonNeuronPair::AxonNeuronPair(){
    enabled = 1;
}

void AxonNeuronPair::setNeuron(Neuron *ner){
    neuron = ner;
}

float AxonNeuronPair::getValue(){
    return (float)(neuron->getValue() * weight * enabled);
}

Neuron::Neuron(int i){
    ID = i;
    alreadyCalculated = 0;
    result = 2;
    type = 1;
    alreadyConverted = 0;
}


float Neuron::getValue(){
    input = 0;
    if(type == 0){
        return result;
    }else if(type == 1){
        for(int i = 0; i < (int) inputs.size(); i++){
            input += inputs.at(i)->getValue();
        }
        return input;
    }
}

Network::Network(int i){
    ID = i;
}

Network::~Network(){

}

void Network::update(){
    if(inputs.size() != inputNeurons.size()){
        cout << "Input amount mismatch" << endl;
        return;
    }
    outputs.clear();
    for(int i = 0; i < (int) outputNeurons.size(); i++){
       outputs.push_back(outputNeurons.at(i)->getValue()); 
    }
}

