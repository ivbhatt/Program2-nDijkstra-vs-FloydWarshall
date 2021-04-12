#include<iostream>
#include<fstream>
#include<sstream>
#include<istream>
#include<iterator>
#include<vector>

using namespace std;


void printGraph(vector<vector<int>> G){
    for(int i = 0; i < G.size(); i++){
        for(int j = 0; j < G[0].size(); j++ )
            cout<<setw(10)<<right<<G[i][j]<<" ";
        cout<<endl;
    }
}

vector<vector<int>> createGraph(string filename){
    vector<vector<int>> Graph;

    fstream newfile;
    newfile.open(filename,ios::in); //open a file to perform read operation using file object

    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        getline(newfile, tp);
        getline(newfile, tp);
        stringstream ss(tp);
        istream_iterator<std::string> begin(ss);
        istream_iterator<std::string> end;
        vector<string> vstrings(begin, end);

        // Extract  number of vertices and edges
        int V = stoi(vstrings[1]);
        int E = stoi(vstrings[2]);
        vector<vector<int>> G (V, vector<int> (V));

        for(int i=0; i<V; i++){
            for(int j=0; j<V; j++){
                if(i==j)
                    G[i][j] = 0;
                else
                    G[i][j] = INT_MAX;
                    // G[i][j] = numeric_limits<int>::max();
            }
        }

        // Extract edges sources, destinations and weights
        int e = 0;
        while(e < E && getline(newfile, tp)){ //read data from file object and put it into string.
            stringstream ss(tp);
            istream_iterator<std::string> begin(ss);
            istream_iterator<std::string> end;
            vector<string> vstrings(begin, end);

            // Process String stored in tp
            if(vstrings[0] == "e"){
                int u = stoi(vstrings[1]) - 1;
                int v = stoi(vstrings[2]) - 1;
                int w = stoi(vstrings[3]);
                G[u][v] = w;
                e++;
            }
        }
        Graph = G;
        newfile.close(); //close the file object.
    } 
    return Graph;
}

// int main(){

//     string fname = "dual_8_12-normalized.gph";
//     vector<vector<int>> G = createGraph(fname);
//     printGraph(G);
//     return 0;
// }
