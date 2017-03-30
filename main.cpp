#include "main.h"

using namespace std;


int main(int argc, char** argv) {
    cout << "hello world" << endl;
    
    vector<vector<double>> cities;
    cities = readFile("a280.tsp");
    cout << cities[0][0] << cities [0][1] << endl;
    
}

vector <vector<double> > readFile(string problem_file_name) {
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
    while(problem_stream.peek()!=EOF) {
        problem_stream.ignore(big_int, 'N'); //jump to where line starts with p
        char curr_line[100];
        problem_stream.getline(curr_line, 100);
        cout << curr_line << endl;
        line = curr_line;
        
        if(line.substr(0, 4).compare("ODE_") == 0) {
            cout << "header found" << endl;
            break;
        }
    }
    
    istringstream iss(line);
    iss.ignore(big_int, 'N'); //jump to after 'NODE_COORD_SECTION' in same line
    
    problem_stream >> next_item_in_stream; //to first literal in first clause
    cout << next_item_in_stream << endl;
    
    while(problem_stream.peek()!=EOF) { //run until end of file
        vector <double> city; //make clause vectore to hold literals
        
        // skip city #
        problem_stream >> next_item_in_stream;
        
        if(next_item_in_stream.substr(0, 3).compare("EOF") == 0) {
            break;
        }
        for(int i = 0; i < 2; ++i) { //run until end of line
            cout << next_item_in_stream << endl;
            city.push_back(stod(next_item_in_stream));
            problem_stream >> next_item_in_stream;
        }
        vector_of_cities.push_back(city);
        city.clear();
        //problem_stream >> next_item_in_stream; //advance past "0"
    }
    cout << "numcities " << vector_of_cities.size()  << endl;
    //return address
    
    cout << "end of debug for file parsing" << endl;
    
    return vector_of_cities;
}
