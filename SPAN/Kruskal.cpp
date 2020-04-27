#include "Kruskal.h";
#include <string>;

Kruskal::Kruskal()
{

}

Kruskal::~Kruskal()
{
}

Kruskal::node* Kruskal::findMST()
{
	node* a = nullptr;
	// Sort the list of edges in increasing order by weight
	// for each edge 
		// if findSet(u) != findSet(v)
			// a = union of u & v
			// setUnion(u,v)
	// return A
}

void Kruskal::makeSet(char word[WORD_SIZE])
{
	node* newNode = new node();
	strcpy(newNode->word, word);

	if (head == nullptr)
	{
		head = newNode;
		return;
	}

	newNode->nextVertex = head;

	head = newNode;
}

Kruskal::node* Kruskal::findSet(char word[WORD_SIZE])
{
	node* p = head;

	while (p != nullptr)
	{
		node* q = p;

		while (q != nullptr)
		{
			if (strcmp(q->word, word) == 0)
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
