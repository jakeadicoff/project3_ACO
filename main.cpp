#include "main.h"


using namespace std;



int main(int argc, char** argv) {
    string ant_system = argv[1];
    string problem_file_name = argv[2];
    
    double alpha, beta, evap_rate, epsilon, tau_0, q_0, elitism;
    int colony_size, num_iterations;
    
    colony_size = 20;
    alpha = 1;
    beta = 3;
    evap_rate = 0.1;
    elitism = colony_size;
    epsilon = 0.1;
    tau_0 = 1; //actually set this in constructor, so this is a placeholder
    q_0 = 0.9;
    num_iterations = 100;
    
    //process file and get pointer to vector of clauses
    Cities tsp = readFile(problem_file_name);
    //num_cities = tsp.positions.size();
    
    cout << "******************************************" << endl;
    cout << " File name: " << problem_file_name << endl;
    if (ant_system == "EAS") {
        EAS eas_alg(alpha, beta, evap_rate, colony_size, num_iterations, tsp, elitism, tau_0);
        
        eas_alg.run_eas();
    }
    else if (ant_system == "ACS") {
        ACS acs_alg(alpha, beta, evap_rate, colony_size, num_iterations, tsp, tau_0, epsilon, q_0);
        cout << "ACS constructed" << endl;
        acs_alg.runACS();
    }
    cout << "******************************************" << endl;
    return 0;

    //cities = readFile("a280.tsp");
    //cout << cities[0][0] << cities [0][1] << endl;
    //test_prob();
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



