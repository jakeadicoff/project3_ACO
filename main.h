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
  Coordinates coodinate_system;
};

Cities readFile(string problem_file_name);
double euc_dist(vector <double> a, vector <double> b);

#endif
