#include "Prim.h"
#include <iostream>

using namespace std;

Prim::Prim()
{

}

Prim::~Prim()
{

}

void Prim::findMST(string* nodeVertices, double** weights, int numOfNodes)
{
	nodes = new node[numOfNodes];

	heapLength = numOfNodes + 1;

	heap = new node * [heapLength];
	heapsize = 0;

	for (int i = 0; i < numOfNodes; i++)
	{
		node newNode;
		newNode.word = nodeVertices[i];
		newNode.weight = std::numeric_limits<double>::max();
		newNode.predecessor = "";
		nodes[i] = newNode;
		heap[i + 1] = &nodes[i];
		heapsize++;
	}

	decreaseKey(1, 0);

	while (heapsize != 0)
	{
		node* u = extractMinNode();

		int uIndex = u - &nodes[0]; 

		for (int i = 0; i < numOfNodes; i++)
		{
			if (weights[uIndex][i] != 0)
			{
				const string& vWord = nodeVertices[i];

				node* v = &nodes[i];

				int posInQueue = findInQueue(v);

				if (posInQueue != 0 && weights[uIndex][i] < v->weight)
				{
					double newWeight = weights[uIndex][i];
					v->predecessor = u->word;
					decreaseKey(posInQueue, newWeight);
				}
			}
		}
	}

	double totalWeight = 0;

	for (int i = 0; i < numOfNodes; i++)
	{
		node& p = nodes[i];

		if (p.predecessor != "")
		{
			cout << p.word << "-" << p.predecessor << ": " << p.weight << endl;
			totalWeight += p.weight;
		}
	}

	cout << totalWeight << endl;

	delete[] nodes;
	delete[] heap;
}

Prim::node* Prim::extractMinNode()
{
	if (heapsize < 1)
	{
		cout << "Heap underflow" << endl;
		return nullptr;
	}

	node* min = heap[1];
	heap[1] = heap[heapsize];
	heapsize--;
	minHeapify(1);
	return min;
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

void Prim::decreaseKey(int index, double key)
{
	node* p = heap[index];
	if (key > p->weight)
	{
		cout << "New key value is greater than current key value" << endl;
		return;
	}

	p->weight = key;

	while (index > 1 && heap[parent(index)]->weight > heap[index]->weight)
	{
		node* temp = heap[index];
		heap[index] = heap[parent(index)];
		heap[parent(index)] = temp;
		index = parent(index);
	}
}


void Prim::minHeapify(int index)
{
	int l = left(index);
	int r = right(index);
	int smallest;

	if (l <= heapsize && heap[l]->weight < heap[index]->weight)
	{
		smallest = l;
	}
	else
	{
		smallest = index;
	}

	if (r <= heapsize && heap[r]->weight < heap[smallest]->weight)
	{
		smallest = r;
	}

	if (smallest != index)
	{
		node* temp = heap[index];
		heap[index] = heap[smallest];
		heap[smallest] = temp;
		minHeapify(smallest);
	}
}

int Prim::findInQueue(node* p)
{
	for (int i = 1; i <= heapsize; i++)
	{
		if (heap[i] == p) return i;
	}

	return 0;
}