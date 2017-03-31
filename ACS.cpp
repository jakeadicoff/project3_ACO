#include "ACS.h"

ACS::ACS(double a, double b, double e, int colonySize, int numIterations, vector<vector<double>> cityLocations, double elitismFactor) {
    AntSystem(a, b, e, colonySize, numIterations, cityLocations);
    this->elitism_factor = elitismFactor;
}

void ACS:runACS() {
    
}
