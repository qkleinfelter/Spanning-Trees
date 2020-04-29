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
	};

	void insert(const string& word);
	node* minimum();
	node* extractMin();
	void decreaseKey(node* x, int index, node key);
	void minHeapify(int index);
	int parent(int index);
	int left(int index);
	int right(int index);

	int heapLength;
	int heapsize;

	node heap[];

public:
	Prim();
	~Prim();

	void findMST();
};