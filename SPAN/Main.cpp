/*
	Quinn Kleinfelter
	EECS 2510-001 Non Linear Data Structures Spring 2020
	Dr. Thomas
	Last Edited: 5/5/20

	Main class to run through Kruskal's and Prim's algorithms 
	on the graph specified by the input file
*/

#include <fstream>
#include <iostream>
#include "Kruskal.h"
#include "Prim.h"

using namespace std;

void readGraphFile(string graphPath); // method we use inside main

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		// If we don't have EXACTLY 2 arguments (SPAN.exe graphfile)
		// then error out
		cout << "Incorrect number of arguments provided" << endl;
		cout << "Usage: SPAN graphFile" << endl;

		return 0;
	}

	readGraphFile(argv[1]); // Read in the graph file and do work on it

	return 0;
}

void readGraphFile(string graphPath)
{
	// Read in the graph file and work on it
	ifstream inputStream; // inputStream to hold the file
	
	inputStream.open(graphPath); // open up the passed in file
	
	if (inputStream.fail())
	{
		// If we couldn't open the file, error out and exit
		cout << "Graph File failed to open" << endl;
		exit(0);
	}

	unsigned int numOfNodes; // Holder for the number of nodes

	inputStream >> numOfNodes; // Grab the number of nodes from the input stream, its always the first character in a valid file

	string* nodeVertices = new string[numOfNodes]; // Initialize the nodeVertices array to be of the size of numOfNodes
	
	for (int i = 0; i < numOfNodes; i++)
	{
		// Grab a node name numOfNodes times and put it into the nodeVertices array from the input stream
		inputStream >> nodeVertices[i];
	}

	double** adjMatrix = new double*[numOfNodes]; // Initialize our adjancecy matrix to be a 2d array of size numOfNodes x numOfNodes

	for (int i = 0; i < numOfNodes; i++)
	{
		// Finish adjancecy matrix 2d array initialization
		adjMatrix[i] = new double[numOfNodes];
	}

	for (int i = 0; i < numOfNodes; i++)
	{
		for (int j = 0; j < numOfNodes; j++)
		{
			// Loop through the passed in adjancecy matrix
			// putting the appropriate spot into the 2d array
			inputStream >> adjMatrix[i][j];	
		}
	}

	Kruskal* kruskal = new Kruskal(); // Initialize our Kruskal's variable
	cout << "Kruskals:" << endl; // Output labelling
	
	kruskal->findMST(nodeVertices, adjMatrix, numOfNodes); // Find the mst using Kruskals passing in nodeVertices, adjMatrix, and numOfNodes

	delete kruskal; // Now we can delete our kruskals variable

	cout << "---------------------------" << endl; // Output separation

	Prim* prim = new Prim(); // Initialize our Prim's variable
	cout << "Prims:" << endl; // Output labelling

	prim->findMST(nodeVertices, adjMatrix, numOfNodes); // Find the mst using Prims passing in nodeVertices, adjMatrix. and numOfNodes

	delete prim; // Now we can delete out prims variable

	delete[] nodeVertices; // and we can delete nodeVertices

	for (int i = 0; i < numOfNodes; i++)
	{
		delete[] adjMatrix[i]; // Loop through deleting the smaller arrays in the adjancecy matrix
	}
	
	delete[] adjMatrix; // and the main array

	inputStream.close(); // Close out the input file
}