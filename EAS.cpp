#include "EAS.h"

using namespace std;


//EAS::EAS(double a, double b, double e, int colonySize, int numIterations, vector <vector < double > > cityLocations, double elitismFactor, double tau_0) {
  //AntSystem(a,b,e,colonySize,numIterations,cityLocations, tau_0);
  //this->elitism_factor = elitismFactor;
  //cout << alpha << endl;
//}




void EAS::run_eas() {
  cout << "1" << endl;
  init_phers();
  cout << "2" << endl;
  for(int i = 0; i < num_iterations; i++) {
    cout << "3" << endl;
    clear_ants();
    cout << "4" << endl;
    pick_initial_cities();
    cout << "5" << endl;
    for(int j = 0; j < num_cities - 1; j++) {
      for(int k = 0; k < colony_size; k++) {
        cout << "6" << endl;
	probabilistic_next_step(k);  
	cout << "7" << endl;
      } // colony
    } // cities
    cout << "8" << endl;
    add_last_cities();
    cout << "9" << endl;
    update_best_ant();
    cout << "10" << endl;
    pheromone_update();
    cout << "11" << endl;
  } // iterations
  cout << best_ant.length << endl;
  for(int i = 0; i < num_cities; i++) {
    cout << best_ant.tour[i] << " ";
  }
  cout << endl;
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
  cout << "a" << endl;
  
  cout << "b" << endl;
}

void EAS::pheromone_update() {
  for(int i = 0; i < num_cities; i++) {
    for(int j = 0; j < i; j++) {
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

void EAS::update_best_ant() {
  for(int i = 0; i < colony_size; i++) {
    cout << "len: " << colony[i].length << endl;
    if(colony[i].length < best_ant.length) {
      
      best_ant = colony[i];
    }
  }
}
