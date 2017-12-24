#include "not.h"
#include <iostream>
#include <vector>
#include "NEAT.h"

using namespace std;


void runNot(){
      initNeat();

      NEAT neat(2,1);
      int size = 1000;

      vector<int> orgs;
      for(int i = 0; i < size; i++){
          orgs.push_back(neat.addOrganism());
      }

      vector<vector<float>> possibleInputs;
      
      possibleInputs.push_back(vector<float> {0, 1});
      possibleInputs.push_back(vector<float> {1, 1});
      possibleInputs.push_back(vector<float> {0, 1});
      possibleInputs.push_back(vector<float> {1, 1});
      possibleInputs.push_back(vector<float> {0, 1});
      possibleInputs.push_back(vector<float> {1, 1});

      Network* bestNet;

      for(;;){
          float avgFitness = 0;
          float maxFitness = -10;
          
          vector<int> bestOrder;
          for(int i = 0; i < size; i++){
              float fitness = 0;
              vector<int> order;
              int inputsCompleted[possibleInputs.size()];
              int sum = 0;
              while(sum != possibleInputs.size()){
                  int value = (int)((double) rand() / RAND_MAX * possibleInputs.size());
                  inputsCompleted[value] = 1;
                  order.push_back(value);
                  vector<float> inputs = possibleInputs.at(value);
                  vector<float>output = neat.inputOrganismNetworkInputs(orgs[i], inputs);
                  int correctOutput = !inputs[0];
                  if(correctOutput == 0){
                      //correctOutput = -1;
                  }
                  fitness += pow((float)correctOutput - output[0], 2);
                  sum = 0;
                  for(int i : inputsCompleted){
                      sum += i;
                  }
              }
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

          if(maxFitness > .9){
              printf("Breaking...\n");
              bestNet = neat.getBestNetwork();
              printf("Best Net ID: %d, Neurons %d, Connections %d\n", bestNet->ID, bestNet->allNeurons.size(), bestNet->hiddenLayerNeurons.size());
              break;
          }
          neat.nextEpoch();
      }

      for(;;){
          float input1;
          cin >> input1;

          vector<float> inputs = {
              input1, 1
          };

          bestNet->inputs = inputs;
          bestNet->update();
          vector<float> output = bestNet->outputs;
          cout << output[0] << endl;
      }

}
