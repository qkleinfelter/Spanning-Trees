#include "Kruskal.h";
#include <string>;

Kruskal::Kruskal()
{

}

Kruskal::~Kruskal()
{
}

Kruskal::nodeList* Kruskal::findMST(nodeList* g, node* w)
{
	return nullptr;
}

void Kruskal::makeSet(char word[WORD_SIZE])
{
	nodeList* newList = new nodeList();

	node* newNode = new node();
	strcpy(newNode->word, word);

	newList->head = newNode;

	if (head == nullptr)
	{
		head = newList;
		return;
	}

	newList->next = head;
	head->prev = newList;

	head = newList;
}

Kruskal::nodeList* Kruskal::findSet(char word[WORD_SIZE])
{
	nodeList* p = head;

	while (p != nullptr)
	{
		node* q = p->head;

		while (q != nullptr)
		{
			if (strcmp(q->word, word) == 0)
			{
				return p;
			}
			q = q->next;
		}
		p = p->next;
	}

	return nullptr;
}

void Kruskal::setUnion(nodeList* u, nodeList* v)
{
}
