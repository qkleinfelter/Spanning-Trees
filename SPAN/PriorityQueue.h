#pragma once
#include <string>

class PriorityQueue
{
private:
	struct node
	{
		string name;
		double weight;
	};
	node* array[10];
	unsigned int length;
	unsigned int heapsize;

public:
	PriorityQueue();
	~PriorityQueue();

	void insert(string name, double weight);
	node* maximum();
	node* extractMax();
	void increaseKey(node* x, int k);
	void maxHeapify();
};