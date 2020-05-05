/*
	File: Kruskal.cpp - Implementation of Kruskal's algorithm to find a MST of a graph
	c.f.: Kruskal.h

	This class implements Kruskal's algorithm to find a minimum spanning
	tree of a graph, using a shared edge struct, quicksort, and insertion sort

	Author: Quinn Kleinfelter
	Class: EECS 2510-001 Non Linear Data Structures Spring 2020
	Instructor: Dr. Thomas
	Last Edited: 5/5/20
	Copyright: Copyright 2020 by Quinn Kleinfelter. All rights reserved.
*/


#include "Kruskal.h";
#include <string>;
#include <iostream>

Kruskal::Kruskal()
{
	// Constructor, nothing really needed here as we handle
	// most things at the beginning of findMST
}

Kruskal::~Kruskal()
{
	// Destructor, nothing really needed here as we handle
	// most things at the end of findMST
}

void Kruskal::findMST(string* nodeVertices, double** adjMatrix, int numOfNodes)
{
	// Finds the minimum spanning tree using Kruskal's algorithm, 
	// for the graph defined by the parameters

	for (int i = 0; i < numOfNodes; i++)
	{
		// Create a set for each of the nodeVertices containing only itself
		makeSet(nodeVertices[i]);
	}

	edge* edges = new edge[numOfNodes * numOfNodes]; // Array of edges, theoretically could have numOfNodes^2 edges, so we need to make our array that big

	int currEdge = 0;	// The edge we are working with

	for (int i = 0; i < numOfNodes; i++)
	{
		for (int j = 0; j < numOfNodes; j++)
		{
			// Loop through the adjancecy matrix
			double currWeight = adjMatrix[i][j]; // The current weight is the adjancecy matrix art the current location

			if (currWeight != 0)
			{
				// If the weight is non-zero, we need an edge to represent it
				edge p;

				p.src = i; // P starts at i
				p.dest = j;// and ends at j

				p.weight = currWeight; // its weight is the value in the adjancecy matrix at i,j

				edges[currEdge] = p; // Add the new edge into our edge array, at the currEdge spot

				currEdge++; // Increment currEdge once we're done working on it
			}
		}
	}

	// Sort the list of edges in increasing order by weight using quicksort
	sortWeightAscending(edges, 0, currEdge);
	
	double totalWeight = 0; // Double to keep track of the total weight

	edge* mergedEdges = new edge[numOfNodes - 1]; // Array of edges to keep track of the ones we use in our MST, it will always be 1 smaller than the number of nodes
	int currMerge = 0; // Tracker for where we are currently at in mergedEdges

	for (int i = 0; i < currEdge; i++)
	{
		// Loop through the edges array
		edge& p = edges[i]; // p is the current edge
		
		node* srcContainer = findSet(nodeVertices[p.src]);		// The set that our src is contained in
		node* destContainer = findSet(nodeVertices[p.dest]);	// The set that our destination is contained in

		if (srcContainer != destContainer)
		{
			// As long as the src and destination are in different sets, we include the edge
			setUnion(srcContainer, destContainer); // So combine the two sets
			mergedEdges[currMerge] = p;	// Add p to our list of merged edges
			currMerge++;	// Increment the merge counter
			totalWeight += p.weight;	// And add p's weight to the total weight
		}
	}


	for (int i = 0; i < currMerge; i++)
	{
		// Here we are looping through the merged edges array
		// to ensure that the edges are formatted correctly for our 
		// alphabetical insertion sort. We always want the smaller
		// lexicographical side to be the src, i.e. we want
		// an edge that goes from a to b, instead of one from
		// b to a
		edge& currEdge = mergedEdges[i]; // Grab the current edge from merged edges

		if (nodeVertices[currEdge.src] > nodeVertices[currEdge.dest])
		{
			// If the src is greater than the destination, swap them
			int temp = currEdge.src;		// Temp variable to hold the source
			currEdge.src = currEdge.dest;	// Change the source to the destination
			currEdge.dest = temp;			// Change the destination to the temp holding the source
		}
	}

	// Run insertion sort on the list of merged edges to make them display alphabetically
	alphabeticalInsertionSort(mergedEdges, currMerge, nodeVertices);

	delete[] edges; // We can delete the edges array here, since we're done with it


	cout << totalWeight << endl;		// Output the total weight of the MST
	for (int i = 0; i < currMerge; i++)
	{
		// Loop through the merged edges array and print them out in the specified format, i.e. "a-b: 1"
		cout << nodeVertices[mergedEdges[i].src] << "-" << nodeVertices[mergedEdges[i].dest] << ": " << mergedEdges[i].weight << endl;
	}
}

void Kruskal::makeSet(const string& word)
{
	// Makes a set for the given word
	node* newNode = new node(); // Start off by making a new node

	newNode->word = word;		// The word for the new node is the one we passed in

	if (head == nullptr)
	{
		// If the head was null before, this must be our head so put it there and return
		head = newNode;
		return;
	}

	newNode->nextVertex = head; // Otherwise, make the next vertex for this set be the current head

	head = newNode;				// and set this node to be the head
}

