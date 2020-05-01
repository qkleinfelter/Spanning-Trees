#pragma once
#include <string>

using namespace std;

class Prim
{
private:
	struct node
	{
		string word;
		double weight;
		string predecessor;
	};

	void insert(const string& word, double key);
	node* minimum();
	node* extractMinNode();
	void decreaseKey(int index, double key);
	void minHeapify(int index);
	int parent(int index);
	int left(int index);
	int right(int index);
	node* getVertex(const string& word);
	node findInNodes(node* nodes, const string& word, int startPos);

	int heapLength;
	int heapsize;

	node* heap;

public:
	Prim();
	~Prim();

	void findMST(string* nodeVertices, double** weights, int numOfNodes);
};