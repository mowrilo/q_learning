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
        Agent(string map_name,double gamma, double alpha, double epsilon);
        void train(int N);
        void print_results();
        int choose_action();
        void update_q(int action, int reward, int next_state, double mult);
    private:
        Environment env;
        double gamma;
        double alpha;
        double epsilon;
        vector<int> nonterminals;
        // maps each nonterminal state ID to the number of its row in the table
        unordered_map<int,int> map_nonterminals;
        // maps the state to each action and Q value
        vector<vector<double> > q_values;
        pair<int,int> current_state;

};

#endif
