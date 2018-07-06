#include <iostream>
#include <string>
#include <vector>

#include "Agent.hpp"
#include "Environment.hpp"

using namespace std;

int main(int argc, char* argv[]){    
    string map = argv[1];
    double alpha = atof(argv[2]);
    double gamma = atof(argv[3]);
    double epsilon = .001;
    int N = atoi(argv[4]);
    Agent a(map, gamma, alpha, epsilon);
    a.train(N);
    a.print_results();
    return 0;
}
