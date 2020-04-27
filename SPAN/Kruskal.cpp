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

void Kruskal::makeSet(string word)
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

Kruskal::node* Kruskal::findSet(string word)
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

}
