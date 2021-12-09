#include <bits/stdc++.h>
#include <fstream>
#include<string>
using namespace std;

int roundUp(int x) {
	if ( x < 0 ) return 0;
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
}

float lowerSqrt(int val) {
	return pow ( 2, floor ( log2 ( val )  / 2 ) );
}

float higherSqrt(int val) {
	return pow ( 2, ceil ( log2 ( val )  / 2 ) );
}

struct veb {
	int u, min, max, sqrt_u, sqrt_high, sqrt_low;
	veb *summary, **cluster;
};

int low(veb *root, int key) {
	return key % root->sqrt_low;
}

int high(veb *root, int key) {
	return key / root->sqrt_low;
}

int index(veb *root, int i, int j) {
	return (i*root->sqrt_low)+j;
}

int veb_max(veb *root) {
	if(root == NULL) {
		return -1;
	}
	return root->max;
}

int veb_min(veb *root) {
	if(root == NULL) {
		return -1;
	}
	return root->min;
}

veb* create(veb *root, int size) {
	int temp = roundUp(size);
	root->u = temp;
	root->sqrt_u = sqrt(temp);
	root->sqrt_low = lowerSqrt(temp);
	root->sqrt_high = higherSqrt(temp);
	root->min = INT_MIN;
	root->max = INT_MIN;
	root->summary = NULL;
	if(root->u <= 2) {
		root->cluster = NULL;
	} else {
		root->cluster = new veb * [root->sqrt_high];
		for(int i = 0; i < root->sqrt_high; i++) {
			root->cluster[i] = NULL;
		}
	}
	return root;
}

void insert(veb *& root, int key, int u) {
	if(root == NULL) {
		root = new veb;
		root = create(root, u);
	}

	if(key < 0 || key >= root->u) {
		cout << "\nKey out of range";
		return;
	}

	if(key == root->min || key == root->max) {
		return;
	}

	if(root->min == INT_MIN) {
		root->min = root->max = key;
		return;
	}

	if(root->min > key) {
		int temp = key;
		key = root->min;
		root->min = temp;
	}

	if(root->max < key) {
		root->max = key;
	}

	if(root->u <= 2) {
		return;
	}

	int i = high(root, key);
	int j = low(root, key);

	if(root->cluster[i] == NULL) {
		insert(root->summary, i, root->sqrt_high);
	}

	insert(root->cluster[i], j, root->sqrt_low);
}

int successor(veb *root, int key) {
	if(root == NULL) {
		return -1;
	}

	if(root->u == 2) {
		if(key == 0 && root->max == 1) {
			return 1;
		}
		return -1;
	}

	if(key < -1 || key >= root->u) {
		return -1;
	}

	if(key < root->min) {
		return root->min;
	}

	if(root->summary == NULL) {
		if(key < root->max) {
			return root->max;
		}
		return -1;
	}

	int i = high(root, key);
	int j = INT_MIN;
	int h = high(root, key);
	int l = low(root, key);

	if(l < veb_max(root->cluster[i])) {
		j = successor(root->cluster[i], l);
		if(j == -1)
			return -1;
	} else {
		i = successor(root->summary, h);

		if(i == -1) {
			if(key < root->max) {
				return root->max;
			}
			return -1;
		}
		j = veb_min(root->cluster[i]);
		if(j == -1)
			return -1;
	}

	return index(root, i, j);
}




int xyz(int source) {
	int nodes, edges, next_dis,num;
	ifstream indata; // indata is like cin from the text file

	indata.open("finaltest.txt"); // Enter filename here which contains graph edge data 
	nodes=5000; //enter number of nodes of graph here
	edges=5000; //enter number of edges of graph here
	//nodes=9;
	//edges=14;
	//source; //enter source node here

	vector< pair<int, int> > graph[nodes+1];
	vector<int> dist(nodes+1, 2147483647); 
	unordered_map<int, list<int> > distList; 

	indata >> num; //read first number from the first line of file
   while ( !indata.eof() ) { //read and perfrom following statements for all numbers in file
	   int i=0; 
	   int a,b,w; //a=starting node of an edge; b=ending node of an edge; w=weight of an edge
	   while(i<3){ //reading data from file and assigning them to their respective variables i.e. a,b or w 
		if(i==0)
			a=num;
		else if(i==1)
			b=num;
		else
			w=num;
		i=i+1;
		indata >> num; // now input next number
	   }

		graph[a].push_back(make_pair(b, w)); //append the edge in the graph i.e a to b in adjacency list representation of graph
		graph[b].push_back(make_pair(a, w)); //we have assumed the graph is undirectional hence appending it to the edge of b too i.e b to a
   }
   indata.close(); //close the file once all graph data has been read and stored in the graph

	dist[source] = 0; //setting distance from source to source equal to 0
	distList[0].push_back(source); 

	veb *targetVeb = new veb; //create the veb object
	targetVeb = create(targetVeb, 100); //universe size has been taken randomly i.e 100
	insert(targetVeb, 0, 10); //insert 0 to veb created in previous line 
	next_dis = 0; 
	while(next_dis != -1) { //apply dijsktra for all the nodes i.e. until the next_dis is not equal to -1 i.e. there exist a successor

		while(!distList[next_dis].empty()) { //applying dijsktra algorithm
			int u = distList[next_dis].front();  //starting node
			distList[next_dis].pop_front(); 
			for(int i = 0; i < graph[u].size(); i++) {
				pair<int, int> extract = graph[u][i]; 
				int v = extract.first; //ending node
				int w = extract.second; //weight of this edge (u,v)

				if(dist[v] > dist[u] + w) { //update the weights of all edges
					dist[v] = dist[u] + w;
					insert(targetVeb, dist[v], 8); //insert dist[v] to veb
					distList[dist[v]].push_back(v);//add dist[v] to the distList
				}
			}
		}
		next_dis = successor(targetVeb, next_dis); //check if there exist any successor if not i.e -1, then terminate and hence dijsktra has been completed for all nodes.
	}
	
	
	int destination=0; // variable to store the nearest node from source
	int n=dist[2]; //variable to store the minimum distance
	for(int i = 0; i < dist.size() - 1; i++) {  //the loop iterates over distList and finds nearest node from source by finding the minimum distance and its corresponding node ID.
		if (dist[i]<n && n!=0 && dist[i]!=0){
			destination=i;
			n=dist[i];
		}	
	}
	cout << "\nNearest Destination from Source: "<<source<<" is : "<<destination<<endl; //prints the output
	return destination;
   }

int main() {
	ofstream myfile;
	myfile.open ("nearest_node.txt");
for (int i = 0; i < 500; i++) {
	
	myfile << xyz(i) << ",";
	
}
myfile.close();
}