Kruskal::node* Kruskal::findSet(const string& word)
{
	// Finds the set that the passed in word is located in
	node* p = head; // Start at the head

	while (p != nullptr)
	{
		node* q = p; // Set q to be p's current location, q will traverse left to right, while p goes top to bottom

		while (q != nullptr)
		{
			if (q->word == word)
			{
				// If q is at the word we want, return p (the set containing the word)
				return p;
			}

			q = q->nextNeighbor; // Otherwise, move q to the right 
		}

		p = p->nextVertex; // If we didn't find the word in that level of the lists, move down a level and try again
	}

	return nullptr; // If we reach this, we didn't find it so return nullptr
}

void Kruskal::setUnion(node* u, node* v)
{
	// Merges 2 sets that are passed in
	node* p = u; // Node that starts at u, but we are going to move it as far right as we can

	while (p->nextNeighbor != nullptr)
	{
		// While p has a next neighbor, move to that one, so we can
		// drop v on the end of it once we're done
		p = p->nextNeighbor;
	}

	p->nextNeighbor = v; // Add v to the end of p
	
	node* q = head; // Start q at the beginning of the list

	while (q->nextVertex != nullptr)
	{
		// Loop through the vertices, if our next vertex is v,
		// that means we need to make our next vertex v's next vertex
		// because v is no longer a vertex
		if (q->nextVertex == v)
		{
			q->nextVertex = v->nextVertex;
			break;
		}

		q = q->nextVertex; // Continue on to the next vertex is we didn't find it there
	}

	if (head == v)
	{
		// If v was the head before
		head = v->nextVertex; // Make the head v's next vertex
	}

	v->nextVertex = nullptr; // And now v is an interior node, so it doesn't have a next vertex
}

void Kruskal::sortWeightAscending(edge arr[], int p, int r)
{
	// Sort the list of edges from p to r, by weight ascending
	// using the quicksort algorithm
	if (p < r)
	{
		// If p is less than r, partition the array
		int q = partitionWeightAscending(arr, p, r); // And store the pivot index in q
		sortWeightAscending(arr, p, q - 1); // Then, recursively quick sort the left side 
		sortWeightAscending(arr, q + 1, r); // and the right side
	}
}

int Kruskal::partitionWeightAscending(edge arr[], int p, int r)
{
	// Partition the edges array from p to r
	// returning the location of the pivot
	int i = p - 1; // Start i at the beginning of our section - 1, because we increment it immediately
	int j = r; // And j at the end of our section
	edge x = arr[p]; // X is the first edge in the array, which will become our pivot
	do
	{
		do i++; while (arr[i].weight < x.weight); // Increase i, then continue to do it as long as the edge at i's weight is less than that of the pivot
		do j--; while (arr[j].weight > x.weight); // Decrease j, then continue to do so as long as the edge at j's weight is greater than that of the pivot
		if (i < j)
		{
			// If i is less than i and j we want to swap
			// arr[i] <=> arr[j]
			edge temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
		{
			// Otherwise break out of the loop
			break;
		}
	} while (true); // Do this infinitely, i.e. until we hit the break
	// At the end, swap arr[j] <=> arr[p]
	edge temp = arr[p];
	arr[p] = arr[j];
	arr[j] = temp;

	return j; // and return j, the location of the pivot
}

void Kruskal::alphabeticalInsertionSort(edge arr[], int numOfEdges, string nodeVertices[])
{
	// Sort the list of merged edges alphabetically, using insertion sort
	int i, j;
	edge key; 
	for (i = 1; i < numOfEdges; i++)
	{
		// Loop through the edges, starting at element 1
		key = arr[i]; // the key becomes the element at i
		j = i - 1; // and j, lags behind starting at i - 1

		while (j >= 0 && !edgeAlphaCompare(arr[j], key, nodeVertices))
		{
			// While j >= 0 and the edge at arr[j] is greater than the key, using our alphabetical comparison
			arr[j + 1] = arr[j]; // move the item from the arr[j] into arr[j + 1]
			j--; // and decrement j
		}
		arr[j + 1] = key; // Then, make arr[j + 1] the key
	}
}

bool Kruskal::edgeAlphaCompare(edge& edge1, edge& edge2, string nodeVertices[])
{
	// Boolean method that determines the order of the 2 edges alphabetically
	if (nodeVertices[edge1.src] == nodeVertices[edge2.src])
	{
		// If the src of both edges is the same, compare the destinations, returning true if
		// edge1 is less than edge2
		return nodeVertices[edge1.dest] < nodeVertices[edge2.dest];
	}
	else
	{
		// Otherwise, we can do our comparison on the src, returning true if edgge1 is less than edge2
		return nodeVertices[edge1.src] < nodeVertices[edge2.src];
	}
}