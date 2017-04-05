//@TODO: Rename this to AS? For Ant System? oops
#ifndef __AC_h
#define __AC_h

#include <vector>
#include <iostream>
#include <string>
#include <set>
#include <cmath>
#include <random>
#include <limits>

using namespace std;

//@TODO: Replaces all occurences of BIG_DOUBLE with MAX_DOUBLE
const double MAX_DOUBLE = numeric_limits<float>::max();

struct Ant {
  vector<int> tour;       //ordered list of the ant's tour
  vector<bool> unvisited; //1 if unvisited, 0 if visited
  double length;          //total tour length
  int last() {return tour[tour.size()-1];} // last city in tour
};

/**
 * Contains all the variables and functions that BOTH elitist and
 * colony systems require.
 */
class AntSystem {
public:
    AntSystem(double a,double b,double e,
	      int colonySize, int numIterations,
	      vector <vector <double > > cityLocations, double tau_0);

protected:
    Ant best_ant; //just such a cool ant
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
    //    void init_phers();
};

#endif
