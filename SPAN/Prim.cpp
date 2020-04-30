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
	heapLength = numOfNodes + 1;
	heap = new node[heapLength];
	heapsize = 0;

	for (int i = 0; i < numOfNodes; i++)
	{
		insert(nodeVertices[i], std::numeric_limits<double>::max());
	}

	decreaseKey(1, 0);

	int totalWeight = 0;

	while (heapsize != 0)
	{
		string minWord = extractMinWord();
		int minRow = -1;
		for (int i = 0; i < numOfNodes; i++)
		{
			if (nodeVertices[i] == minWord)
			{
				minRow = i;
				break;
			}
		}

		for (int i = 0; i < numOfNodes; i++)
		{
			if (weights[minRow][i] != 0)
			{
				const string& vWord = nodeVertices[i];

				node* v = getVertex(vWord);

				if (v != nullptr && weights[minRow][i] < v->weight)
				{
					cout << "Minimum edge is: " << nodeVertices[minRow] << " and lowest adjacent edge is: " << v->word << " with weight: " << weights[minRow][i] << endl;
					v->weight = weights[minRow][i];
					totalWeight += v->weight;
				}
			}
		}
	}
	cout << totalWeight << endl;

	delete[] heap;
	
}

Prim::node* Prim::minimum()
{
	return &heap[1];
}

string Prim::extractMinWord()
{
	if (heapsize < 1)
	{
		cout << "Heap underflow" << endl;
		return nullptr;
	}

	node min = heap[1];
	heap[1] = heap[heapsize];
	heapsize--;
	minHeapify(1);
	return min.word;
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
	if (key > heap[index].weight)
	{
		//cout << "New key value is greater than current key value" << endl;
		return;
	}

	heap[index].weight = key;

	while (index > 1 && heap[parent(index)].weight > heap[index].weight)
	{
		node temp = heap[index];
		heap[index] = heap[parent(index)];
		heap[parent(index)] = temp;
		index = parent(index);
	}
}

void Prim::insert(const string& word, double key)
{
	heapsize++;
	node* newNode = new node();
	newNode->word = word;
	newNode->weight = 50000; // Needs to be a super large number

	heap[heapsize] = *newNode;

	decreaseKey(heapsize, key);
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

Prim::node* Prim::getVertex(const string& word)
{
	for (int i = 1; i <= heapsize; i++)
	{
		if (heap[i].word == word)
		{
			return &heap[1];
		}
	}

	return nullptr;
}