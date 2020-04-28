#pragma once
#include <string>

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

	struct edge
	{
		unsigned int src;
		unsigned int dest;
		double weight;
	};

	node* head = nullptr;
	void quickSort(edge arr[], int p, int r);
	int qsPartition(edge arr[], int p, int r);
public:
	Kruskal();
	~Kruskal();

	void findMST(string* nodeVertices, double** adjMatrix, int numOfNodes);
	void makeSet(const string& word);
	node* findSet(const string& word);
	void setUnion(node* u, node* v);

};