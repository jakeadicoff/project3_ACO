#ifndef __EAS_h
#define __EAS_h

#include "AC.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

class EAS : public AntSystem {
 public:
 EAS(double a, double b, double e, int colonySize, int numIterations, vector<vector<double>> cityDists, double elitismFactor, double tau_0) :
  AntSystem(a,b,e,colonySize,numIterations,cityDists, tau_0),
    elitism_factor(elitismFactor) {}

  Result run_eas();

 private:
  double elitism_factor;

  void init_phers();
  void pick_initial_cities();
  void add_last_cities();
  void update_ant(int ant_index, int city_index);
  void pheromone_update();
  void regular_ant_contribution();
  void best_ant_contribution();
  void add_pheremone(int cityA, int cityB, double quantity);
  void update_best_ant();

};

#endif
