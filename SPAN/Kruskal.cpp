#include "Kruskal.h";
#include <string>;
#include <iostream>

Kruskal::Kruskal()
{

}

Kruskal::~Kruskal()
{
}

void Kruskal::findMST(string* nodeVertices, double** adjMatrix, int numOfNodes)
{
	for (int i = 0; i < numOfNodes; i++)
	{
		makeSet(nodeVertices[i]);
	}

	edge* edges = new edge[numOfNodes * numOfNodes];
	int currEdge = 0;

	for (int i = 0; i < numOfNodes; i++)
	{
		for (int j = 0; j < numOfNodes; j++)
		{
			double currWeight = adjMatrix[i][j];

			if (currWeight != 0)
			{
				edge p;

				p.src = i;
				p.dest = j;

				p.weight = currWeight;

				edges[currEdge] = p;

				currEdge++;
			}
		}
	}
	// Sort the list of edges in increasing order by weight
	insertionSort(edges, currEdge);

	double totalWeight = 0;

	for (int i = 0; i < currEdge; i++)
	{
		edge& p = edges[i];
		
		node* srcContainer = findSet(nodeVertices[p.src]);
		node* destContainer = findSet(nodeVertices[p.dest]);

		if (srcContainer != destContainer)
		{
			setUnion(srcContainer, destContainer);
			cout << "Merging " << srcContainer->word << " and " << destContainer->word << endl;
			totalWeight += p.weight;
		}
	}

	delete[] edges;
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