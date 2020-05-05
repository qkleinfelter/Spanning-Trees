#include <fstream>
#include <iostream>
#include "Kruskal.h"
#include "Prim.h"

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

	//cout << "Creating " << numOfNodes << " nodes for the graph";

	string* nodeVertices = new string[numOfNodes];
	
	for (int i = 0; i < numOfNodes; i++)
	{
		inputStream >> nodeVertices[i];
		//cout << "Node Name: " << nodeVertices[i] << endl;
	}
	

	double** adjMatrix = new double*[numOfNodes];

	for (int i = 0; i < numOfNodes; i++)
	{
		adjMatrix[i] = new double[numOfNodes];
	}

	for (int i = 0; i < numOfNodes; i++)
	{
		for (int j = 0; j < numOfNodes; j++)
		{
			inputStream >> adjMatrix[i][j];	

			//cout << adjMatrix[i][j] << " ";
		}
		//cout << endl;
	}

	Kruskal* kruskal = new Kruskal();
	cout << "Kruskals:" << endl;
	
	kruskal->findMST(nodeVertices, adjMatrix, numOfNodes);

	delete kruskal;

	cout << "---------------------------" << endl;

	Prim* prim = new Prim();
	cout << "Prims:" << endl;

	prim->findMST(nodeVertices, adjMatrix, numOfNodes);

	delete prim;

	delete[] nodeVertices;

	for (int i = 0; i < numOfNodes; i++)
	{
		delete[] adjMatrix[i];
	}
	
	delete[] adjMatrix;

	inputStream.close();
}