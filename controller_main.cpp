// Problem link: 
// LINK
// Ishan Bhatt DATE

#include"floyd_warshall.cpp"
#include"dijkstra.cpp"

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
        cout << "Running Floyd-Warshall"<< endl;
        fw = true;
    }
    else if(algo.compare("d") == 0){
        cout << "Running Dijkstra"<< endl;
        d = true;
    }
    else{
        cout << "Only Dijkstra(d) and Floyd-Warshall(fw) are supported" << endl;
        return -1;
    }

    vector<vector<int>> G = createGraph(input_file);
    
    cout << "Input Graph Adj. Matrix:";
    printGraph(G);

    if(fw){
        
        clock_t start = clock();
        int fw_comparisions = implementFloydWarshall(G);
        clock_t end = clock();

        clock_t fw_time = double(end-start)/ double(CLOCKS_PER_SEC);

        cerr << "runtime\t" << fw_time << endl;
        cerr << "comparisions\t" << fw_comparisions << endl;
    }

    else{
        clock_t start = clock();
        int dj_comparisions = implementDijkstra(G);
        clock_t end = clock();

        clock_t dj_time = double(end-start)/ double(CLOCKS_PER_SEC);

        cerr << "runtime\t" << dj_time << endl;
        cerr << "comparisions\t" << dj_comparisions << endl;
    }




	// cout << "You've entered " << argc << " clis\n";

    return 0;
}