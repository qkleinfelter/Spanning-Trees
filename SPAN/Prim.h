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

	void insert(const string& word, double key);
	node* minimum();
	string extractMinWord();
	void decreaseKey(int index, double key);
	void minHeapify(int index);
	int parent(int index);
	int left(int index);
	int right(int index);
	node* getVertex(const string& word);

	int heapLength;
	int heapsize;

	node* heap;

public:
	Prim();
	~Prim();

	void findMST(string* nodeVertices, double** weights, int numOfNodes);
};