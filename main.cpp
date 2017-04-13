#include "main.h"

using namespace std;

int main(int argc, char** argv) {
  string ant_system = argv[1];
  string problem_file_name = argv[2];

  double alpha, beta, evap_rate, epsilon, tau_0, q_0, elitism;
  int colony_size, num_iterations, num_cities;


  //process file and get pointer to vector of cities
  Cities tsp = readFile(problem_file_name);
  num_cities = tsp.positions.size();
  vector<vector<double>> cityDistances = init_dists(tsp, num_cities);
  string input;
  cout << "run all tests? (y / n)" << endl;
  cin >> input;
  if(input == "n") {

    cout << "******************************************" << endl;
    cout << " File name: " << problem_file_name << endl;
    if (ant_system == "EAS") {
      //@TODO: Make these into parameters
      alpha = 1;
      beta = 3;
      evap_rate = 0.5;
      colony_size = num_cities;
      elitism = colony_size;
      tau_0 = -4242424242424; //actually set this in constructor, so this is a placeholder
      num_iterations = 10;
      
      EAS eas_alg(alpha, beta, evap_rate, colony_size, num_iterations, cityDistances, elitism, tau_0);
      Result results = eas_alg.run_eas();
    }
    else if (ant_system == "ACS") {
      //@TODO: Make these into parameters
      colony_size = num_cities;
      alpha = 1;
      beta = 3;
      evap_rate = 0.99;
      epsilon = 0.1;
      tau_0 = -4242242424; //actually set this in constructor, so this is a placeholder
      q_0 = 0.9;
      num_iterations = 10;
      
      ACS acs_alg(alpha, beta, evap_rate, colony_size, num_iterations, cityDistances, tau_0, epsilon, q_0);
      cout << "ACS constructed" << endl;
      Result results = acs_alg.runACS();
    }
    cout << "******************************************" << endl;
  }
  else {
    string acs_filename, eas_filename;
    ofstream eas_output_file;
    ofstream acs_output_file;
    cout << "name eas file (with .csv): " << endl;
    cin >> eas_filename;
    cout << "name acs file (with .csv): " << endl;
    cin >> acs_filename;
    // header for output files
    string eas_output_string = "EAS\nbeta,evap,elitism,avg time,avg dist,avg iter\n";
    string acs_output_string = "ACS\nbeta,evap,q_0,avg time,avg dist,avg iter\n";
    // general params for both algs
    tau_0 = -4242242424; //actually set this in constructor, so this is a placeholder
    num_iterations = 100; // ????
    alpha = 1;
    // specific for EAS
    colony_size = 10;
    
    for(int i = 0; i < 3; i++) { // vary beta
      for(int j = 0; j < 3; j++) { // vary evap
	for(int k = 0; k < 3; k++) { // vary elitism
	  // set params for testing     
	  beta = i*3+3;
	  evap_rate = double(j)*2/10.0 + 0.3; // test values .3, .5, .7
	  elitism = (k+1)*(colony_size)/2;
	  double avg_dist = 0;
	  double avg_time = 0;
	  double avg_iter = 0;
	  for(int l = 0; l < 10; l++) { // 10 tests
	    EAS eas_alg(alpha, beta, evap_rate, colony_size, num_iterations, cityDistances, elitism, tau_0);
	    Result result = eas_alg.run_eas();
	    avg_dist += result.best_length;
	    avg_time += result.run_time;
	    avg_iter += double(result.iteration_of_best_ant);
	  }//10 tests
	  avg_dist = avg_dist/10;
	  avg_time = avg_time/10;
	  avg_iter = avg_iter/10;
	  eas_output_string = eas_output_string + to_string(beta) + "," + to_string(evap_rate) + "," +
	    to_string(elitism) + "," + to_string(avg_time) + "," + to_string(avg_dist) + "," +
	    to_string(avg_iter) + "\n";
	}// vary elitism
      } // vary evap
    } // vary beta
    eas_output_file.open(eas_filename);
    eas_output_file << eas_output_string;
    eas_output_file.close();

    // static parameters
    epsilon = 0.1;
    colony_size = 20;
    // tests
    for(int i = 0; i < 3; i++) {
      for(int j = 0; j < 3; j++) {
	for(int k = 0; k < 3; k++) {
	  beta = i*3+3;
	  evap_rate = double(j)/10.0 + 0.1; // test values .3, .5, .7
	  q_0 = .9 - double(k)/10.0;
	  double avg_dist = 0;
	  double avg_time = 0;
	  double avg_iter = 0;
	  for(int l = 0; l < 10; l++) { // 10 tests
	    ACS acs_alg(alpha, beta, evap_rate, colony_size, num_iterations, cityDistances, tau_0, epsilon, q_0);
	    Result result = acs_alg.runACS();
	    avg_dist += result.best_length;
	    avg_time += result.run_time;
	    avg_iter += double(result.iteration_of_best_ant);
	  }//10 tests
	  avg_dist = avg_dist/10;
	  avg_time = avg_time/10;
	  avg_iter = avg_iter/10;
	  acs_output_string = acs_output_string + to_string(beta) + "," + to_string(evap_rate) + "," +
	    to_string(q_0) + "," + to_string(avg_time) + "," + to_string(avg_dist) + "," +
	    to_string(avg_iter) + "\n";
	}
      }
    }
    acs_output_file.open(acs_filename);
    acs_output_file << acs_output_string;
    acs_output_file.close();
  }// end of else

  return 0;
}

