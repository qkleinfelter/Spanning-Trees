#include "Prim.h"
#include <iostream>

using namespace std;

Prim::Prim()
{

}

Prim::~Prim()
{

}

Prim::node* Prim::minimum()
{
	return &heap[1];
}

Prim::node* Prim::extractMin()
{
	if (heapsize < 1)
	{
		cout << "Heap underflow" << endl;
		return;
	}

	node min = heap[1];
	heap[1] = heap[heapsize];
	heapsize -= 1;
	minHeapify(1);
	return &min;
}