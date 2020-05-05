/*
	File: Prim.cpp - Implementation of Prim's algorithm to find a MST of a graph
	c.f.: Prim.h

	This class implements Prim's algorithm to find a minimum spanning
	tree of a graph, using a shared edge struct, a min priority queue,
	and insertion sort

	Author: Quinn Kleinfelter
	Class: EECS 2510-001 Non Linear Data Structures Spring 2020
	Instructor: Dr. Thomas
	Last Edited: 5/5/20
	Copyright: Copyright 2020 by Quinn Kleinfelter. All rights reserved.
*/

#include "Prim.h"
#include <iostream>

using namespace std;

Prim::Prim()
{
	// Constructor, nothing really needed here as we handle
	// most things at the beginning of findMST
}

Prim::~Prim()
{
	// Destructor, nothing really needed here as we handle
	// most things at the end of findMST
}

void Prim::findMST(string* nodeVertices, double** weights, int numOfNodes)
{
	// Finds a minimum spanning tree on the graph specified
	// by the parameters using Prim's algorithm

	nodes = new edge[numOfNodes]; // initialize our nodes array

	heapLength = numOfNodes + 1; // Heaplength needs to be the number of nodes + 1 so we can use the heap as 1 indexed

	heap = new edge * [heapLength]; // Initialize the heap array
	heapsize = 0; // Heapsize is 0 because there is nothing in it

	for (int i = 0; i < numOfNodes; i++)
	{
		// Loop through creating our edges to fill up the nodes and heap array
		edge newNode;
		newNode.src = i; // The source of the new node is i, the current node
		newNode.weight = std::numeric_limits<double>::max(); // Weight starts off as the numerical maximum for a double
		newNode.dest = i; // The destination starts at i as well
		nodes[i] = newNode; // Nodes[i] becomes our new node
		heap[i + 1] = &nodes[i]; // The heap of i + 1 (because it is one indexed) becomes a reference to the new node in the nodes array
		heapsize++; // Increment the heapsize
	}

	decreaseKey(1, 0); // Decrease the first element to a key of 0

	while (heapsize != 0)
	{
		// Loop while we still have something in the heap
		edge* u = extractMinNode(); // Extract the minimum node from the heap

		int uIndex = u - &nodes[0]; // Calculate the index of u in the nodes array by subtracting the pointer to it and to nodes[0]. C++ will make the pointer math work nicely for us

		for (int i = 0; i < numOfNodes; i++)
		{
			// Loop through the row of the adjacency matrix that contains the current node, so we consider edges that include u
			if (weights[uIndex][i] != 0)
			{
				// If the weight at the given index is not 0, we know there is an edge here
				const string& vWord = nodeVertices[i]; // Grab the word for v (or the destination), by checking nodeVertices at i

				edge* v = &nodes[i]; // The edge for v is simply a reference to to nodes at i

				int posInQueue = findInQueue(v); // Next we want to check if v is in the queue, so we try to find it in the queue

				if (posInQueue != 0 && weights[uIndex][i] < v->weight)
				{
					// If we found v in the queue, (posInQueue != 0) and the weight at the index is less
					// than the weight already attached to v
					double newWeight = weights[uIndex][i]; // Grab the weight for v
					v->dest = uIndex; // Set v's destination to be u
					decreaseKey(posInQueue, newWeight); // Decrease v's key in the queue to be the new weight we grabbed above
				}
			}
		}
	}

	for (int i = 0; i < numOfNodes; i++)
	{
		// Loop through our nodes array making the vertices be in the correct order
		// i.e. a-b instead of b-a
		edge& currEdge = nodes[i]; // Grab the current edge

		if (nodeVertices[currEdge.src] > nodeVertices[currEdge.dest])
		{
			// If the src is greater than the destination, lexicographically,
			// swap them
			int temp = currEdge.src;
			currEdge.src = currEdge.dest;
			currEdge.dest = temp;
		}
	}

	alphabeticalInsertionSort(nodes, numOfNodes, nodeVertices); // Sort the nodes alphabetically using insertion sort

	double totalWeight = 0; // Double variable to keep track of the total weight, because we want to print this before any edges

	for (int i = 0; i < numOfNodes; i++)
	{
		// Loop through the nodes array
		edge& p = nodes[i];

		if (p.dest != p.src)
		{
			// If our current edge doesn't have the same src and dest, we know its in the MST, so increase the total weight
			totalWeight += p.weight;
		}
	}

	cout << totalWeight << endl; // Output the total weight

	for (int i = 0; i < numOfNodes; i++)
	{
		// Loop through the nodes array
		edge& p = nodes[i];

		if (p.dest != p.src)
		{
			// If our current edge doesn't have the same src and dest, we know its in the MST,
			// so print it out nicely, i.e. "a-b: 1"
			cout << nodeVertices[p.src] << "-" << nodeVertices[p.dest] << ": " << p.weight << endl;
		}
	}

	// delete nodes and heap as clean up
	delete[] nodes; 
	delete[] heap;
}

edge* Prim::extractMinNode()
{
	if (heapsize < 1)
	{
		cout << "Heap underflow" << endl;
		return nullptr;
	}

	edge* min = heap[1];
	heap[1] = heap[heapsize];
	heapsize--;
	minHeapify(1);
	return min;
}

int Prim::left(int index)
{
	return 2 * index;
}

int Prim::right(int index)
{
	return (2 * index) + 1;
}

int Prim::parent(int index)
{
	return index / 2;
}

void Prim::decreaseKey(int index, double key)
{
	edge* p = heap[index];
	if (key > p->weight)
	{
		cout << "New key value is greater than current key value" << endl;
		return;
	}

	p->weight = key;

	while (index > 1 && heap[parent(index)]->weight > heap[index]->weight)
	{
		edge* temp = heap[index];
		heap[index] = heap[parent(index)];
		heap[parent(index)] = temp;
		index = parent(index);
	}
}


void Prim::minHeapify(int index)
{
	int l = left(index);
	int r = right(index);
	int smallest;

	if (l <= heapsize && heap[l]->weight < heap[index]->weight)
	{
		smallest = l;
	}
	else
	{
		smallest = index;
	}

	if (r <= heapsize && heap[r]->weight < heap[smallest]->weight)
	{
		smallest = r;
	}

	if (smallest != index)
	{
		edge* temp = heap[index];
		heap[index] = heap[smallest];
		heap[smallest] = temp;
		minHeapify(smallest);
	}
}

int Prim::findInQueue(edge* p)
{
	for (int i = 1; i <= heapsize; i++)
	{
		if (heap[i] == p) return i;
	}

	return 0;
}

void Prim::alphabeticalInsertionSort(edge arr[], int numOfEdges, string nodeVertices[])
{
	int i, j;
	edge key;
	for (i = 1; i < numOfEdges; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && !edgeAlphaCompare(arr[j], key, nodeVertices))
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

bool Prim::edgeAlphaCompare(edge& edge1, edge& edge2, string nodeVertices[])
{
	if (nodeVertices[edge1.src] == nodeVertices[edge2.src])
	{
		return nodeVertices[edge1.dest] < nodeVertices[edge2.dest];
	}
	else
	{
		return nodeVertices[edge1.src] < nodeVertices[edge2.src];
	}
}