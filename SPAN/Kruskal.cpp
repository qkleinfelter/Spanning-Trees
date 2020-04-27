#include "Kruskal.h";
#include <string>;

Kruskal::Kruskal()
{

}

Kruskal::~Kruskal()
{
}

Kruskal::node* Kruskal::findMST(string* nodeVertices, double** weights, int numOfNodes)
{
	node* a = nullptr;
	// Sort the list of edges in increasing order by weight
	// for each edge 
		// if findSet(u) != findSet(v)
			// a = union of u & v
			// setUnion(u,v)
	// return A
}

void Kruskal::makeSet(const string& word)
{
	node* newNode = new node();

	newNode->word = word;

	if (head == nullptr)
	{
		head = newNode;
		return;
	}

	newNode->nextVertex = head;

	head = newNode;
}

Kruskal::node* Kruskal::findSet(const string& word)
{
	node* p = head;

	while (p != nullptr)
	{
		node* q = p;

		while (q != nullptr)
		{
			if (q->word == word)
			{
				return p;
			}

			q = q->nextNeighbor;
		}

		p = p->nextVertex;
	}

	return nullptr;
}

void Kruskal::setUnion(node* u, node* v)
{
	node* p = u;

	while (p->nextNeighbor != nullptr)
	{
		p = p->nextNeighbor;
	}

	p->nextNeighbor = v;
	
	node* q = head;

	while (q->nextVertex != nullptr)
	{
		if (q->nextVertex == v)
		{
			q->nextVertex = v->nextVertex;
			break;
		}

		q = q->nextVertex;
	}

	if (head == v)
	{
		head = v->nextVertex;
	}

	v->nextVertex = nullptr;
}


void Kruskal::insertionSort(edge arr[], int n)
{
	edge key;
	int j;
	for (int i = 1; i < n; i++)
	{
		key = arr[i];
		j = i;

		while (j > 0 && arr[j - 1].weight > key.weight)
		{
			arr[j] = arr[j - 1];
			j--;
		}

		arr[j] = key;
	}
}