#include "AC.h"

AntSystem::AntSystem(double a, double b,double e, int colonySize,
	  int numIterations, vector<vector<double>> cityDistances, double tau_0) {
  this->alpha = a; //scaling factor
  this->beta = b;  //scaling factor
  this->evap_rate = e;
  this->colony_size = colonySize;
  this->num_iterations = numIterations;
  this->num_cities = cityDistances.size();
  

  vector<vector <double > > ps; //dummy vector - pheremones
  vector<vector <double > > ds; //dummy vector - distances
  Result data;
  Ant dummy_ant;
  vector<Ant> dummy_colony(colony_size, dummy_ant);
  this->colony = dummy_colony;

  this->results = data;
  this->dists = cityDistances;
  this->pheromones = ps;
    init_0_phers();
  dummy_ant.length = MAX_DOUBLE;
  this->best_ant = dummy_ant;
}

/*
void AntSystem::make_ants() {
  for(int i = 0; i < colony_size; ++i) {
    Ant new_ant;
    colony.push_back(new_ant);
  }
}
*/

void AntSystem::init_0_phers(){
    pheromones.clear();
    vector<double> row;
    for(int i = 0; i < num_cities; i++) {
        row.clear();
        for(int j = 0; j < i; j++) {
            row.push_back(0);
        }
        pheromones.push_back(row);
    }
}

/**
 * Resets all of the ant's variables
 */
void AntSystem::clear_ants() {
  for(int i = 0; i < colony_size; i++) {
    colony[i].tour.clear();
    colony[i].length = 0;

    // set every city to unvisited
    vector<bool> true_vec(num_cities, true);
    colony[i].unvisited = true_vec;
  }
}


double AntSystem::lookup_dist(int i, int j) {
  if( i > j) return dists[i][j];
  return dists[j][i];
}

//Ensures larger index comes first during lookup
double AntSystem::lookup_pher(int i, int j) {
  if( i > j) return pheromones[i][j];
  return pheromones[j][i];
}

/**
 * Executes the selection for probabilistically choosing the next city
 * to add a SINGLE ants' tour. The probability is PROPORTIONAL to the
 * PHEREMONE LEVEL on the path, and the INVERSELY proportional to
 * DISTANCE.
 *
 * The probabilities are normalized.
 *
 * This method is always used in tour building for Elitist Ant System,
 * and used with a probability (usually 0.1) in Ant Colony System.
 */
void AntSystem::probabilistic_next_step(int ant_index) {
  int curr_city = colony[ant_index].tour.back();

  //to feed into the discrete_distribution. Will have the correct
  //weight (based on dist, pheremone) if unvisited, ZERO if visited
  vector<double> probability_vector;

  for(int i = 0; i < num_cities; i++ ) {
    double weight = 0;
    // if city is unvisited update, selection weight to be NON ZERO
    if(colony[ant_index].unvisited[i]) {
        double pher = pow(lookup_pher(colony[ant_index].last(),i),alpha);
        double dist = pow(1/(lookup_dist(colony[ant_index].last(),i)),beta);
        //cout << "Dist: " << dist << ", Pher: " << pher << endl;
        weight = pher * dist;
        //cout << weight << endl;
    }
    probability_vector.push_back(weight);
  }

  //@TODO: this line may only need to be used once, i forget CHECK IT
  default_random_engine generator;
  // black box
  discrete_distribution<double> distribution
    (probability_vector.begin(),probability_vector.end());

  //Selects the next city based on the given weights! Magic!! Wow!
  int next_city = distribution(generator);

  // update the ant's tour and unvisited vector
  colony[ant_index].unvisited[next_city] = false;
  colony[ant_index].tour.push_back(next_city);
  colony[ant_index].length += lookup_dist(curr_city,next_city);
  // that was neat
}

/**
 * Selects the next city simply by taking the nearest unvisited city.
 * Necessary to set initial pheremone levels, tau_0
 */
double AntSystem::length_nn() {
  Ant nn_ant;
  vector<bool> ones(num_cities, true);
  nn_ant.unvisited = ones;
  nn_ant.tour.push_back(0);
  nn_ant.unvisited[0] = false;
  int curr_city = 0;

  for(int i = 0; i < num_cities - 1; i++) {
    int nearest_city;
    double dist_to_nearest_city = MAX_DOUBLE;

    //Keep searching for the closest city, from the most recent city
    for(int j = 0; j < num_cities; j++) {
      if(nn_ant.unvisited[j]) {

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

  // go home (cyclical tour)
  nn_ant.tour.push_back(0);
  nn_ant.length += dists[curr_city][0];

  return nn_ant.length;
}

