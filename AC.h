#ifndef __AC_h
#define __AC_h

#include <vector>
#include <string>
#include <set>


using namespace std;

struct Ant {
    set<int> tour;
    set<int> unvisited;
    double length;
};

class AntSystem {
 public:
    void AntSystem();
    

 private:
    Ant best_ant;
    vector<Ant> colony;
    vector<vector<double>> dists;
    vector<vector<double>> pheromones;
    double alpha, beta, evap_rate;
    int colony_size, num_iterations, num_cities;
    
    void take_next_step(int ant_index);
};

#endif
