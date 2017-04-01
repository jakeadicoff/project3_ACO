#include "EAS.h"

using namespace std;


//EAS::EAS(double a, double b, double e, int colonySize, int numIterations, vector <vector < double > > cityLocations, double elitismFactor) {
  //AntSystem(a,b,e,colonySize,numIterations,cityLocations);
  //this->elitism_factor = elitismFactor;
  //cout << alpha << endl;
//}




void EAS::run_eas() {
  for(int i = 0; i < num_iterations; i++) {
    pick_initial_cities();
    for(int j = 0; j < num_cities - 1; j++) {

      for(int k = 0; k < colony_size; k++) {
	int city_index = probabilistic_next_step(k);  
	update_ant(k,city_index);
      } // colony
    } // cities
    add_last_cities();
    // pheromone_update();
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

