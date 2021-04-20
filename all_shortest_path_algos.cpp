#include"dependencies.h"


// function to implement thr FloydWarshall algorithm
void implementFloydWarshall(vector<vector<long>> G, double* time_taken, int* num_comparisions){


//DEBUG
    // cout << "Before FloydWarshall:" << endl;
    // printGraph(G);

    //start the clock
    clock_t start = clock();


    int n = G.size();
    // comparison counter
    int comparisions = 0;


    // the floyd-warshall algorithm-loop
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

    // stop the clock
    clock_t end = clock();

    // measure the time in milliseconds
    double d_time = double(end-start)/ double(CLOCKS_PER_SEC/(1000));
    
    // printing the output in the required format
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

    // "return" the stats
    *num_comparisions = comparisions;
    *time_taken = d_time; 
}


// Implements the Dijkstra Algorithm for a given graph and source vertex
void implementDijkstraDHeap(vector<vector<long>> G, int src, double* time_taken, int* num_comparisions, int D, bool debug){

//DEBUG
    // cout << "Before Dijkstra:" << endl;
    // printGraph(G);
//    cerr << "++++++++++++++++++++++" << endl;

    int V = G.size();
    int djk_edge_comparisons = 0;

    // Declare MinHeap/PriorityQueue
    DMinHeap pq(D, V);


    // Initially all nodes are ata distance of INFINITY from the start_node
    vector<long> dist(V, INT_MAX);
 
    // One the best path to a node is found, the node is marked as "DONE" 
    vector<bool> doneSet(V, false);

    // start the clock
    clock_t start = clock();
    
    // Insert Source node to the PriorityQueue
    dist[src] = 0;
    pq.insertKey(make_pair(0, src));
     
    

    // repeat until the priority queue is empty
    while (!pq.isEmpty()){

        // Extract the first element from the priority queue
        pair<long, int> extracted_node = pq.extractMin();

        long u_dist = extracted_node.first;
        int u = extracted_node.second;

//DEBUG
//        cerr << "Removed node:" << u_dist << " " << u << endl;


//        This node's best distance is found
        doneSet[u] = true;

//DEBUG
//        cerr<<"For vertex:" << u << endl;
//        cerr << "comparisions:" << pq.getComparisions() << endl;
//        cerr << djk_comps << endl;
            

// Check all nodes connected to u and relax edges
        for (int i = 0; i < V; ++i){

            // get the weight from current node to this node from the adjacency matrix            
	        long weight = G[u][i];

            // Of all neighbours, only consider neighbours whose best distance is not yet found
            if (weight != INT_MAX && doneSet[i] == false)
            {
//DEBUG
//                cerr << "finding better path to:" << i <<  "from " << u <<endl;

                // An edge comparison
		        djk_edge_comparisons++;

		        if(dist[i] > dist[u] + weight ){

                	if(dist[i] != INT_MAX){
                	// if this node is already discovered, update best path
//DEBUG
//                	    cerr << "Updating node: "<< dist[i] <<  "  "<< i << " to  ";  
                	    dist[i] = dist[u] + weight;
//DEBUG
//                	    cerr << dist[i] <<  "  "<< i << endl;  

                	    pq.decreaseKey(i, dist[i]);
                	}
                	else{
                	// if this node has not been discovered yet, we insert it into the priority queue
//DEBUG
//                	    cerr << "Inserting node: "<< dist[i] << "  "<< i << endl;
                         
                	    dist[i] = dist[u] + weight;
                	    pq.insertKey(make_pair(dist[i], i));

                	}
                	
		        }
            }
        }

//DEBUG
        
        
        
    }
    // print DEBUG information if requested
    if(debug){
        cerr << "== Last Iteration of Dijsktra == " << endl;
        cerr << "Heap comparisions:\t" << pq.getComparisions() << "\t";
        cerr << "Edge comparisions:\t\t\t" << djk_edge_comparisons << endl;
        
        cerr << "Count calls to extractMin:\t" << pq.number_of_calls_to_ExtractMin << "\t";
        cerr << "Sum comparisons by extractMin:\t" << pq.total_comparisons_added_by_extractMin << "\t";
        cerr << "Max comparisons by one extractMin:\t" << pq.max_comparisons_added_by_extractMin << "\n";
        
        cerr << "Count calls to decreaseKey:\t" << pq.number_of_calls_to_DereaseKey << "\t";
        cerr << "Sum comparisons by decreaseKey:\t" << pq.total_comparisons_added_by_DecreaseKey << "\t";
        cerr << "Max comparsons by decreaseKey:\t\t" << pq.max_comparisons_added_by_DecreaseKey << "\n";
    }
    // stop the clock
    clock_t end = clock();

    double d_time = double(end-start)/ double(CLOCKS_PER_SEC/(1000));

    //"return" the runtime stats    
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

