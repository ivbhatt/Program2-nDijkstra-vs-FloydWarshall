#include"all_shortest_path_algos.cpp"
#include <iomanip>

using namespace std;

int main(int argc, char* argv[]){

    // First check if proper CLIs are supplied (3 additional command lines are expected and required) 
    if (argc != 4){
        cerr << "This program takes 3 CLIs- 1: [d/fw] 2:[input_filename] 3:[D for D-heap dijkstra]" << endl;
        return -1;
    }

    // Storing the CLIs
    string algo = argv[1];
    string input_file = argv[2];
    int D = atoi(argv[3]);
    bool fw = false, d = false;


    // choose algorithm
    if(algo.compare("fw") == 0)
        fw = true;
    else if(algo.compare("d") == 0)
        d = true;
    else{
        cout << "Only Dijkstra(d) and Floyd-Warshall(fw) are supported" << endl;
        return -1;
    }


    // utility function to represent graph in Adjacency Matrix reading it from a gph-file
    vector<vector<long>> G = createGraph(input_file);


    if(fw){

        // place holders to store run-time and num_comparisions
        double fw_time;
        int fw_comparisions;

        implementFloydWarshall(G, &fw_time, &fw_comparisions);

        cerr << "runtime\t" << setprecision(1) << double(fw_time/1000) << endl;
        cerr << "comparisions\t" << fw_comparisions << endl;
    }

    else{
        // place holders to store run-time and num_comparisions

        double dj_time = 0;
        int dj_comparisions = 0;
        for(int i=0; i<G.size(); i++){
            int temp_comparisions = 0;
            double temp_time;
            implementDijkstraDHeap(G, i ,&temp_time, &temp_comparisions, D);

            dj_time += temp_time;
            dj_comparisions += temp_comparisions;
            break;
        }

        cerr << "runtime\t" << fixed << setprecision(1) << double(dj_time / 1000)<< endl;
        cerr << "comparisions\t" << dj_comparisions << endl;
        
    }

    return 0;
}
