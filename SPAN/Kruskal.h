#pragma once

class Kruskal
{
private:
	static const unsigned int WORD_SIZE = 2;
	struct node
	{
		char word[WORD_SIZE];
		double weight;
		node* nextNeighbor = nullptr;
		node* nextVertex = nullptr;
	};

	node* head = nullptr;

public:
	Kruskal();
	~Kruskal();

	node* findMST();
	void makeSet(char word[WORD_SIZE]);
	node* findSet(char word[WORD_SIZE]);
	void setUnion(node* u, node* v);

};