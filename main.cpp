#include <iostream>
#include <vector>

#include "Environment.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Environment env;
    vector<int> aaa = env.read_map("maps/pacmaze-01-tiny.txt");
    //for (int i=0; i<(7*14-1); i++)  cout << env.query_state(i);
    return 0;
}
