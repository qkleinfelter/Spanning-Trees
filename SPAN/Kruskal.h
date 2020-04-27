#pragma once

class Kruskal
{
private:
	static const unsigned int WORD_SIZE = 2;
	struct node
	{
		char word[WORD_SIZE];
		node* next = nullptr;
	};
	struct nodeList
	{
		node* head = nullptr;
		nodeList* prev = nullptr;
		nodeList* next = nullptr;
	};
	nodeList* head = nullptr;
public:
	Kruskal();
	~Kruskal();

	nodeList* findMST(nodeList* g, node* w);
	void makeSet(char word[WORD_SIZE]);
	nodeList* findSet(char word[WORD_SIZE]);
	void setUnion(nodeList* u, nodeList* v);

};