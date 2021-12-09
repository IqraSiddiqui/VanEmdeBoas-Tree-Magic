
// C / C++ program for Dijkstra's
// shortest path algorithm for adjacency
// list representation of graph
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
// A structure to represent a
// node in adjacency list
// Ref: https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/

using namespace std;

struct AdjListNode			//---------O(1)
{
    int dest;
    int weight;
    struct AdjListNode* next;
};
 
// A structure to represent
// an adjacency list
struct AdjList
{
     
   // Pointer to head node of list
   struct AdjListNode *head;
};
 
// A structure to represent a graph.
// A graph is an array of adjacency lists.
// Size of array will be V (number of
// vertices in graph)
struct Graph						//---------O(1)
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create
// a new adjacency list node
struct AdjListNode* newAdjListNode( 	//---------O(1)
                   int dest, int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*)
      malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates
// a graph of V vertices
struct Graph* createGraph(int V)			//---------O(V)
{
    struct Graph* graph = (struct Graph*)
            malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists. 
    // Size of array will be V
    graph->array = (struct AdjList*)
       malloc(V * sizeof(struct AdjList));
 
    // Initialize each adjacency list
    // as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src,		//---------O(1)
                   int dest, int weight)
{
    // Add an edge from src to dest. 
    // A new node is added to the adjacency
    // list of src.  The node is
    // added at the beginning
    struct AdjListNode* newNode =
            newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected,
    // add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// Structure to represent a min heap node
struct MinHeapNode				//---------O(1)
{
    int  v;
    int dist;
};
 
// Structure to represent a min heap
struct MinHeap						//---------O(1)
{
     
    // Number of heap nodes present currently
    int size;    
   
    // Capacity of min heap
    int capacity; 
   
    // This is needed for decreaseKey()
    int *pos;   
    struct MinHeapNode **array;
};
// A utility function to create a
// new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v,
                                 int dist)					//---------O(1)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*)
      malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*)
      malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(
            capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**)
                 malloc(capacity *
       sizeof(struct MinHeapNode*));
    return minHeap;
}
 
// A utility function to swap two
// nodes of min heap.
// Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a,
                     struct MinHeapNode** b)				//---------O(1)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
// A standard function to
// heapify at given idx
// This function also updates
// position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap,
                                  int idx)				//---------O(1)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist <
         minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist <
         minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode =
             minHeap->array[smallest];
        MinHeapNode *idxNode =
                 minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
                         &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 
// A utility function to check if
// the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)			//---------O(1)
{
    return minHeap->size == 0;
}
 
// Standard function to extract
// minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap*
                                   minHeap)		//---------O(1)
{
    if (isEmpty(minHeap))
        return NULL;
 
    // Store the root node
    struct MinHeapNode* root =
                   minHeap->array[0];
 
    // Replace root node with last node
    struct MinHeapNode* lastNode =
         minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasy dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap* minHeap,
                         int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete
    // tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist <			//---------O(log i)
           minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =
                                      (i-1)/2;
        minHeap->pos[minHeap->array[
                             (i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], 
                 &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
// A utility function used to print the solution
void printArr(int dist[], int n)				//---------O(n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
 
// The main function that calulates
// distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(struct Graph* graph, int src)
{
     
    // Get the number of vertices in graph
    int V = graph->V;
   
    // dist values used to pick
    // minimum weight edge in cut
    int dist[V];    
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)					//---------O(V)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v,
                                      dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] =
          newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially size of min heap is equal to V
    minHeap->size = V;
 
    // In the followin loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!isEmpty(minHeap))				//---------O(size_of_MinHeap)
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode* minHeapNode =
                     extractMin(minHeap);
       
        // Store the extracted vertex number
        int u = minHeapNode->v;
 
        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        struct AdjListNode* pCrawl =
                     graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
 
            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            if (isInMinHeap(minHeap, v) &&
                      dist[u] != INT_MAX &&
              pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
 
                // update distance
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }
 
    // print the calculated shortest distances
    //printArr(dist, V);

    int destination=0; // variable to store the nearest node from source
	int n=dist[2]; //variable to store the minimum distance
	for(int i = 0; i < V - 1; i++) {  //the loop iterates over distList and finds nearest node from source by finding the minimum distance and its corresponding node ID.
		if (dist[i]<n && n!=0 && dist[i]!=0){
			destination=i;
			n=dist[i];
		}	
	}
    cout << "\nNearest Destination from Source: "<<src<<" is : "<<destination<<endl; //prints the output 
}

using namespace std; 
// Driver program to test above functions
int main()
// Ref: https://www.geeksforgeeks.org/tokenizing-a-string-cpp/
{
    /* Time function returns the time since the 
        Epoch(jan 1 1970). Returned time is in seconds. */
    time_t start, end;
  
    /* You can call it like this : start = time(NULL);
     in both the way start contain total time in seconds 
     since the Epoch. */
    time(&start);
  
    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);
  
    int V = 5000;
    struct Graph* graph = createGraph(V);
    std::ifstream myfile("myfile.txt");
    std::string line;
    if (myfile.is_open()) {
       
        while (getline(myfile,line)){
           // std::cout << line << std::endl ; 
            vector <string> tokens;
      
            // stringstream class check1
            std::stringstream check1(line);
            
            std::string intermediate;
            
            // Tokenizing w.r.t. space ' '
            while(getline(check1, intermediate, ' '))
            {
                tokens.push_back(intermediate);
            }
            addEdge(graph, stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2]));
            //cout << stoi(tokens[0]) << " " << stoi(tokens[1]) << " " << stoi(tokens[2]) << endl; 
            
        }
    }
    else {
        std::cout << "Error opening file ... " << std::endl; 
    }
    // create the graph given in above fugure
    
    
 //Complexity Analysis
    dijkstra(graph, 0);
    // Recording end time.
    time(&end);
  
    // Calculating total time taken by the program.
    double time_taken = double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << endl;
    cout << " sec " << endl;
 
    return 0;
}
//-----------------------------------------------HENCE,
//It can be concluded that the worst case time complexity of Dijsktra with min Heap is O(V) where V is the size of minHeap that is basically number of nodes in graph.
