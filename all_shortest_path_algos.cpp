#include"dependencies.h"

void implementFloydWarshall(vector<vector<long>> G, clock_t* time_taken, int* num_comparisions){

    // cout << "Before FloydWarshall:" << endl;
    // printGraph(G);
    clock_t start = clock();

    int n = G.size();
    int comparisions = 0;



    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(!(G[i][k] == INT_MAX || G[k][j] == INT_MAX)){ 
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                    comparisions++;
                }
            }
        }
    }

    clock_t end = clock();

    clock_t d_time = double(end-start)/ double(CLOCKS_PER_SEC/(1000));
    
    cerr << d_time << endl;
    cout << n << endl;
    for(int i = 0; i< n; i++){
        for(int j=0; j<n; j++){
            if(G[i][j] >= INT_MAX)
                cout << "-1" << endl;
            else
                cout << G[i][j] << endl;
        }        
        if(i != n-1)
            cout << "-1" << endl;
    }


    // cout << "After FloydWarshall:" << endl;
    // printGraph(G);

    *num_comparisions = comparisions;
    *time_taken = d_time; 
}


// Implements the Dijkstra Algorithm for a given graph and source vertex
void implementDijkstra(vector<vector<long>> G, int src, clock_t* time_taken, int* num_comparisions){


    int V = G.size();
    int djk_comps = 0;

    // Initialize MinHeap/PriorityQueue
    MinHeap pq(V);


    vector<long> dist(V, INT_MAX);
    clock_t start = clock();
    
    // Insert Source node to the PriorityQueue
    pq.insertKey(make_pair(0, src));
    dist[src] = 0;
  
    // Insert the rest of nodes with a weight of INT_MAX
    for(int i = 0; i<V; i++){
        if(i != src){
            pq.insertKey(make_pair(INT_MAX, i));
        }
    }


    while (!pq.isEmpty()){

        // Extract the first element from the priority queue
        int u = pq.extractMin().second;

        // Check all nodes connected to u and relax edges
        for (int i = 0; i != G[u].size(); ++i)
        {
            int v = i;
            long weight = G[u][i];

            if (weight != INT_MAX && dist[v] > dist[u] + weight)
            {
                djk_comps++;
                dist[v] = dist[u] + weight;
                pq.decreaseKey(i, dist[v]);
            }
        }
    }

    clock_t end = clock();

    clock_t d_time = double(end-start)/ double(CLOCKS_PER_SEC/(1000));
    
    *time_taken = d_time;
    *num_comparisions = djk_comps + pq.getComparisions();
    
    // Print shortest distances stored in dist[]
    if(src == 0)
        cout<<V<<endl;
    for (int i = 0; i < V; ++i){
        if (dist[i] >= INT_MAX)
            cout<<"-1"<<endl;
        else
            cout<<dist[i]<<endl;
    }
    if(src != V-1){
        cout<<"-1"<<endl;
    }
}

