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

	Kruskal* kruskalGraph = new Kruskal();

	readGraphFile(argv[1], kruskalGraph);

	delete kruskalGraph;
	return 0;
}

void readGraphFile(string graphPath, Kruskal* kGraph)
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

	char nodeId[2];

	for (int i = 0; i < numOfNodes; i++)
	{
		inputStream >> nodeId;

		cout << "Creating node " << nodeId << " now." << endl;

		kGraph->makeSet(nodeId);
	}

	double weight;

	for (int i = 0; i < numOfNodes; i++)
	{
		cout << "Adjacency list for the " << i << "th node from the file" << endl;

		for (int j = 0; j < numOfNodes; j++)
		{
			inputStream >> weight;
			
			cout << "Node i has a path of weight " << weight << " to node j" << endl;
		}
	}

	inputStream.close();
}