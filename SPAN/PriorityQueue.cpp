#include "PriorityQueue.h"
#include <iostream>
using namespace std;

PriorityQueue::PriorityQueue()
{

}

PriorityQueue::~PriorityQueue()
{
}



void PriorityQueue::insert(string name, double weight)
{

}

PriorityQueue::node* PriorityQueue::maximum()
{
	return array[1];
}

PriorityQueue::node* PriorityQueue::extractMax()
{
	if (heapsize < 1)
	{
		cout << "Heap underflow error" << endl;
		return;
	}
	node* max = array[1];
	array[1] = array[heapsize];
	heapsize -= 1;
	maxHeapify(1);
	return max;
}

void PriorityQueue::increaseKey(node* x, int k)
{
}

void PriorityQueue::maxHeapify(int index)
{
}
