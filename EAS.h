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
    EAS::EAS(double a, double b, double e, int colonySize, int numIterations, vector <vector < double > cityLocations, double elitismFactor) : AntSystem(a,b,e,colonySize,numIterations,cityLocations),
    elitism_factor(elitismFactor) {}
    void run_eas();
private:
    double elitism_factor;
    
    void pick_initial_cities();
    void add_last_cities();
    void update_ant(int ant_index, int city_index);
    
};

#endif 
