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

	node* extractMinNode();
	void decreaseKey(int index, double key);
	void minHeapify(int index);
	int parent(int index);
	int left(int index);
	int right(int index);
	int findInQueue(node* p);

	int heapLength;
	int heapsize;

	node* nodes;
	node** heap;

public:
	Prim();
	~Prim();

	void findMST(string* nodeVertices, double** weights, int numOfNodes);
};