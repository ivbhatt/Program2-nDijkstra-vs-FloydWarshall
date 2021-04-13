#include<bits/stdc++.h>

using namespace std;


void printGraph(vector<vector<long>> G){
    for(int i = 0; i < G.size(); i++){
        for(int j = 0; j < G[0].size(); j++ )
            cout<<setw(10)<<right<<G[i][j]<<" ";
        cout<<endl;
    }
}

vector<vector<long>> createGraph(string filename){
    vector<vector<long>> Graph;

    fstream newfile;
    newfile.open(filename,ios::in); //open a file to perform read operation using file object

    if (newfile.is_open()){   //checking whether the file is open
        string tp;
        getline(newfile, tp);
        while(tp.at(0) == 'c'){
            getline(newfile, tp);        
        }
        stringstream ss(tp);
        istream_iterator<std::string> begin(ss);
        istream_iterator<std::string> end;
        vector<string> vstrings(begin, end);

        // Extract  number of vertices and edges
        int V = stoi(vstrings[1]);
        int E = stoi(vstrings[2]);
        vector<vector<long>> G (V, vector<long> (V));

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
                G[v][u] = w;
                e++;
            }
        }
        Graph = G;
        newfile.close(); //close the file object.
    } 
    return Graph;
}



// A utility function to swap two elements
void swap(pair<long,int> *x, pair<long,int> *y){
    pair<long,int> temp = *x;
    *x = *y;
    *y = temp;
}

// A class for Min Heap
class MinHeap{
    vector<pair<long,int>> harr; // pointer to array of elements in heap
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
    pair<long,int> extractMin();
  
    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, long new_val);

    // Inserts a new key 'k'
    void insertKey(pair<long,int> k);

    int isEmpty();

    void printHeap();

    int getComparisions(){ return comps; }
};

// Constructor: Builds a heap from a given array a[] of given size
MinHeap::MinHeap(int cap){
    heap_size = 0;
    capacity = cap;
    comps = 0;
    harr = vector<pair<long,int>> (cap);
}
  
// Inserts a new key 'k'
void MinHeap::insertKey(pair<long,int> k){
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
    comps++;

    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
  
    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)].first > harr[i].first)
    {
        comps++;
        swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}
  
// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void MinHeap::decreaseKey(int i, long new_val){
    harr[i].first = new_val;
    while (i != 0 && harr[parent(i)].first > harr[i].first)
    {
        comps++;
        swap(harr[i], harr[parent(i)]);
        i = parent(i);
    }
}
  
// Method to remove minimum element (or root) from min heap
pair<long,int> MinHeap::extractMin(){
    if (heap_size <= 0)
        return make_pair(INT_MAX,INT_MAX);
    if (heap_size == 1)
    {
        heap_size--;
        return harr[0];
    }
  
    // Store the minimum value, and remove it from heap
    pair<long,int> root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);
  
    return root;
}

void MinHeap::MinHeapify(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;
    comps++;
    if (l < heap_size && harr[l].first < harr[i].first){
        smallest = l;
        
    }
    comps++;
    if (r < heap_size && harr[r].first < harr[smallest].first){
        smallest = r;
        
    }
    if (smallest != i)
    {
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
