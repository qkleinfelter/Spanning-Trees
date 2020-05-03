#pragma once
#include <string>
#include "Edge.h"

using namespace std;

class Kruskal
{
private:
	struct node
	{
		string word;
		node* nextNeighbor = nullptr;
		node* nextVertex = nullptr;
	};

	node* head = nullptr;
	void sortWeightAscending(edge arr[], int p, int r);
	int partitionWeightAscending(edge arr[], int p, int r);

public:
	Kruskal();
	~Kruskal();

	void findMST(string* nodeVertices, double** adjMatrix, int numOfNodes);
	void makeSet(const string& word);
	node* findSet(const string& word);
	void setUnion(node* u, node* v);

};