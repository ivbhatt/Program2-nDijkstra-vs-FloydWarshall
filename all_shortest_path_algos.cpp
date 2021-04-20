#include"dependencies.h"

void implementFloydWarshall(vector<vector<long>> G, double* time_taken, int* num_comparisions){


//DEBUG
    // cout << "Before FloydWarshall:" << endl;
    // printGraph(G);

    clock_t start = clock();

    int n = G.size();
    int comparisions = 0;


    for(int k = 0; k < n; k++){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
//            There can never be a path from i to j (through k) if either i or j has no edge connecting them to k
                if(!(G[i][k] == INT_MAX || G[k][j] == INT_MAX)){ 
                    G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
                    comparisions++;
                }
            }
        }
    }

    clock_t end = clock();

    double d_time = double(end-start)/ double(CLOCKS_PER_SEC/(1000));
    
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

//DEBUG
    // cout << "After FloydWarshall:" << endl;
    // printGraph(G);

    *num_comparisions = comparisions;
    *time_taken = d_time; 
}


// Implements the Dijkstra Algorithm for a given graph and source vertex
void implementDijkstraDHeap(vector<vector<long>> G, int src, double* time_taken, int* num_comparisions, int D){

//DEBUG
    // cout << "Before Dijkstra:" << endl;
    // printGraph(G);

    cerr << "++++++++++++++++++++++" << endl;

    int V = G.size();
    int djk_edge_comparisons = 0;

    // Initialize MinHeap/PriorityQueue
    DMinHeap pq(D, V);


    vector<long> dist(V, INT_MAX);
    
    vector<bool> doneSet(V, false);

    clock_t start = clock();
    
    // Insert Source node to the PriorityQueue
    dist[src] = 0;
    pq.insertKey(make_pair(0, src));
     
    // Insert the rest of nodes with a weight of INT_MAX
//    for(int i = 0; i<V; i++){
//        if(i != src){
//            pq.insertKey(make_pair(INT_MAX, i));
//        }
//    }

    

    while (!pq.isEmpty()){

// Extract the first element from the priority queue

        pair<long, int> extracted_node = pq.extractMin();

        
        long u_dist = extracted_node.first;
        int u = extracted_node.second;

//        cerr << "Removed node:" << u_dist << " " << u << endl;

//        This node's best distance is found
        doneSet[u] = true;

   
        cerr<<"For vertex:" << u << endl;
//        cerr << "comparisions:" << pq.getComparisions() << endl;
//        cerr << djk_comps << endl;
            

// Check all nodes connected to u and relax edges
        for (int i = 0; i < V; ++i){
            
	        long weight = G[u][i];

// Of all neighbours, only consider neighbours whose best distance is not yet found
            if (weight != INT_MAX && doneSet[i] == false)
            {
//                cerr << "finding better path to:" << i <<  "from " << u <<endl;
		        djk_edge_comparisons++;
		        if(dist[i] > dist[u] + weight ){
                	if(dist[i] != INT_MAX){
//                	    cerr << "Updating node: "<< dist[i] <<  "  "<< i << " to  ";  

                	    dist[i] = dist[u] + weight;
//                	    cerr << dist[i] <<  "  "<< i << endl;  

                	    pq.decreaseKey(i, dist[i]);
                	}
                	else{
                	    dist[i] = dist[u] + weight;
//                	    cerr << "Inserting node: "<< dist[i] << "  "<< i << endl;

                	    pq.insertKey(make_pair(dist[i], i));

                	}
                	
		        }
            }
        }

//DEBUG
        
        cerr << "Heap comparisions:" << pq.getComparisions() << "\t";
        cerr << "Edge comparisions:" << djk_edge_comparisons << endl;
        
        cerr << "Calls to extractMin:" << pq.number_of_calls_to_ExtractMin << "\t";
        cerr << "total comparisons by extractMin:" << pq.total_comparisons_added_by_extractMin << "\t";
        cerr << "Max incr by extrMin:" << pq.max_comparisons_added_by_extractMin << "\n";
        
        cerr << "Calls to decreaseKey:" << pq.number_of_calls_to_DereaseKey << "\t";
        cerr << "total comparisons by decreaseKey:" << pq.total_comparisons_added_by_DecreaseKey << "\t";
        cerr << "Max incr by decreaseKey:" << pq.max_comparisons_added_by_DecreaseKey << "\n";
        
    }

    clock_t end = clock();

    double d_time = double(end-start)/ double(CLOCKS_PER_SEC/(1000));
    
    *time_taken = d_time;
    *num_comparisions = djk_edge_comparisons + pq.getComparisions();

//DEBUG
    // cout << "After Dijkstra:" << endl;
    // printGraph(G);

    
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

