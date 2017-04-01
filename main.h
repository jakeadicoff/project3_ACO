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



using namespace std;

vector <vector<double> > readFile(string problem_file_name);
void test_prob();

#endif
