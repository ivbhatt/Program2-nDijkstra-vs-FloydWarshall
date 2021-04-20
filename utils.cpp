#include<bits/stdc++.h>
using namespace std;


//Utility function used for debugging 
void printGraph(vector<vector<long>> G){
    for(int i = 0; i < G.size(); i++){
        for(int j = 0; j < G[0].size(); j++ )
            cerr<<setw(12)<<right<<G[i][j]<<" ";
        cerr<<endl;
    }
}

//Utility function used to load the graph into RAM (in adjaceny matrix format) from .gph file

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


//Class to implement D-arry MinHeap

class DMinHeap{
	vector<pair<long,int>> heap_array; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int heap_size; // Current number of elements in min heap
	int comparisions; // variable to store the number of comparisons done on this instance of the heap
	int D;     // tells us how many children does each node have

    
public:
    int number_of_calls_to_ExtractMin;
    int max_comparisons_added_by_extractMin;
    int total_comparisons_added_by_extractMin;

    int number_of_calls_to_DereaseKey;
    int max_comparisons_added_by_DecreaseKey;
    int total_comparisons_added_by_DecreaseKey;

//Generic constructor to initialize the DMinHeap
    DMinHeap(int D, int capacity){
        heap_size = 0;
        this->capacity = capacity;
        this->comparisions = 0;
        this->D = D;
        heap_array = vector<pair<long,int>> (capacity);
        number_of_calls_to_ExtractMin = 0;
        max_comparisons_added_by_extractMin = 0;
        total_comparisons_added_by_extractMin = 0;

        number_of_calls_to_DereaseKey = 0;
        max_comparisons_added_by_DecreaseKey = 0;
        total_comparisons_added_by_DecreaseKey = 0;
        
    }
    
//    Basic getters and setters are defined inline 
    
    int getComparisions(){
        return comparisions;
    }
    int parent(int i){
        if(i==0)
            return 0;
        return (i-1)/D;
    }
    
    
    int isEmpty(){
        if(heap_size == 0){
            return 1;
        }
        else{
            return 0;
        }
    }
// ***************************************************

//Functionalities are declared here and defined outside the class defintion
    
    void insertKey(pair<long,int> new_node);    
    
    pair<long, int> extractMin();

	void minHeapify(int index);
	

	void decreaseKey(int i, long new_val);
	
	void printHeap();
	
	
	
};

//Used to insert a node into the heap while maintaining the heap property
void DMinHeap::insertKey(pair<long,int> new_node){
    //If heap is full, throw error
    if(heap_size == capacity){
        cout << "\nWARNING:: Overflow: Could not insertKey\n";
        return;
    }
    
    
    //insert the node at the end of the heap
    heap_size++;
    int i = heap_size-1;
    heap_array[i] = new_node;
    
    //then percolate it up to its appropriate position
    while(i>=0){
//        comparisions++;
        if(heap_array[i] < heap_array[parent(i)]){

            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
            
        }
        else{
            break;
        }
    }
    
}
   

//Used to extract the minimum node (root) from the heap while maintaining the heap property
pair<long, int> DMinHeap::extractMin(){
    number_of_calls_to_ExtractMin += 1;
    
    //If heap is empty return an infinite value
    if(heap_size <=0)
        return make_pair(INT_MAX, INT_MAX);

    if(heap_size == 1){
        heap_size--;
        return heap_array[0];
    }

    //If heap has many elements than we must remove root, replace it by the last element 
    //and then call heapify on the new root to maintain heap property    
    pair<long, int> root = heap_array[0];
    heap_array[0] = heap_array[heap_size-1];
    heap_size--;

    minHeapify(0); 
    return root;
}
    
// Function used to ensure heap-property starting at node index
void DMinHeap::minHeapify(int index){

    int children[D+1];
    int total_comparison_cnt = 0;
    while(1){
    
        for(int i=1; i<=D; i++){
            children[i] = ((D*index + i) < heap_size) ? (D*index + i) : -1;
        }
        
        int min_child_index;
        //Value of 505 is used because this code is being written as a part for CSC 505: Design and Analysis of Algorithms
        pair<long,int> min_child = make_pair(INT_MAX, 505);
        
        //Number of comparisions required to find the minimum child are stored in this variable 
        int comparison_counter = 0;
        
        // Find the minimum child with at most D comparisions
        for(int i=1; i<=D; i++){
            if(children[i] != -1){ 
                comparison_counter++;
                if(heap_array[children[i]].first < min_child.first){
                    min_child_index = children[i];
                    min_child = heap_array[children[i]];
                }
            }
        }
        
        if(min_child.first == INT_MAX){
//            cerr << "w";
            break;
        }

        if(comparison_counter > D){
            cerr << "WARNING:: comparison_counter > D. The code is giong CRAZZIE! (unknown bug/ this should never happen)" << endl;
            exit(-1);
        }
        
        
        //adding comparisons made to the global counter
        comparisions+=comparison_counter;        
        total_comparison_cnt += comparison_counter;
        // if min_child is less than parent, we must swap the parent and the child
        if(heap_array[index].first > heap_array[min_child_index].first){
            swap(heap_array[index], heap_array[min_child_index]);
        }else{
            break;
        }
        
        //continue to see if parent deserves to go further down!
        index = min_child_index;
    }
    if(total_comparison_cnt > max_comparisons_added_by_extractMin)
            max_comparisons_added_by_extractMin = total_comparison_cnt;
//    
    total_comparisons_added_by_extractMin += total_comparison_cnt;

}
 
   
//decreaseKey decreases the Key for a particular value and then percolates that node upwards to maintain the minHeap property
void DMinHeap::decreaseKey(int i, long new_val){
    number_of_calls_to_DereaseKey++;
//Finding the node with value equal to i    
    bool found = false;
    for(int temp = 0; temp < heap_size; temp++){
        if(heap_array[temp].second == i){
            heap_array[temp].first = new_val;
            i = temp;
            found = true;
            break;
        }
    }
    if (!found)
        cerr << "WARNING:: KEY NOT FOUND!" << endl;

//Percolate this node (with reduced key) until either it becomes the root or it has a parent with smaller key    
    int total_comparisions = 0;
    while(i!=0){
//    One comparision level. At most log_D(N) such comparisions will be made per decreaseKey call
        comparisions++;
        total_comparisions++;
        if(heap_array[parent(i)].first > heap_array[i].first){

            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
        }
        else
//        Break if a smaller parent is found
            break;
    
    }
    if(total_comparisions > max_comparisons_added_by_DecreaseKey)
        max_comparisons_added_by_DecreaseKey = total_comparisions;
    total_comparisons_added_by_DecreaseKey += total_comparisions;

}

//Utility function to print Heap contents
void DMinHeap::printHeap(){
cerr<<"HEAP-------->"<<endl;
for(int i = 0; i < heap_size; i++){
    cerr<<"("<<heap_array[i].first<<","<<heap_array[i].second<<")"<<endl;
}
cerr<<"---------->"<<endl;
}

