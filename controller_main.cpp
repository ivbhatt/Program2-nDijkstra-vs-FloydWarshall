// Problem link: 
// LINK
// Ishan Bhatt DATE

#include"all_shortest_path_algos.cpp"

using namespace std;

int main(int argc, char* argv[]){

    if (argc != 3){
        cout << "This program takes 2 CLIs- 1: [d/fw] 2:[input_filename]" << endl;
        return -1;
    }

    string algo = argv[1];
    string input_file = argv[2];
    bool fw = false, d = false;

    if(algo.compare("fw") == 0){
        // cout << "Running Floyd-Warshall"<< endl;
        fw = true;
    }
    else if(algo.compare("d") == 0){
        // cout << "Running Dijkstra"<< endl;
        d = true;
    }
    else{
        cout << "Only Dijkstra(d) and Floyd-Warshall(fw) are supported" << endl;
        return -1;
    }

    vector<vector<long>> G = createGraph(input_file);
    


    if(fw){
        
        clock_t start = clock();
        int fw_comparisions = implementFloydWarshall(G);
        clock_t end = clock();

        clock_t fw_time = double(end-start)/ double(CLOCKS_PER_SEC);

        cerr << "runtime\t" << fw_time << endl;
        cerr << "comparisions\t" << fw_comparisions << endl;
    }

    else{
        clock_t dj_time = 0;
        int dj_comparisions = 0;
        for(int i=0; i<G.size(); i++){
            int temp_comparisions;
            clock_t temp_time;
            implementDijkstra(G, i ,&temp_time, &temp_comparisions);

            // cout << temp_time << endl;
            dj_time += temp_time;
            dj_comparisions += temp_comparisions;

            // cout << temp_time << "\t" << temp_comparisions << endl; 
        }

        cerr << "runtime\t" << (dj_time * 1000)<< endl;
        cerr << "comparisions\t" << dj_comparisions << endl;
    }




	// cout << "You've entered " << argc << " clis\n";

    return 0;
}