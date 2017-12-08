#ifndef NETWORK_H
#define NETWORK_H
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

typedef struct Neuron Neuron;
typedef struct AxonNeuronPair AxonNeuronPair;

typedef struct AxonNeuronPair{
    //Variables
    Neuron * neuron;
    float weight;
    int innovationNumber;
    bool enabled;

    //Functions
    float getValue(vector<int>& beingCalcualted);
    AxonNeuronPair();
    void setNeuron(Neuron *ner);

}AxonNeuronPair;

typedef struct Neuron{
    //Variables
    vector<AxonNeuronPair *> inputs;
    bool alreadyCalculated; 
    float result;
    int ID;
    int type;
    float input;
    bool alreadyConverted;

    //Functions
    Neuron(int i);
    float getValue(vector<int>& beingCalculated);

}Neuron;

class Network{
    public:
        Network(int i);
        ~Network();
        vector<float> outputs;
        vector<float> inputs;
        void update();
        void getGenes(); //TODO This will return a pointer to the networks genes in memory
        void loadGenes();
 //   private: //Comenting this out so that I can modify this stuff easily for now
        int ID;
        vector<AxonNeuronPair *> hiddenLayerNeurons;
        vector<Neuron *> allNeurons;
        vector<Neuron *> inputNeurons;
        vector<Neuron *> outputNeurons;
        
};
#endif
