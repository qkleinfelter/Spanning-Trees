#include <fstream>
#include <iostream>
#include "Kruskal.h"

using namespace std;

void readGraphFile(string graphPath);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Incorrect number of arguments provided" << endl;
		cout << "Usage: SPAN graphFile" << endl;

		return 0;
	}

	readGraphFile(argv[1]);

	return 0;
}

void readGraphFile(string graphPath)
{
	ifstream inputStream;
	
	inputStream.open(graphPath);

	if (inputStream.fail())
	{
		cout << "Graph File failed to open" << endl;
		exit(0);
	}

	unsigned int numOfNodes;

	inputStream >> numOfNodes;

	cout << "Creating " << numOfNodes << " nodes for the graph";

	string* nodeVertices = new string[numOfNodes];

	for (int i = 0; i < numOfNodes; i++)
	{
		inputStream >> nodeVertices[i];
		cout << "Node Name: " << nodeVertices[i] << endl;
	}

	double** weights = new double*[numOfNodes];

	for (int i = 0; i < numOfNodes; i++)
	{
		weights[i] = new double[numOfNodes];
	}

	for (int i = 0; i < numOfNodes; i++)
	{
		for (int j = 0; j < numOfNodes; j++)
		{
			inputStream >> weights[i][j];	

			cout << weights[i][j] << " ";
		}
		cout << endl;
	}

	Kruskal kruskal;
	
	kruskal.findMST(nodeVertices, weights, numOfNodes);

	delete[] nodeVertices;

	for (int i = 0; i < numOfNodes; i++)
	{
		delete[] weights[i];
	}
	
	delete[] weights;

	inputStream.close();
}