#include "ACS.h"

ACS::ACS(double a, double b, double e, int colonySize, int numIterations, vector<vector<double>> cityLocations, double t0, double wearFactor) {
    AntSystem(a, b, e, colonySize, numIterations, cityLocations);
    this->epsilon = wearFactor;
    this->tau_0 = t0;
    
    // give all paths epsilon * tau_0 pheromones
    init_phers();
}

void ACS::runACS() {
    
}

// add initial pheromone to every path
void ACS::init_phers() {
    for(int i = 1; i < num_cities; ++i) {
        for(int j = 0; j < i; ++j) {
            pheromones[i][j] = tau_0 * epsilon;
        }
    }
}


// add pheromone to every ant path on bsf and evaporate from all
void ACS::add_pheromone() {
    
    //evaporate pheromone
    for(int i = 1; i < num_cities; ++i) {
        for(int j = 0; j < i; ++j) {
            pheromones[i][j] = (1 - evap_rate) * pheromones[i][j];
        }
    }
    
    // add pheromone to paths on bsf
    for(int j = 0; j < num_cities; ++j) {
        int start_city = best_ant.tour[j];
        int end_city;
        if(j < num_cities - 1) {
            end_city = best_ant.tour[j+1]
        }
        else {
            end_city = best_ant.tour[0];
        }
        pheromones[start_city][end_city] = evap_rate / lookup_dist(start_city, end_city);
    }
}


// wear away the paths of all the ants
void ACS::wear_away() {
    for(int i = 0; i < colony_size; ++i) {
        //THIS WILL SEGFAULT UNLESS THE ANTS LAST & FIRST START IS INLCUDED
        for(int j = 0; j < num_cities; ++j) {
            int start_city = colony[i].tour[j];
            int end_city;
            if(j < num_cities - 1) {
                end_city = colony[i].tour[j+1]
            }
            else {
                end_city = colony[i].tour[0];
            }
            pheromones[start_city][end_city] = (1 - epsilon) * pheromones[start_city][end_city] + tau_0 * epsilon;
        }
    }
}


// take the exploitation step that maximizes pheromone/distance
void ACS::exploitation_step(int ant_index) {
    
    int max_city;
    double max_city_value = -1;
    
    for(int i = 0; i < num_cities; ++i) {
        if(colony[ant_index].unvisited[i] = true) {
            int curr_city = colony[ant_index].tour.back();
            double path_dist = lookup_dist(curr_city, i);
            double path_pher = lookup_pher(curr_city, i);
            double city_value = path_pher * pow(1 / path_dist, beta);
            
            // if this city is the new best, update
            if(max_city_value < city_value) {
                max_city = i;
                max_city_value = city_value;
            }
        }
    }
    
    // update the ant's tour and unvisited vector
    colony[ant_index].unvisited[max_city] = false;
    colony[ant_index].tour.push_back(max_city);
}

double ACS::rand_between_01() {
    return (double) rand() / RAND_MAX;
}






