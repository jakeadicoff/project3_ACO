Elitist Ant System and Ant Colony System for TSP
Jake Adicoff, Malcolm Groves, Ethan Zhou

To run:
      1. make
      2. ./ACO ALG FILE
      	 (ALG must either be 'EAS' or 'ACS' and FILE must be in your local)
      3. Choose which tests to run as prompted
      

To change parameter settings for a single test, you must edit the main.cpp file. in main() you will see where to hard-code the values.

Bugs:
The code will seg fault if you try to run with more ants than cities. This is not a problem, since you should never need to do this.
