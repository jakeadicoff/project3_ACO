#include "AC.h"



AntSystem::AntSystem(double a, double b, double e, int colonySize, int numIterations, vector <vector <double > > cityLocations, double t0) {
    
    this->alpha = a;
    this->beta = b;
    this->evap_rate = e;
    this->colony_size = colonySize;
    this->num_iterations = numIterations;
    this->num_cities = cityLocations.size();
    
    vector<vector <double > > ps;
    vector<vector <double > > ds;
    Ant dummy_ant;
    vector<Ant> dummy_colony(colony_size, dummy_ant);
    this->colony = dummy_colony;
    dummy_ant.length = BIG_DOUBLE;
    
    this->dists = ds;
    this->pheromones = ps;
    this->best_ant = dummy_ant;
    
    init_dists_and_phers(cityLocations);
    this->tau_0 = 1 / (colony_size * length_nn());
    
}
void AntSystem::make_ants() {
    for(int i = 0; i < colony_size; ++i) {
        Ant new_ant;
        colony.push_back(new_ant);
    }
}

void AntSystem::init_dists_and_phers(vector <vector <double> > cityLocations) {
    vector <double> row1;
    vector <double> row2;
    for(int i = 0; i < num_cities; i++) {
        row1.clear();
        row2.clear();
        for(int j = 0; j < i; j++) {
            double dist_ij = euc_dist(cityLocations[i], cityLocations[j]);
            row1.push_back(dist_ij);
            row2.push_back(0);
        }
        dists.push_back(row1);
        pheromones.push_back(row2);
    }
    
    clear_ants();
    init_phers();
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
    colony[ant_index].length += lookup_dist(curr_city,next_city);
    // that was neat
}

void AntSystem::clear_ants() {
    for(int i = 0; i < colony_size; i++) {
        colony[i].tour.clear();
        colony[i].length = 0;
        vector<bool> true_vec(num_cities, true);
        colony[i].unvisited = true_vec;
    }
}

double AntSystem::length_nn() {
    Ant nn_ant;
    vector<bool> ones(num_cities, true);
    nn_ant.unvisited = ones;
    nn_ant.tour.push_back(0);
    nn_ant.unvisited[0] = false;
    int curr_city = 0;
    
    for(int i = 0; i < num_cities - 1; ++i) {
        int nearest_city;
        double dist_to_nearest_city = BIG_DOUBLE;
        
        for(int j = 0; j < num_cities; ++j) {
            if(nn_ant.unvisited[j] == true) {
                
                double path_dist = lookup_dist(curr_city, j);
                // if this city is the new nearest, update
                if(path_dist < dist_to_nearest_city) {
                    nearest_city = j;
                    dist_to_nearest_city = path_dist;
                }
            }
        }
        // update the ant's tour and unvisited vector
        nn_ant.unvisited[nearest_city] = false;
        nn_ant.tour.push_back(nearest_city);
        nn_ant.length += lookup_dist(nearest_city, curr_city);
        
        curr_city = nearest_city;
    }
    
    // go home
    nn_ant.tour.push_back(0);
    nn_ant.length += dists[curr_city][0];
    
    return nn_ant.length;
}

// add initial pheromone to every path
void AntSystem::init_phers() {
    for(int i = 1; i < num_cities; ++i) {
        for(int j = 0; j < i; ++j) {
            pheromones[i][j] = tau_0;
        }
    }
}


