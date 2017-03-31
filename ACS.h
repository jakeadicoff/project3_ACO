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



class ACS : public AntSystem {

public:
    void runACS();
    ACS();
    
    
private:
    void pheromone_update();
    void exploitation_step(int ant_index);
    void take_step(int ant_index);
    void wear_away(int start_city, int end_city);
    void add_pheromone(int start_city, int end_city);
    
    
};

#endif




