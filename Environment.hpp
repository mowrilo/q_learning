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
        vector<int> read_map(string filename);
        pair<int,int> NtoXY(int state);
        int XYtoN(int x, int y);
        char query_state(int state);//int x, int y);
        pair<int,pair<int,int> > take_action(int act);
        int reset();
        int get_reward(int state);
        ~Environment();
    private:
        int n_lin;
        int n_col;
        vector<int> nonterminal_states;
        string* map;
        pair<int,int> current_state;
};
