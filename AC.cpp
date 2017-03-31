#include "AC.h"

double BIG_DOUBLE = 999999999999999;

AntSystem::AntSystem(double a, double b, double e, int colonySize, int numIterations, vector <vector <double > > cityLocations) {
  this->alpha = a;
  this->beta = b;
  this->evap_rate = e;
  this->colony_size = colonySize;
  this->num_iterations = numIterations;
  this->num_cities = cityLocations.size();
  vector<vector <double > > ps;
  vector<vector <double > > ds;
  Ant dummy_ant;
  dummy_ant.length = BIG_DOUBLE;
  this->dists = ds;
  this->pheromones = ps;
  this->best_ant = dummy_ant;
}


void AntSystem::init_dists(vector <vector <double> > cityLocations) {
  vector <double> row;
  for(int i = 0; i < num_cities; i++) {
    row.clear();
    for(int j = 0; j <= i; j++) {
      double dist_ij = euc_dist(cityLocations[i], cityLocations[j]);
      row.push_back(dist_ij);
    }
    dists.push_back(row);
  }
}

double AntSystem::euc_dist(vector <double> a, vector <double> b) {
  return sqrt(pow(a[0]-b[0],2)+pow(a[1]-b[1],2));
}

double AntSystem::lookup_dist(int i, int j) {
  if( i > j) return dists[i][j];
  return dists[j][i];
}

double AntSystem::lookup_pher(int i, int j) {
  if( i > j) return pheromones[i][j];
  return pheromones[j][i];
}
  
int AntSystem::probabilistic_next_step(int ant_index) {
  double sum = 0;
  vector<double> probability_vector;
  // consider computing this once when ant picks first city, and then subtract from the sum whenever an ant picks a new leg. ew.
  for(int i = 0; i < num_cities; i++ ) { 
    double x = 0;
    if(colony[ant_index].unvisited[i]) {
      x = pow(lookup_pher(colony[ant_index].last(),i),alpha) +  pow(lookup_dist(colony[ant_index].last(),i),beta);
    }
    sum += x;
    probability_vector.push_back(x);
  }
  for(int i = 0; i < probability_vector.size(); i++){
    probability_vector[i] = probability_vector[i]/sum;
  }
}

