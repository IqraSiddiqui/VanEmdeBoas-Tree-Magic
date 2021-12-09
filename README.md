# Overview
This is an academic technical project presented by team analyzed-structures of CS-201 at Habib University. We have implemented and used Van Emde Boas Tree (a.k.a VEB) in C++ to solve nearest node problem in the best efficient way possible and incorporate its GUI using html.

# Problem Statement
Finding Nearest Node from a source node in O(log(log U)) time complexity.

# Application
Searching for the nearest node from a source node find its application in number of brands and organizations such as in food delivery applications, navigational applictions etc. It play a vital role in these zones and hence opting the most efficient way to serve this purpose is very essential. This project provides a skeleton and prototype of one such application using Van Emde Boas Tree as the primary data structure at back end. We have tried to use the con of VEB including traversal and search in O(log log U) time complexity.  Our goal is to establish that indeed if VEB is used to find nearest node at the back end then it can greatly enhance the overall time complexity of the system. This prototype can be incorporated in any other system which includes finding of nearest node.

# Approach
We have selected Dijsktra Algorithm to find the nearest node as it is a single-source optimized algortithm hence is best suited for our purpose. Van Emde Boass Tree class has been implemented in veb.cpp. This class is being used in dijsktra_on_VEB.cpp, in which we have the running function that takes, source as input and returns the nearest node from this source using Dijsktra Algorithm. The GUI for this prototypte is a html webpage which displays the graph of interest and a search box and a submit button where user must enter the source node i.e. node whose nearest node one has to search for. Following are some snippets of our GUI:
<img src="/doc/3.png" alt="Loadin Graph"/>
<img src="/doc/1.png" alt=""/>
<img src="/doc/2.png" alt=""/>

# Header Files
- fstream.h
- bits/stdc++.h
- string.h

# Testing
We have developed two dummy data; one of 500 nodes and other 5000 nodes graph in order to test our prototype. The graph was developed using a python script make_graph.py. 
In order to test the back end code, following steps were performed:
- Open dijsktra_on_VEB.cpp
- in line 7; enter file name containing graph data for every edge at every line as 
startingNode endingNode weightOfEdge
- in line 8; enter number of nodes
- in line 9; enter number of edges
- Finally run main.cpp
In GUI, 500 nodes data has been incorporated. It was tested by adding source nodes in text box and using submit button. We have also tested our GUI for wrong source odes i.e. nodes that do not exist in graph. 

# Conclusions
Alongside this, we also implemented Dijsktra on a Min Heap to find the nearest node from a source. After performing time complexity analysis of Dijsktra on VEB and Dijsktra o Min Heap, it can be concluded that Dijsktra Algorithm performed brilliantly great with VEB i.e. with a time complexity of O(log(log U)) while with Min Heap, the time complexity of Dijsktra came out to be O(V) where V is the number of nodes in the graph. 
Hence, it can be concluded that if VEB is used as a data structure with shortest path algorithms like Dijsktra, the results can be impressive and it can reduce the overall time complexity of such systems. 

# References
- https://visjs.github.io/vis-network/docs/network/
- https://websitesetup.org/website-coding-html-css/
- https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
- https://github.com/aishwarydewangan/Dijkstra-using-van-Emde-Boas-Tree
