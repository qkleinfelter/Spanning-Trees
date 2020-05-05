/*
	Quinn Kleinfelter
	EECS 2520-001 Non Linear Data Structures Spring 2020
	Dr. Thomas
	Last Edited: 5/5/20

	Header file for the Prim's algorithm running class,
	this class uses the shared edge struct, as well as a
	min priority queue and insertion sort, to run Prim's algorithm
	to find a minimum spanning tree.
*/

#pragma once
#include <string>
#include "Edge.h"

using namespace std;

class Prim
{
private:

	edge* extractMinNode();					// Extracts the minimum node from the min priority queue
	void decreaseKey(int index, double key);// Decreases the node at a given index in the min priority queue to the key passed in
	void minHeapify(int index);				// Ensures the min priority queue maintains the min heap property at an index
	int parent(int index);					// Returns the index of the parent of a given index
	int left(int index);					// Returns the index of the left child of a given index
	int right(int index);					// Returns the index of the right child of a given index
	int findInQueue(edge* p);				// Finds where a given edge exists at in the queue

	int heapLength;							// Variable to keep track of the heap length
	int heapsize;							// Variable to keep track of the heap size

	edge* nodes;							// Array of edges
	edge** heap;							// Array of pointers to the location of each edge in the nodes array

	void alphabeticalInsertionSort(edge arr[], int numOfEdges, string nodeVertices[]); // Alphabetical insertion sort run on the final list of edges to produce a correct output
	bool edgeAlphaCompare(edge& edge1, edge& edge2, string nodeVertices[]); // Alphabetical edge comparison function, used in the insertion sort above
public:
	Prim();		// Constructor
	~Prim();	// Destructor

	void findMST(string* nodeVertices, double** weights, int numOfNodes);	// Finds an MST for a graph that has a string[] of nodeVertices, a 2d array of weights that make up an adjancecy matrix, and the number of nodes in the graph
};