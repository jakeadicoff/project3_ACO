#ifndef __main_h
#define __main_h

#include "AC.h"
#include "ACS.h"
#include "EAS.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <sstream>


enum Coordinates {GEOGRAPHIC, EUCLIDEAN};

struct Cities {
  vector<vector<double>> positions;
  Coordinates coordinate_system ;
};

Cities readFile(string problem_file_name);
double euc_dist(vector <double> a, vector <double> b);
vector<vector<double>> init_dists(Cities cities, int num_cities);
double euc_dist(vector <double> a, vector <double> b);
double geo_dist(vector <double> a, vector <double> b);
double rad_to_deg(double rad);
double deg_to_rad(double deg);

#endif
