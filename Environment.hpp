#include <fstream>
#include <string>
#include <utility>

class Environment{
    public:
        Environment();
        void read_map(string filename);
        char query_state(int x, int y);
        pair<int,int> take_action(int act);
        ~Environment();
    private:
        char** map;
        pair<int,int> current_state;
}