Cities readFile(string problem_file_name) {

  Cities tsp;
  //item to return
  vector <vector<double> > vector_of_cities;
  //file stream initialization
  ifstream problem_stream;
  string num_clauses, num_literals;
  //hold iteam that was just pulled from the file stream
  string next_item_in_stream;
  //for advancing filestream
  int big_int = 100000;
  cout << "Start of debug for parsing" << endl;
  problem_stream.open(problem_file_name.c_str(), ios::in);
  if(!problem_stream.good()) { //open file stream
    cout << "Error: not able to open file" << endl;
  }
  // WILL NEED FIXING IN FILES WITH MORE WRITING AT BEGINING. WILL IGNORE TO FIRST 'p'

  string line;
  char curr_line[100];

  while(problem_stream.peek()!=EOF) {
    problem_stream.ignore(big_int, 'E'); //jump to where line starts with p
    problem_stream.getline(curr_line, 100);
    line = curr_line;

    if(line.substr(0, 4).compare("DGE_") == 0) {
      break;
    }
  }

  int string_index = 0;

  for(int i = 0; i - line.length(); ++i) {
    if(curr_line[i] == ':') {
      string_index = i;
    }
  }
  string_index = string_index + 2;

  string edge_weights = line.substr(string_index);
  cout << edge_weights << endl;

  if(edge_weights == "GEO") {
    tsp.coordinate_system = GEOGRAPHIC;
    cout << "GEO" << endl;
  }
  else {
    tsp.coordinate_system = EUCLIDEAN;
    cout << "EUC_2D" << endl;
  }


  while(problem_stream.peek()!=EOF) {
    problem_stream.ignore(big_int, 'N'); //jump to where line starts with p
    char curr_line[100];
    problem_stream.getline(curr_line, 100);
    line = curr_line;

    if(line.substr(0, 4).compare("ODE_") == 0) {
      break;
    }
  }

  //istringstream iss(line);
  //iss.ignore(big_int, 'N'); //jump to after 'NODE_COORD_SECTION' in same line

  problem_stream >> next_item_in_stream; //to first literal in first clause

  while(problem_stream.peek()!=EOF) { //run until end of file
    vector <double> city; //make clause vectore to hold literals

    // skip city #
    problem_stream >> next_item_in_stream;

    if(next_item_in_stream.substr(0, 3).compare("EOF") == 0) {
      break;
    }
    for(int i = 0; i < 2; ++i) { //run until end of line
      city.push_back(stod(next_item_in_stream));
      cout << next_item_in_stream << "\t";
      problem_stream >> next_item_in_stream;
    }
    cout << endl;
    vector_of_cities.push_back(city);
    city.clear();
    //problem_stream >> next_item_in_stream; //advance past "0"
  }
  cout << "Number of Cities: " << vector_of_cities.size()  << endl;
  //return address

  cout << "end of debug for file parsing" << endl;

  tsp.positions = vector_of_cities;

  return tsp;
}


/**
 * Distance and Pheremone tables fully populate a N by N array, such
 * that the distance from city A to B can be looked up in constant
 * time with dists[A][B], and similarly pheremones[A][B] for
 * pheremones.
 *
 * Only the "lower" half the of array is populated with the
 * information, so when the lookup is executed, the LARGER index
 * always needs to come first.
 */

vector<vector<double>> init_dists(Cities cities, int num_cities) {
  vector <double> row; //distance from A to B
  vector<vector<double>> dists;
  vector<vector<double>> cityLocations = cities.positions;
  
  switch(cities.coordinate_system) {
  case EUCLIDEAN:
    for(int i = 0; i < num_cities; i++) {
      row.clear();
      
      // each row is one column longer than the last one -- makes a
      // triangle, excluding the midline
      for(int j = 0; j < i; j++) {
	double dist_ij = euc_dist(cityLocations[i], cityLocations[j]);
	row.push_back(dist_ij);
      }
      
      dists.push_back(row);
    }
    break;
  case GEOGRAPHIC:
    for(int i = 0; i < num_cities; i++) {
      row.clear();
      for(int j = 0; j < i; j++) {
	double dist_ij = geo_dist(cityLocations[i], cityLocations[j]);
	row.push_back(dist_ij);
      }
      dists.push_back(row);
    }
    break;
  }
  return dists;
}


// Calculates 2D euclidean distance
double euc_dist(vector <double> a, vector <double> b) {
  return sqrt(pow(a[0]-b[0],2)+pow(a[1]-b[1],2));
}

// change this up
double geo_dist(vector <double> a, vector <double> b) {
  double global_lat1, global_lon1, global_lat2, global_lon2;
  global_lat1 = a[0];
  global_lon1 = a[1];
  global_lat2 = b[0];
  global_lon2 = b[1];
  
  //calculate distance in radians (check rad & deg conversion)
  double distance = sin(deg_to_rad(global_lat1)) *
    sin(deg_to_rad(global_lat2)) + cos(deg_to_rad(global_lat1)) *
    cos(deg_to_rad(global_lat2)) * cos(deg_to_rad(global_lon2 - global_lon1));
  
  //convert distance to degrees
  distance = rad_to_deg(distance);
  
  //convert degrees to kilometers on the surface of the earth
  distance = distance * 60 * 1.1515;
  distance = (6.371 * pi * distance)/180;
  
  return distance;
}

double rad_to_deg(double rad) {
  return (rad * 180 / pi);
};

double deg_to_rad(double deg) {
  return (deg * pi / 180);
};
