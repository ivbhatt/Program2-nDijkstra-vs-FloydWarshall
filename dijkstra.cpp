#include<iostream>
#include<climits>
#include<queue>
#include<vector>

#include"dependencies.h"

using namespace std;


// A utility function to swap two elements
void swap(pair<int,int> *x, pair<int,int> *y){
    pair<int,int> temp = *x;
    *x = *y;
    *y = temp;
}

// A class for Min Heap
class MinHeap{
    vector<pair<int,int>> harr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
    int comps;
public:
    // Constructor
    MinHeap(int capacity);
  
    int parent(int i) { return (i-1)/2; }
  
    // to get index of left child of node at index i
    int left(int i) { return (2*i + 1); }
  
    // to get index of right child of node at index i
    int right(int i) { return (2*i + 2); }

    // to heapify a subtree with the root at given index
    void MinHeapify(int );
  
    // to extract the root which is the minimum element
    pair<int,int> extractMin();
  
    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);

    // Inserts a new key 'k'
    void insertKey(pair<int,int> k);

    int isEmpty();

    void printHeap();

    int getComparisions(){ return comps; }
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap){
    heap_size = 0;
    capacity = cap;
    comps = 0;
    harr = vector<pair<int,int>> (cap);
}
  
// Inserts a new key 'k'
void MinHeap::insertKey(pair<int,int> k){
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
  
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
  
    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)].first > harr[i].first)
    {
        swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}
  
// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, int new_val){
    harr[i].first = new_val;
    while (i != 0 && harr[parent(i)].first > harr[i].first)
    {
        comps++;
        swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}
  
// Method to remove minimum element (or root) from min heap
pair<int,int> MinHeap::extractMin(){
    if (heap_size <= 0)
        return make_pair(INT_MAX,INT_MAX);
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
  
    // Store the minimum value, and remove it from heap
    pair<int,int> root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);
  
    return root;
}

void MinHeap::MinHeapify(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l].first < harr[i].first){
        smallest = l;
        comps++;
    }
    if (r < heap_size && harr[r].first < harr[smallest].first){
        smallest = r;
        comps++;
    }
    if (smallest != i)
    {
        comps++;
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

int MinHeap::isEmpty(){
    if(heap_size == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void MinHeap::printHeap(){
    
    cout<<"HEAP-------->"<<endl;
    for(int i = 0; i < heap_size; i++){
        cout<<"("<<harr[i].first<<","<<harr[i].second<<")"<<endl;
    }
    cout<<"---------->"<<endl;
}


int implementDijkstra(vector<vector<int>> G){


    return 0;
}

int main(){

    string input_file = "dual_06_09.gph";

    vector<vector<int>> G = createGraph(input_file);
    

    int V = G.size();
    int djk_comps = 0;
    MinHeap pq(V);

    printGraph(G);
    vector<int> dist(V, INT_MAX);
  
    int src = 0;
    pq.insertKey(make_pair(0, src));
    dist[src] = 0;
  
    for(int i = 1; i<V; i++){
        pq.insertKey(make_pair(INT_MAX, i));
    }

    while (!pq.isEmpty()){

        pq.printHeap();
        int u = pq.extractMin().second;

        for (int i = 0; i != G[u].size(); ++i)
        {
            int v = i;
            int weight = G[u][i];

            if (weight != INT_MAX && dist[v] > dist[u] + weight)
            {
                djk_comps++;
                dist[v] = dist[u] + weight;
                pq.decreaseKey(i, dist[v]);
            }
        }
    }

    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
    
    cout<<"Comparisions: "<<pq.getComparisions() + djk_comps<<endl;
    

    return 0;
}