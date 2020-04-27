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

	struct path
	{
		node* left = nullptr;
		node* right = nullptr;
		double weight = 0;
	};

	node* head = nullptr;

public:
	Kruskal();
	~Kruskal();

	node* findMST(string* nodeVertices, double** weights, int numOfNodes);
	void makeSet(string word);
	node* findSet(string word);
	void setUnion(node* u, node* v);

};