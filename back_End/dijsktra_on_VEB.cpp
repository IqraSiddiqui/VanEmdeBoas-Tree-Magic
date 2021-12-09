

#include"veb.cpp"

int dijsktra_on_VEB(int source) {
	int nodes, edges, next_dis,num;
	ifstream indata; // indata is like cin from the text file

	indata.open("testData.txt");  // Enter filename here which contains graph edge data 
	nodes=14; //enter number of nodes of graph here
	edges=9; //enter number of edges of graph here
	
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
   return destination;
}

