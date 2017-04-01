#ifndef __AC_h
#define __AC_h

#include <vector>
#include <string>
#include <set>
#include <cmath>
#include <random>

using namespace std;

const double BIG_DOUBLE = 999999999999999;


struct Ant {
    vector<int> tour;
    vector<bool> unvisited;
    double length;
    int last() {return tour[tour.size()-1];}
};

class AntSystem {
public:
    AntSystem(double a,double b,double e,int colonySize, int numIterations, vector <vector <double > > cityLocations);
    
    
protected:
    Ant best_ant;
    vector<Ant> colony;
    vector<vector<double>> dists;
    vector<vector<double>> pheromones;
    double alpha, beta, evap_rate;
    int colony_size, num_iterations, num_cities;
    
    void probabilistic_next_step(int ant_index);
    void init_dists_and_phers(vector<vector< double> > cityLocations);
    double euc_dist(vector <double> a, vector <double> b);
    double lookup_dist(int i, int j);
    double lookup_pher(int i, int j);
    void clear_ants();
};

#endif
