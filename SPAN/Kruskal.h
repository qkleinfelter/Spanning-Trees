/*
	Quinn Kleinfelter
	EECS 2520-001 Non Linear Data Structures Spring 2020
	Dr. Thomas
	Last Edited: 5/5/20

	Header file for the Kruskal's algorithm running class,
	this class uses the shared edge struct, as well as a
	quicksort and insertion sort, to run Kruskal's algorithm
	to find a minimum spanning tree.
*/

#pragma once
#include <string>
#include "Edge.h"

using namespace std;

class Kruskal
{
private:
	struct node
	{
		// Node struct used to keep track of the different sets
		// we have in use in our Kruskal's algorithm
		// Next Neighbor and Next Vertex allow this to work 
		// as a linked list of linked lists
		string word;
		node* nextNeighbor = nullptr;
		node* nextVertex = nullptr;
	};

	node* head = nullptr; // The first node in our linked list of linked lists
	void sortWeightAscending(edge arr[], int p, int r);		// Sort an array of edges by weight ascending using quick sort
	int partitionWeightAscending(edge arr[], int p, int r); // Partition the edge array using the quick sort algorithm

	void alphabeticalInsertionSort(edge arr[], int numOfEdges, string nodeVertices[]); // An insertion sort run at the end of findMST to sort the edges into alphabetical order
	bool edgeAlphaCompare(edge& edge1, edge& edge2, string nodeVertices[]); // Quick edge comparison function used in the alphabetical insertion sort

public:
	Kruskal(); // Constructor
	~Kruskal();// Destructor

	void findMST(string* nodeVertices, double** adjMatrix, int numOfNodes); // Find an MST of a graph that has a nodeVertices array of strings, a 2 dimensional double array adjancecy matrix, and a certain number of nodes
	void makeSet(const string& word); // Makes a new set for the passed in word
	node* findSet(const string& word); // Finds the set that the passed in word is located in
	void setUnion(node* u, node* v); // Merges the two sets passed in

};