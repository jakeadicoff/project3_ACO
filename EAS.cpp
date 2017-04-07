#include "EAS.h"

using namespace std;


//EAS::EAS(double a, double b, double e, int colonySize, int numIterations, vector <vector < double > > cityLocations, double elitismFactor, double tau_0) {
//AntSystem(a,b,e,colonySize,numIterations,cityLocations, tau_0);
//this->elitism_factor = elitismFactor;
//cout << alpha << endl;
//}




Result EAS::run_eas() {
    
    double start_time = clock();
    double curr_best = BIG_DOUBLE;
    
    init_phers();
    
    for(int i = 0; i < num_iterations; i++) {
    
        clear_ants();
        
        pick_initial_cities();
        for(int j = 0; j < num_cities - 1; j++) {
            for(int k = 0; k < colony_size; k++) {
                probabilistic_next_step(k);
            } // colony
        } // cities
        add_last_cities();
        update_best_ant();
        pheromone_update();
        
        if(i % 10 == 0) {
            results.best_ant_every_10.push_back(best_ant.length);
            cout << "Iteration " << i << ": " << best_ant.length;
            cout << endl;
        }
        if(best_ant.length < curr_best) {
            curr_best = best_ant.length;
            results.iteration_of_best_ant = i;
        }

    } // iterations
    //cout << best_ant.length << endl;
//    for(int i = 0; i < num_cities; i++) {
//        cout << best_ant.tour[i] << " ";
//    }
    cout << endl;
    double end_time = clock();
    
    results.greedy_result = length_nn();
    results.best_length = best_ant.length;
    results.run_time = (end_time - start_time)/CLOCKS_PER_SEC;
    
    cout << "The shortest ACS path is " << best_ant.length << endl;
    cout << "The shortest greedy path is " << results.greedy_result << endl;
    cout << "Runtime: " << results.run_time << endl;
    
    return results;
}


// randomly assign an ant some initial city
void EAS::pick_initial_cities() {
    
    for(int i = 0; i < colony_size; i++) {
        int random = rand() % num_cities;
        colony[i].tour.push_back(random);
        colony[i].unvisited[random] = false;
    }
}
// add the final leg (back to initial city) to an ants tour
void EAS::add_last_cities() {
    for(int i = 0; i < colony_size; i++) {
        update_ant(i,colony[i].tour[0]);
    }
}
// make all necessary updates to the Ant type when a new city is picked
void EAS::update_ant(int ant_index, int city_index) {
    colony[ant_index].length += lookup_dist(colony[ant_index].last(),city_index);
    colony[ant_index].tour.push_back(city_index);
    colony[ant_index].unvisited[city_index] = false;
    //cout << "a" << endl;
    
    //cout << "b" << endl;
}

void EAS::pheromone_update() {
    for(int i = 0; i < num_cities; i++) {
        for(int j = 0; j < i; j++) {
            pheromones[i][j] = (1-evap_rate)*lookup_pher(i, j);
            pheromones[i][j] += pher_sum(i,j);
            pheromones[i][j] += elitism_factor*in_bsf(i,j);
        }
    }
}

double EAS::in_bsf(int city_1, int city_2) {
    for(int i = 0; i < num_cities; i++) {
        if((best_ant.tour[i] == city_1 && best_ant.tour[loop_list(i+1,num_cities)] == city_2 ) || (best_ant.tour[i] == city_2 && best_ant.tour[loop_list(i+1,num_cities)] == city_1 )) {
            return 1/best_ant.length;
        }
    }
    return 0;
}

double EAS::pher_sum(int city_1, int city_2) {
    double sum = 0;
    for(int i = 0; i < colony_size; i++) {
        for(int j = 0; j < num_cities; j++) {
            if((colony[i].tour[j] == city_1 && colony[i].tour[loop_list(j+1,num_cities)] == city_2) || (colony[i].tour[j] == city_2 && colony[i].tour[loop_list(j+1,num_cities)] == city_1)) {
                sum += 1/colony[i].length;
                break;
            }
        }
    }
    return sum;
}

int EAS::loop_list(int i, int list_size) {
    if(0 > i) {
        return list_size - 1;
    }
    return i%list_size;
}

void EAS::update_best_ant() {
    for(int i = 0; i < colony_size; i++) {
        if(colony[i].length < best_ant.length) {
            
            best_ant = colony[i];
        }
    }
}
