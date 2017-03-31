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

using namespace std;

srand(time(NULL));

class ACS : public AntSystem {

public:
    void runACS();
    ACS();
    
    
private:
    void pheromone_update();
    void exploitation_step(int ant_index);
    void take_step(int ant_index);
    void wear_away();
    void add_pheromone();
    
    double wear, tau_0;
    
    double rand_between_01();
    
};

#endif




