#include "AC.h"



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
    init_dists_and_phers(cityLocations);
}


void AntSystem::init_dists_and_phers(vector <vector <double> > cityLocations) {
    vector <double> row1;
    vector <double> row2;
    for(int i = 0; i < num_cities; i++) {
        row1.clear();
        row2.clear();
        for(int j = 0; j <= i; j++) {
            double dist_ij = euc_dist(cityLocations[i], cityLocations[j]);
            row1.push_back(dist_ij);
            row2.push_back(0);
        }
        dists.push_back(row1);
        pheromones.push_back(row2);
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

void AntSystem::probabilistic_next_step(int ant_index) {
    
    int curr_city = colony[ant_index].tour.back();
    
    vector<double> probability_vector;
    // num cities is a bool vector
    for(int i = 0; i < num_cities; i++ ) {
        // initialize weight to 0
        double weight = 0;
        // if city is unvisited update weight accordingly
        if(colony[ant_index].unvisited[i]) {
            weight = pow(lookup_pher(colony[ant_index].last(),i),alpha) +  pow(lookup_dist(colony[ant_index].last(),i),beta);
        }
        // push back weight
        probability_vector.push_back(weight);
    }
    // this line may only need to be used once, i forget CHECK IT
    default_random_engine generator;
    // black box
    discrete_distribution<double> distribution (probability_vector.begin(),probability_vector.end());

    int next_city = distribution(generator);
    
    // update the ant's tour and unvisited vector
    colony[ant_index].unvisited[next_city] = false;
    colony[ant_index].tour.push_back(next_city);
    colony[ant_index].length += dists[curr_city][next_city];
    // that was neat
}




