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
	void insertionSort(edge arr[], int n);
public:
	Kruskal();
	~Kruskal();

	node* findMST(string* nodeVertices, double** weights, int numOfNodes);
	void makeSet(const string& word);
	node* findSet(const string& word);
	void setUnion(node* u, node* v);

};