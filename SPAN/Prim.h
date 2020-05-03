#pragma once
#include <string>
#include "Edge.h"

using namespace std;

class Prim
{
private:

	edge* extractMinNode();
	void decreaseKey(int index, double key);
	void minHeapify(int index);
	int parent(int index);
	int left(int index);
	int right(int index);
	int findInQueue(edge* p);

	int heapLength;
	int heapsize;

	edge* nodes;
	edge** heap;

	void alphabeticalInsertionSort(edge arr[], int numOfEdges, string nodeVertices[]);
	bool edgeAlphaCompare(edge& edge1, edge& edge2, string nodeVertices[]);
public:
	Prim();
	~Prim();

	void findMST(string* nodeVertices, double** weights, int numOfNodes);
};