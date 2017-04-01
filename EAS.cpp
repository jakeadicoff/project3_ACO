#include "EAS.h"

using namespace std;


//EAS::EAS(double a, double b, double e, int colonySize, int numIterations, vector <vector < double > > cityLocations, double elitismFactor, double tau_0) {
  //AntSystem(a,b,e,colonySize,numIterations,cityLocations, tau_0);
  //this->elitism_factor = elitismFactor;
  //cout << alpha << endl;
//}




void EAS::run_eas() {
  //init_phers();
  for(int i = 0; i < num_iterations; i++) {
    clear_ants();
    pick_initial_cities();
    for(int j = 0; j < num_cities - 1; j++) {
      for(int k = 0; k < colony_size; k++) {
        probabilistic_next_step(k);  
      } // colony
    } // cities
    add_last_cities();
    pheromone_update();
  } // iterations
}


// randomly assign an ant some initial city
void EAS::pick_initial_cities() {
  for(int i = 0; i < colony_size; i++) {
    int random = rand() % num_cities;
    update_ant(i,random);
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
  colony[ant_index].tour.push_back(city_index);
  colony[ant_index].unvisited[city_index] = false;
  colony[ant_index].length += lookup_dist(colony[ant_index].last(),city_index);
}

void EAS::pheromone_update() {
  for(int i = 0; i < num_cities; i++) {
    for(int j = 0; j <= i; j++) {
      pheromones[i][j] = (1-evap_rate)*pheromones[i][j];
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
