#include "main.h"

using namespace std;

int main(int argc, char** argv) {
  string ant_system = argv[1];
  string problem_file_name = argv[2];

  double alpha, beta, evap_rate, epsilon, tau_0, q_0, elitism;
  int colony_size, num_iterations, num_cities;


  //process file and get pointer to vector of cities
  vector <vector<double> > cities = readFile(problem_file_name);
  num_cities = cities.size();

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
    num_iterations = 1000;

    EAS eas_alg(alpha, beta, evap_rate, colony_size, num_iterations,
		cities, elitism, tau_0);
    eas_alg.run_eas();
  }
  else if (ant_system == "ACS") {
    //@TODO: Make these into parameters
    colony_size = num_cities;
    alpha = 1;
    beta = 3;
    evap_rate = 0.99;
    elitism = colony_size;
    epsilon = 0.1;
    tau_0 = -4242242424; //actually set this in constructor, so this is a placeholder
    q_0 = 0.9;
    num_iterations = 1000;

    ACS acs_alg(alpha, beta, evap_rate, colony_size, num_iterations,
		cities, tau_0, epsilon, q_0);
    acs_alg.runACS();
  }
  cout << "******************************************" << endl;
  return 0;
}

/** Reads a .tsp file */
vector <vector<double> > readFile(string problem_file_name) {
  vector <vector<double> > vector_of_cities; //object to return
  ifstream problem_stream;    //file stream initialization
  string next_item_in_stream; //holds item that was just pulled from
                              //the file stream
  int big_int = 100000;       //for advancing filestream

  //open file stream
  problem_stream.open(problem_file_name.c_str(), ios::in);
  if(!problem_stream.good()) {
    cout << "Error: not able to open file" << endl;
  }

  string line;
  //Keep ignoring until the "NODE_COORD_SECTION" line
  while(problem_stream.peek()!=EOF) {
    problem_stream.ignore(big_int, 'N');
    char curr_line[100];
    problem_stream.getline(curr_line, 100);
    line = curr_line;

    //break once we find the appropriate line
    if(line.substr(0, 4).compare("ODE_") == 0) {
      break;
    }
  }

  //Loop through city coordinates
  while(problem_stream.peek()!=EOF) { //run until end of file
    vector <double> city; // Holds coordinates of the city

    problem_stream >> next_item_in_stream; //City ID value, discarded

    if(next_item_in_stream.substr(0, 3).compare("EOF") == 0) {
      break;
    }

    for(int i = 0; i < 2; ++i) { //get city X,Y coordinates
      problem_stream >> next_item_in_stream;
      city.push_back(stod(next_item_in_stream));
    }

    vector_of_cities.push_back(city);
    city.clear();
  }

  cout << "Number of Cities: " << vector_of_cities.size()  << endl;

  return vector_of_cities;
}
