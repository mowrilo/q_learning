#include "Environment.hpp"

using namespace std;

Environment::Environment(){
    srand(20); // initialize seed
}

void Environment::read_map(string filename){
    ifstream f(filename);
    int lin,col;
    f >> lin >> col;
    string line;
    this->n_lin = lin;
    this->n_col = col;
    this->map = new char*[lin];    
    vector<int> nterminal_states(10);
    getline(f,line);
    for (int n_line=0; n_line<lin; n_line++){
        getline(f,line);
        this->map[n_line] = new char[col];
        for (int nc=0; nc<col; nc++)    this->map[n_line][nc] = line[nc];
        for (int n_column=0; n_column<col; n_column++){
            if (line[n_column] == '-'){
                int this_state = XYtoN(n_line,n_column);
                this->nonterminal_states.push_back(this_state);
            }
        }
    }
    f.close();
}

vector<int> Environment::get_nonterminal(){
    return this->nonterminal_states;
}

// x is the number of the line, y is the number of the column
int Environment::XYtoN(int x, int y){
    return x* this->n_col + y;
}

pair<int,int> Environment::NtoXY(int state){
   int x = state/this->n_col;
   int y = state % this->n_col;
   return make_pair(x,y);
}

char Environment::query_state(int state){
    if (state < 0)  return '#';
    if (state > (this->n_lin*this->n_col - 1))    return '!';
    pair<int,int> xy = NtoXY(state);
    return this->map[xy.first][xy.second];
}

pair<int,int> Environment::get_dimensions(){
    return {this->n_lin, this->n_col};
}

// Returns the triple (isTerminal, reward, next state)
// action maps: 
//      up: 0
//      right: 1
//      down: 2
//      left: 3
pair<int,pair<int,int> > Environment::take_action(int act){
    int rew = 0;
    pair<int,int> new_state = current_state;
    int isTerminal = 0;
    if (act == 0){
        new_state.first--;
        int new_state_int = XYtoN(new_state.first, new_state.second);
        if (query_state(new_state_int) == '#'){
            new_state = current_state;
        }
        new_state_int = XYtoN(new_state.first, new_state.second);
        rew = get_reward(new_state_int);
        if (rew == 10 || rew == -10)    isTerminal = 1;
    }
    else if (act == 1){
        new_state.second++;
        int new_state_int = XYtoN(new_state.first, new_state.second);
        if (query_state(new_state_int) == '#'){
            new_state = current_state;
        }
        new_state_int = XYtoN(new_state.first, new_state.second);
        rew = get_reward(new_state_int);
        if (rew == 10 || rew == -10)    isTerminal = 1;
    }
    else if (act == 2){
        new_state.first++;
        int new_state_int = XYtoN(new_state.first, new_state.second);
        if (query_state(new_state_int) == '#'){
            new_state = current_state;
        }
        new_state_int = XYtoN(new_state.first, new_state.second);
        rew = get_reward(new_state_int);
        if (rew == 10 || rew == -10)    isTerminal = 1;
    }
    else if (act == 3){
        new_state.second--;
        int new_state_int = XYtoN(new_state.first, new_state.second);
        if (query_state(new_state_int) == '#'){
            new_state = current_state;
        }
        new_state_int = XYtoN(new_state.first, new_state.second);
        rew = get_reward(new_state_int);
        if (rew == 10 || rew == -10)    isTerminal = 1;
    }
    else{
        cout << "You took a forbidden action! You should be penalized for that!\n";
        rew = -100;
    }
    this->current_state = new_state;
    int next_state = XYtoN(new_state.first, new_state.second);
    return make_pair(isTerminal,make_pair(rew, next_state));
}

int Environment::get_reward(int state){
    char state_obs = query_state(state);
    if (state_obs == '-')   return -1;
    else if (state_obs == '0')  return 10;
    else if (state_obs == '&')  return -10;
    return 0;
}

// Generates a random state for the agent to start
int Environment::reset(){
    int num_of_nonterminal = this->nonterminal_states.size();
    int new_state = rand() % num_of_nonterminal;
    new_state = this->nonterminal_states[new_state];
    this->current_state = NtoXY(new_state);
    return new_state;
}

Environment::~Environment(){
    for (int i=0; i<this->n_lin; i++)   delete[] this->map[i];
    delete[] this->map;
}
