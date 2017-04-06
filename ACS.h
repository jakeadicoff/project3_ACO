#ifndef __ACS_h
#define __ACS_h

#include "AC.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <time.h>

using namespace std;



class ACS : public AntSystem {
    
public:
    void runACS();
    ACS(double a, double b, double e, int colonySize, int numIterations, Cities tsp, double t0, double wearFactor, double q0);
    
    
private:
    void pheromone_update();
    void exploitation_step(int ant_index);
    void make_tours();
    void wear_away();
    void add_pheromone();
    void init_phers();
    
    double epsilon, tau_0, q_0;
    
    
    
};

#endif




