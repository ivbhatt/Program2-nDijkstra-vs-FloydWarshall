#include"dependencies.h"

int implementFloydWarshall(vector<vector<long>> G){

    cout << "Before FloydWarshall:" << endl;
    printGraph(G);

    int n = G.size();
    int comparisions = 0;

    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(!(G[i][k] == INT_MAX || G[k][j] == INT_MAX)){ 
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                }
                comparisions++;
            }
        }
    }


    cout << "After FloydWarshall:" << endl;
    printGraph(G);

    return comparisions;
}



void implementDijkstra(vector<vector<long>> G, int src, clock_t* time_taken, int* num_comparisions){


    int V = G.size();
    int djk_comps = 0;
    MinHeap pq(V);

    vector<long> dist(V, INT_MAX);

    clock_t start = clock();
    
    pq.insertKey(make_pair(0, src));
    dist[src] = 0;
  
    for(int i = 0; i<V; i++){
        if(i != src){
            pq.insertKey(make_pair(INT_MAX, i));
        }
    }

    while (!pq.isEmpty()){

        int u = pq.extractMin().second;

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

    clock_t d_time = double(end-start)/ double(CLOCKS_PER_SEC/(1000*1000));
    
    *time_taken = d_time;
    *num_comparisions = djk_comps + pq.getComparisions();
    
    // Print shortest distances stored in dist[]
    // for (int i = 0; i < V; ++i){
    //     cout<<dist[i]<<endl;
    // }
}

