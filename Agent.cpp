#include "Agent.hpp"

Agent::Agent(string map_name, double gamma, double alpha, double epsilon){
    env.read_map(map_name);
    this->nonterminals = env.get_nonterminal();
    for (int i=0; i<this->nonterminals.size(); i++){
        this->map_nonterminals.insert({this->nonterminals[i],i});
    }

    this->gamma = gamma;
    this->alpha = alpha;
    this->epsilon = epsilon;
}

// tries to approximate the optimal Q(s,a) values by using
// an epsilon-greedy approach to explore/exploit
void Agent::train(int N){
    int state_n = env.reset();
    pair<int,int> state = env.NtoXY(state_n);
    this->current_state = state;
    for (int s=0; s<this->nonterminals.size(); s++){
        vector<double> this_line;
        for (int a=0; a<4; a++){
            double init_Q = 0;
            this_line.push_back(init_Q);
        }
        q_values.push_back(this_line);
    }
    double mult = 1;
    for (int step=0; step<N; step++){
        cout << "Step: " << step << "\n";
        cout << "\tCurrent state: " << this->current_state.first << " " << this->current_state.second << "\n";
        int act = choose_action();
        cout << "\tAction: " << act << "\n";
        pair<int,pair<int,int> > result = env.take_action(act);
        int next_state = result.second.second;
        int reward = result.second.first;
        int isTerminal = result.first;
        cout << "\tNext state: " << next_state << "\n\tReward: " << reward << "\n\tisTerminal: " << isTerminal << "\n\n";
        update_q(act, reward, next_state, mult);
        
        if (isTerminal){
            next_state = env.reset();
            cout << "\tReached terminal!\n";
        }
        
        pair<int,int> next_coords = env.NtoXY(next_state);
        this->current_state = next_coords;
        mult *= this->gamma;
    }
}

void Agent::update_q(int action, int reward, int next_state, double mult){
    int state_n = env.XYtoN(this->current_state.first, this->current_state.second);
    unordered_map<int,int>::iterator find_state = this->map_nonterminals.find(state_n); 
    int state_entry = find_state->second;
    double q_value = this->q_values[state_entry][action];


    
    
    double max_q = -1000;
    if (reward == -1){
        unordered_map<int,int>::iterator find_next_state = this->map_nonterminals.find(next_state);
        int next_state_entry = find_next_state->second;
        for (int a=0; a<4; a++){
            if (this->q_values[next_state_entry][a] > max_q){
                max_q = this->q_values[next_state_entry][a];
            }
        }
    }
    else{
        max_q = 0;
    }

    this->q_values[state_entry][action] = (1-this->alpha)*q_value + this->alpha*(((double) reward) + (this->gamma*max_q));

}

void Agent::print_results(){
    ofstream fpi("./pi.txt");
    
    pair<int,int> dims = env.get_dimensions();
    for (int lin=0; lin<dims.first; lin++){
        for (int col=0; col<dims.second; col++){
            int state_n = env.XYtoN(lin,col);
            char obs = env.query_state(state_n);
            if (obs == '-'){
                unordered_map<int,int>::iterator find_state = this->map_nonterminals.find(state_n);
                int state_entry = find_state->second;
                int act;
                double max_q = -1000;
                for (int a=0; a<4; a++){
                    double this_q = this->q_values[state_entry][a];
                    if (this_q > max_q){
                        max_q = this_q;
                        act = a;
                    }
                }
                char best_act;
                if (act == 0)   best_act = '^';
                else if (act == 1)  best_act = '>';
                else if (act == 2)  best_act = 'v';
                else if (act == 3)  best_act = '<';
                else    best_act = '-';
                
                fpi << best_act;
            }
            else{
                fpi << obs;
            }
        }
        fpi << "\n";
    }

    ofstream fq("./q.txt");
    
    vector<int> nonterms = env.get_nonterminal();

    for (int s=0; s<nonterms.size(); s++){
        for (int a=0; a<4; a++){
            int state_n = nonterms[s];
            pair<int,int> coords = env.NtoXY(state_n);
            fq << coords.first << "," << coords.second << ",";
            if (a == 0) fq << "acima,";
            else if (a == 1)    fq << "direita,";
            else if (a == 2)    fq << "abaixo,";
            else if (a == 3)    fq << "esquerda,";

            fq << this->q_values[s][a] << "\n";
        }
    }

    fq.close();
    fpi.close();
}

int Agent::choose_action(){
    double randnum = ((double) rand())/RAND_MAX;
    int chosen = 0;
    if (randnum < this->epsilon){
        chosen = rand() % 4;
    }
    else{
        int state_n = env.XYtoN(this->current_state.first, this->current_state.second);
        unordered_map<int,int>::iterator find_state = this->map_nonterminals.find(state_n); 
        int state_entry = find_state->second;
        double max = -1000;
        for (int a=0; a<4; a++){
            if (this->q_values[state_entry][a] >= max){
                chosen = a;
                max = this->q_values[state_entry][a];
            }
        }
    }
    return chosen;
}

