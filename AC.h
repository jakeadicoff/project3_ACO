#ifndef __AC_h
#define __AC_h

#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <cmath>
#include <random>



using namespace std;

const double BIG_DOUBLE = 999999999999999;
const double pi = 3.14159;

struct Ant {
    vector<int> tour;
    vector<bool> unvisited;
    double length;
    int last() {return tour[tour.size()-1];}
};


enum Coordinates {GEOGRAPHIC, EUCLIDEAN};

struct Cities {
    vector<vector<double>> positions;
    Coordinates coordinate_system;
};

struct Result {
    double best_length;
    double run_time;
    double greedy_result;
    vector<double> best_ant_every_10;
    int iteration_of_best_ant;
};

class AntSystem {
public:
    AntSystem(double a,double b,double e,int colonySize, int numIterations, Cities tsp, double tau_0);
    
    
protected:
    Coordinates coordinates;
    Result results;
    Ant best_ant;
    vector<Ant> colony;
    vector<vector<double>> dists;
    vector<vector<double>> pheromones;
    double alpha, beta, evap_rate, tau_0;
    int colony_size, num_iterations, num_cities;
    
    void probabilistic_next_step(int ant_index);
    void init_dists_and_phers(vector<vector< double> > cityLocations);
    double euc_dist(vector <double> a, vector <double> b);
    double lookup_dist(int i, int j);
    double lookup_pher(int i, int j);
    void clear_ants();
    double length_nn();
    void make_ants();
    void init_phers();
    double rad_to_deg(double rad);
    double deg_to_rad(double deg);
    double geo_dist(vector<double> a, vector<double> b);
};

#endif
