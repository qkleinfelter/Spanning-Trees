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
		return nullptr;
	}

	node min = heap[1];
	heap[1] = heap[heapsize];
	heapsize -= 1;
	minHeapify(1);
	return &min;
}

int Prim::left(int index)
{
	return 2 * index;
}

int Prim::right(int index)
{
	return (2 * index) + 1;
}

int Prim::parent(int index)
{
	return index / 2;
}

void Prim::decreaseKey(node* x, int index, node key)
{
	if (key.weight > heap[index].weight)
	{
		cout << "New key value is greater than current key value" << endl;
		return;
	}

	heap[index] = key;

	while (index > 1 && heap[parent(index)].weight > heap[index].weight)
	{
		node temp = heap[index];
		heap[index] = heap[parent(index)];
		heap[parent(index)] = temp;
		index = parent(index);
	}
}

void Prim::insert(const string& word)
{
	heapsize += 1;
	
}

void Prim::minHeapify(int index)
{
	int l = left(index);
	int r = right(index);

	int smallest;

	if (l <= heapsize && heap[l].weight < heap[index].weight)
	{
		smallest = l;
	}
	else
	{
		smallest = index;
	}
	if (r <= heapsize && heap[r].weight < heap[smallest].weight)
	{
		smallest = r;
	}
	if (smallest != index)
	{
		node temp = heap[index];
		heap[index] = heap[smallest];
		heap[smallest] = temp;
		minHeapify(smallest);
	}
}