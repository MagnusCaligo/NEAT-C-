#include <iostream>
#include "network.h"

using namespace std;

AxonNeuronPair::AxonNeuronPair(){
    enabled = 1;
}

void AxonNeuronPair::setNeuron(Neuron *ner){
    neuron = ner;
}

float AxonNeuronPair::getValue(vector<int>& beingCalculated){
    if(find(beingCalculated.begin(), beingCalculated.end(),neuron->ID) == beingCalculated.end()){
        return (float)(neuron->getValue(beingCalculated) * weight * enabled);
    }else{
        return (float)(neuron->result * weight * enabled);
    }
}

Neuron::Neuron(int i){
    ID = i;
    alreadyCalculated = 0;
    result = 1;
    type = 1;
    alreadyConverted = 0;
}


float Neuron::getValue(vector<int>& beingCalculated){
    input = 0;
    if(alreadyCalculated == 0){
        alreadyCalculated = 1;
        if(type == 0){
            return result;
        }else if(type == 1){
            beingCalculated.push_back(ID);
            for(int i = 0; i < (int) inputs.size(); i++){
                input += inputs.at(i)->getValue(beingCalculated);
            }
            input = (1/(exp(-input) + 1)) -.5;
            //printf("Final result is %f\n", input);
            //input *= 5;
            result = input;
            beingCalculated.erase(remove(beingCalculated.begin(), beingCalculated.end(), ID), beingCalculated.end());
            return input;
        }else if(type == 2){
            beingCalculated.push_back(ID);
            printf("Amount of inputs is %d\n", inputs.size());
            for(int i = 0; i < (int) inputs.size(); i++){
                input += inputs.at(i)->getValue(beingCalculated);
            }
            //input = (1/(exp(-input) + 1)) -.5;
            //printf("Final result is %f\n", input);
            //result = input * 5;
            result = input;
            beingCalculated.erase(remove(beingCalculated.begin(), beingCalculated.end(), ID), beingCalculated.end());
            return result;
        }
    }else{
        return result;
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
        cout << inputs.size() << ", " << inputNeurons.size() <<endl;
        return;
    }
    for(int i = 0; i < inputs.size(); i++){
        Neuron* neuron = NULL;
        for(int m = 0; m < inputs.size(); m++){
           if(inputNeurons.at(m)->ID == i){
               neuron = inputNeurons.at(m);
               break;
           }
        }
        if(neuron == NULL){ 
            throw runtime_error("Couldn't find input neuron");
        }
        neuron->result = inputs.at(i);
    }
    outputs.clear();
    vector<int> beingCalculated;
    for(int i = 0; i < (int) outputNeurons.size(); i++){
       outputs.push_back(outputNeurons.at(i)->getValue(beingCalculated)); 
    }
    for(int i = 0; i < (int) allNeurons.size(); i++){
        allNeurons.at(i)->alreadyCalculated = 0;
    }
}

