// Your First C++ Program

#include <iostream>
#include <fstream>
#include <string>
#include <map>


using namespace std;

struct neighbor{
    int neighbor;
    int weight;
};

int main () {
    string line;
    ifstream myfile ("../Instances/rn.gph");

    map<int, neighbor> adj_map;

    adj_map.insert(pair<int, neighbor>(1, {1,2}));

    

    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }

    else cout << "Unable to open file"; 

    cout << adj_map[1].weight;

    return 0;
}