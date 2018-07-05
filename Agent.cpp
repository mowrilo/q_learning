#include "Agent.hpp"

Agent::Agent(string map_name, double gamma, double alpha, double epsilon){
    env.read_map(map_name);
    this->gamma = gamma;
    this->alpha = alpha;
    this->epsilon = epsilon;
}

// tries to approximate the optimal Q(s,a) values by using
// an epsilon-greedy approach
void Agent::train(int N){
    vector<int> nonterminals = env.get_nonterminal();
    int state_n = env.reset();
    pair<int,int> state = env.NtoXY(state_n);
    this->current_state = state;
    for (vector<int>::iterator it=nonterminals.begin(); it!=nonterminals.end(); it++){
        map<int,double> this_aqmap;
        for (int a=0; a<4; a++){
            double init_Q = (rand()/RAND_MAX * 20) - 10;
            this_aqmap.insert({a,init_Q});
        }
        q_values.insert({*it,this_aqmap});
    }
}
