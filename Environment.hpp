#ifndef ENVCLASS
#define ENVCLASS

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <tuple>
#include <vector>

using namespace std;

class Environment{
    public:
        Environment();
        // read map returns a list of possible states!
        void read_map(string filename);
        vector<int> get_nonterminal();
        pair<int,int> NtoXY(int state);
        int XYtoN(int x, int y);
        char query_state(int state);
        pair<int,pair<int,int> > take_action(int act);
        int reset();
        int get_reward(int state);
        pair<int,int> get_dimensions();
        ~Environment();
    private:
        int n_lin;
        int n_col;
        vector<int> nonterminal_states;
        char** map;
        pair<int,int> current_state;
};

#endif
