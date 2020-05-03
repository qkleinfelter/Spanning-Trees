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
	nodes = new edge[numOfNodes];

	heapLength = numOfNodes + 1;

	heap = new edge * [heapLength];
	heapsize = 0;

	for (int i = 0; i < numOfNodes; i++)
	{
		edge newNode;
		newNode.src = i;
		newNode.weight = std::numeric_limits<double>::max();
		newNode.dest = i;
		nodes[i] = newNode;
		heap[i + 1] = &nodes[i];
		heapsize++;
	}

	decreaseKey(1, 0);

	while (heapsize != 0)
	{
		edge* u = extractMinNode();

		int uIndex = u - &nodes[0]; 

		for (int i = 0; i < numOfNodes; i++)
		{
			if (weights[uIndex][i] != 0)
			{
				const string& vWord = nodeVertices[i];

				edge* v = &nodes[i];

				int posInQueue = findInQueue(v);

				if (posInQueue != 0 && weights[uIndex][i] < v->weight)
				{
					double newWeight = weights[uIndex][i];
					v->dest = uIndex;
					decreaseKey(posInQueue, newWeight);
				}
			}
		}
	}

	for (int i = 0; i < numOfNodes; i++)
	{
		edge& currEdge = nodes[i];

		if (nodeVertices[currEdge.src] > nodeVertices[currEdge.dest])
		{
			int temp = currEdge.src;
			currEdge.src = currEdge.dest;
			currEdge.dest = temp;
		}
	}

	alphabeticalInsertionSort(nodes, numOfNodes, nodeVertices);

	double totalWeight = 0;

	for (int i = 0; i < numOfNodes; i++)
	{
		edge& p = nodes[i];

		if (p.dest != p.src)
		{
			totalWeight += p.weight;
		}
	}

	cout << totalWeight << endl;

	for (int i = 0; i < numOfNodes; i++)
	{
		edge& p = nodes[i];

		if (p.dest != p.src)
		{
			cout << nodeVertices[p.src] << "-" << nodeVertices[p.dest] << ": " << p.weight << endl;
		}
	}

	delete[] nodes;
	delete[] heap;
}

edge* Prim::extractMinNode()
{
	if (heapsize < 1)
	{
		cout << "Heap underflow" << endl;
		return nullptr;
	}

	edge* min = heap[1];
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
	edge* p = heap[index];
	if (key > p->weight)
	{
		cout << "New key value is greater than current key value" << endl;
		return;
	}

	p->weight = key;

	while (index > 1 && heap[parent(index)]->weight > heap[index]->weight)
	{
		edge* temp = heap[index];
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
		edge* temp = heap[index];
		heap[index] = heap[smallest];
		heap[smallest] = temp;
		minHeapify(smallest);
	}
}

int Prim::findInQueue(edge* p)
{
	for (int i = 1; i <= heapsize; i++)
	{
		if (heap[i] == p) return i;
	}

	return 0;
}

void Prim::alphabeticalInsertionSort(edge arr[], int numOfEdges, string nodeVertices[])
{
	int i, j;
	edge key;
	for (i = 1; i < numOfEdges; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && !edgeAlphaCompare(arr[j], key, nodeVertices))
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

bool Prim::edgeAlphaCompare(edge& edge1, edge& edge2, string nodeVertices[])
{
	if (nodeVertices[edge1.src] == nodeVertices[edge2.src])
	{
		return nodeVertices[edge1.dest] < nodeVertices[edge2.dest];
	}
	else
	{
		return nodeVertices[edge1.src] < nodeVertices[edge2.src];
	}
}