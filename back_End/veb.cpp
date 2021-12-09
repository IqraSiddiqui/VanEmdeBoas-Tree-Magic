//Ref: https://github.com/aishwarydewangan/Dijkstra-using-van-Emde-Boas-Tree

#include <bits/stdc++.h>
#include <fstream>
#include<string>

using namespace std;

int roundUp(int x) { //Since we know that Van Emde has a universe size of 2^v where v is the number of nodes. Hence, this helper function is responsible to modify and round up universe size on the basis of this principle by taking x; number of nodes as parameters.
	if ( x < 0 ) return 0;
	--x;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	x |= x >> 32;
	return x + 1;
}

float lowerSqrt(int val) {  //temperory function to find lowerSqrt 
	return pow ( 2, floor ( log2 ( val )  / 2 ) );
}

float higherSqrt(int val) { //temperory function to find higherSqrt 
	return pow ( 2, ceil ( log2 ( val )  / 2 ) );
}

struct veb { //Defining VEB structure 
	int u, min, max, sqrt_u, sqrt_high, sqrt_low; //u=universe size of VEB; min=minimum in VEB; max= maximum in VEB
	veb *summary, **cluster; //pointer to indicate summary of VEB; pointer to pointer to indicate clusters in VEB
};

int low(veb *root, int key) { //function to find lower order bit
	return key % root->sqrt_low;
}

int high(veb *root, int key) { //function to find higher order bit
	return key / root->sqrt_low;
}

int index(veb *root, int i, int j) { //function to find index
	return (i*root->sqrt_low)+j;
}

int veb_max(veb *root) { //function to find maximum in VEB
	if(root == NULL) {
		return -1;
	}
	return root->max;
}

int veb_min(veb *root) { //function to find minimum in VEB
	if(root == NULL) {
		return -1;
	}
	return root->min;
}

veb* create(veb *root, int size) { //function to create VEB
	int temp = roundUp(size); //calculating universe size for this VEB
	root->u = temp; //setting universe size for this VEB
	root->sqrt_u = sqrt(temp); //finding sqrt(u) for this VEB as it indicates the number of childrens it can have
	root->sqrt_low = lowerSqrt(temp);
	root->sqrt_high = higherSqrt(temp);
	root->min = INT_MIN; //initializing min to the lowest integr value possible
	root->max = INT_MIN; //initializing max to the lowest integr value possible
	root->summary = NULL; //initializing summary for this VEB is currently null
	//creating clusters for VEB
	if(root->u <= 2) { 
		root->cluster = NULL; //no cluster if universe size is 2 or less
	} else { //otherwise create respective number of clusters and initialize them to currently null
		root->cluster = new veb * [root->sqrt_high];
		for(int i = 0; i < root->sqrt_high; i++) {
			root->cluster[i] = NULL;
		}
	}
	return root;//hence at this stage, VEB is created and finally return the root of this VEB
}

void insert(veb *& root, int key, int u) { //function to insert a value in VEB 
	
	if(root == NULL) {  //if VEB with this root and universe size does not exist then create one 
		root = new veb;
		root = create(root, u);
	}

	if(key < 0 || key >= root->u) { // if key is beyond our universe size then display this error alert
		cout << "\nKey out of range";
		return;
	}

	if(key == root->min || key == root->max) { //If key already exist as min or max of VEB
		return;
	}

	if(root->min == INT_MIN) { //insert key as the min or max of VEB
		root->min = root->max = key;
		return;
	}

	if(root->min > key) {  //If current min of VEB is greator than key then hence make key as the new min for VEB
		int temp = key;
		key = root->min;
		root->min = temp;
	}

	if(root->max < key) { //If current max of VEB is less than key then hence make key as the new max for VEB
		root->max = key;
	}

	if(root->u <= 2) { //If universe size is less than hence do nothing. i.e. neither alter veb min, max etc
		return;
	}

	int i = high(root, key);
	int j = low(root, key);

	if(root->cluster[i] == NULL) { 
		insert(root->summary, i, root->sqrt_high);
	}

	insert(root->cluster[i], j, root->sqrt_low);
}

int successor(veb *root, int key) { //Function for finding successor key
	if(root == NULL) { //If VEB is empty then hence no successor
		return -1;
	}

	if(root->u == 2) {  //i.e. only two keys can be stored in this VEB
		if(key == 0 && root->max == 1) {
			return 1;
		}
		return -1; //otherwise no successor found
	}

	if(key < -1 || key >= root->u) {  //i.e. key does not exist in VEB then returns -1
		return -1;
	}

	if(key < root->min) { // if key is less than minimum of this VEB then hence return minimum as that will the successor for such key
		return root->min;
	}

	if(root->summary == NULL) { //empty VEB then do this
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
