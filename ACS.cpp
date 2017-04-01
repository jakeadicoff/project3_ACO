#include "ACS.h"

ACS::ACS(double a, double b, double e, int colonySize, int numIterations, vector<vector<double>> cityLocations, double t0, double wearFactor, double q0) : AntSystem(a, b, e, colonySize, numIterations, cityLocations) {
    //AntSystem(a, b, e, colonySize, numIterations, cityLocations);
    this->epsilon = wearFactor;
    //this->tau_0 = t0;
    this->q_0 = q0;
    srand(time(NULL));
    
}

void ACS::runACS() {
    
    double start_time = clock();
    
    for(int i = 0; i < num_iterations; ++i) {
        make_tours();
        wear_away();
        add_pheromone();
        clear_ants();
    }
    
    double end_time = clock();
    cout << "The shortest ACS path is " << best_ant.length << endl;
    cout << "The shortest greedy path is " << length_nn() << endl;
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
            end_city = best_ant.tour[j+1];
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
                end_city = colony[i].tour[j+1];
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
    int curr_city = colony[ant_index].tour.back();
    
    for(int i = 0; i < num_cities; ++i) {
        if(colony[ant_index].unvisited[i] == true) {
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
    colony[ant_index].length += dists[curr_city][max_city];
}

void ACS::make_tours() {
    for(int i = 0; i < colony_size; ++i) {
        
        
        int starting_city = rand() % num_cities;
        colony[i].tour.push_back(starting_city);
        
        for(int j = 0; j < num_cities - 1; ++j) {
            double step_prob = (double) rand() / RAND_MAX;
            
            if(step_prob < q_0) {
                exploitation_step(i);
            }
            else {
                probabilistic_next_step(i);
            }
        }
        
        // make ant return to starting city
        colony[i].tour.push_back(starting_city);
        colony[i].length += lookup_dist(starting_city, colony[i].tour.back());
        
        // update best ant as necessary
        if(colony[i].length < best_ant.length) {
            best_ant = colony[i];
        }
    }
}







