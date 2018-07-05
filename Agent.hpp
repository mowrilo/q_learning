#ifndef AGCLASS
#define AGCLASS

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Environment.hpp"

using namespace std;

class Agent{
    public:
        Agent(string map_name,double gamma, double alpha, double epsilon)
        void train(int N);
        void print_results();
    private:
        Environment env;
        double gamma;
        double alpha;
        double epsilon;
        // maps the state to each action and Q value
        unordered_map<int, map<int,double> > q_values;
        pair<int,int> current_state;

};

#endif
