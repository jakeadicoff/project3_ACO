#include "EAS.h"

using namespace std;


//EAS::EAS(double a, double b, double e, int colonySize, int numIterations, vector <vector < double > > cityLocations, double elitismFactor, double tau_0) {
//AntSystem(a,b,e,colonySize,numIterations,cityLocations, tau_0);
//this->elitism_factor = elitismFactor;
//cout << alpha << endl;
//}


void EAS::run_eas() {
  this->tau_0 = (elitism_factor + colony_size)/(evap_rate * length_nn()); //input t0 in unecessary
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
  } // iterations

  cout << best_ant.length << endl;
  for(int i = 0; i < num_cities; i++) {
    cout << best_ant.tour[i] << " ";
  }
  cout << endl;
}

void EAS::init_phers() {
  for(int i = 0; i < num_cities; ++i)
    for(int j = 0; j < i; ++j)
      pheromones[i][j] = tau_0;
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
  //  cout << "a" << endl;

  //  cout << "b" << endl;
}

void EAS::pheromone_update() {
  //evaporate all pheremones
  for(int i = 0; i < num_cities; i++)
    for(int j = 0; j < i; j++)
      pheromones[i][j] = (1-evap_rate)*pheromones[i][j];

  regular_ant_contribution(); // add pheremones from every ant
  best_ant_contribution();    // additional pheremone from best ant
}

void EAS::regular_ant_contribution() {
  //for each ant
  for(int i = 0; i < colony_size; i++) {
    Ant curr_ant = colony[i]; //not the fruit

    //for each leg in its tour
    for(int j = 0; j < num_cities; j++) {
      int city_A = curr_ant.tour[i];
      int city_B = curr_ant.tour[i+1];

      add_pheremone(city_A, city_B, 1/curr_ant.length);
    }
  }
}

void EAS::best_ant_contribution() {
  for(int i = 0; i < num_cities; i++) {
    int city_A = best_ant.tour[i];
    int city_B = best_ant.tour[i+1];

    add_pheremone(city_A, city_B, elitism_factor*1/best_ant.length);
  }
}

void EAS::add_pheremone(int city_A, int city_B, double quantity) {
    //Ensures city_A > city_B
    if(city_A < city_B) {
      int tmp = city_A;
      city_A = city_B;
      city_B = tmp;
    }

    pheromones[city_A][city_B] += quantity;
}
// int EAS::loop_list(int i, int list_size) {
//   if(0 > i) return list_size - 1;
//   return i%list_size;
// }

void EAS::update_best_ant() {
  for(int i = 0; i < colony_size; i++) {
    //    cout << "len: " << colony[i].length << endl;
    if(colony[i].length < best_ant.length) {
      best_ant = colony[i];
    }
  }

  cout << "best ant len: " << best_ant.length << endl;
}
