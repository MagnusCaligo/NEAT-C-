#include <iostream>
#include "network.h"
#include "genetics.h"
#include "evolution.h"
#include "debug.h"
#include "NEAT.h"
#include <stdlib.h>

using namespace std;

int main(){
      initNeat();

      NEAT neat(3,1);
      int size = 500;

      vector<int> orgs;
      for(int i = 0; i < size; i++){
          orgs.push_back(neat.addOrganism());
      }

      vector<vector<float>> possibleInputs;
      
      possibleInputs.push_back(vector<float> {0, 0, 1});
      possibleInputs.push_back(vector<float> {0, 1, 1});
      possibleInputs.push_back(vector<float> {1, 0, 1});
      possibleInputs.push_back(vector<float> {1, 1, 1});

      Network* bestNet;

      for(;;){
          float avgFitness = 0;
          float maxFitness = -10;
          
          vector<int> bestOrder;
          for(int i = 0; i < size; i++){
              float fitness = 0;
              vector<int> order;
              printf("Starting Network\n");
              for(int m = 0; m < possibleInputs.size(); m++){
                  int value = m;
                  order.push_back(value);
                  vector<float> inputs = possibleInputs.at(value);
                  vector<float>output = neat.inputOrganismNetworkInputs(orgs[i], inputs);
                  int correctOutput =(int)(inputs[0]) ^ (int)(inputs[1]);
                  //int correctOutput = !inputs[0];
                  if(correctOutput == 0){
                      correctOutput = -1;
                  }
                  fitness += pow((float)correctOutput - output[0], 2);
                  printf("Correct Output %d, Network Output %f, fitness give %f\n", correctOutput, output[0], fitness);
              }
              cout << endl;
              fitness = 1 - fitness;
              if(fitness > maxFitness){
                  maxFitness = fitness;
                  bestOrder = order;
              }
              avgFitness += fitness;
              neat.inputOrganismFitness(orgs[i], fitness);
          }
          avgFitness /= size;
          printf("Average was %f, max was %f\n", avgFitness, maxFitness);

          if(maxFitness > .1){
              printf("Breaking...\n");
              bestNet = neat.getBestNetwork();
              printf("Best Net ID: %d, Neurons %d, Connections %d\n", bestNet->ID, bestNet->allNeurons.size(), bestNet->hiddenLayerNeurons.size());
              for(int i = 0; i < bestOrder.size(); i++){
                  //printf("Order %d\n", bestOrder.at(i));
              }
              break;
          }
          //printf("Getting Next Epoch\n");
          int i;
          //cin >> i;
          neat.nextEpoch();
      }

      for(;;){
          float input1;
          float input2;
          cin >> input1;
          cin >> input2;

//          vector<float> inputs = {
//              input1, 1
//          };
          vector<float> inputs = {
              input1, input2, 1
          };

          bestNet->inputs = inputs;
          bestNet->update();
          vector<float> output = bestNet->outputs;
          cout << output[0] << endl;
      }

}


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

