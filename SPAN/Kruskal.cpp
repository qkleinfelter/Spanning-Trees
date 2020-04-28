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
	quickSort(edges, 0, currEdge);
	
	double totalWeight = 0;

	edge* mergedEdges = new edge[numOfNodes - 1];
	int currMerge = 0;

	for (int i = 0; i < currEdge; i++)
	{
		edge& p = edges[i];
		
		node* srcContainer = findSet(nodeVertices[p.src]);
		node* destContainer = findSet(nodeVertices[p.dest]);

		if (srcContainer != destContainer)
		{
			setUnion(srcContainer, destContainer);
			cout << "Merging " << srcContainer->word << " and " << destContainer->word << endl;
			mergedEdges[currMerge] = p;
			currMerge++;
			totalWeight += p.weight;
		}
	}

	cout << "Printing list of merged edges -- UNSORTED" << endl;
	for (int i = 0; i < currMerge; i++)
	{
		cout << mergedEdges[i].src << "-" << mergedEdges[i].dest << ": " << mergedEdges[i].weight << endl;
	}

	alphaQuickSort(mergedEdges, 0, currMerge - 1, nodeVertices, true);
	alphaQuickSort(mergedEdges, 0, currMerge - 1, nodeVertices, false);

	cout << "Printing list of merged edges -- SORTED" << endl;
	for (int i = 0; i < currMerge; i++)
	{
		cout << mergedEdges[i].src << "-" << mergedEdges[i].dest << ": " << mergedEdges[i].weight << endl;
	}
	//delete[] edges;


	cout << "Total weight: " << totalWeight << endl;

	node* p = head;

	while (p != nullptr)
	{
		node* q = p;
		while (q != nullptr)
		{
			cout << q->word << " ";
			q = q->nextNeighbor;
		}
		cout << endl;
		p = p->nextVertex;
	}
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


void Kruskal::quickSort(edge arr[], int p, int r)
{
	if (p < r)
	{
		int q = qsPartition(arr, p, r);
		quickSort(arr, p, q - 1);
		quickSort(arr, q + 1, r);
	}
}

int Kruskal::qsPartition(edge arr[], int p, int r)
{
	int i = p;
	int j = r;
	edge x = arr[p];
	do
	{
		do i++; while (arr[i].weight < x.weight);
		do j--; while (arr[j].weight > x.weight);
		if (i < j)
		{
			// swap arr[i] and arr[j];
			edge temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
		{
			break;
		}
	} while (true);
	// swap arr[p] and arr[j];
	edge temp = arr[p];
	arr[p] = arr[j];
	arr[j] = temp;
	return j;
}

void Kruskal::alphaQuickSort(edge arr[], int p, int r, string nodeVertices[], bool firstPass)
{
	if (p < r)
	{
		int q = alphaQSPartition(arr, p, r, nodeVertices, firstPass);
		alphaQuickSort(arr, p, q - 1, nodeVertices, firstPass);
		alphaQuickSort(arr, q + 1, r, nodeVertices, firstPass);
	}
}

int Kruskal::alphaQSPartition(edge arr[], int p, int r, string nodeVertices[], bool firstPass)
{
	int i = p;
	int j = r + 1;
	edge x = arr[p];
	do
	{
		if (firstPass)
		{
			cout << nodeVertices[arr[i].src] << " " << nodeVertices[x.src] << " " << arr[j].src << endl;
			do i++; while (nodeVertices[arr[i].src] < nodeVertices[x.src]);
			do j--; while (nodeVertices[arr[j].src] > nodeVertices[x.src]);
		}
		else
		{
			cout << nodeVertices[arr[i].src] << " " << nodeVertices[x.src] << " " << nodeVertices[arr[j].src] << endl;
			do i++; while (nodeVertices[arr[i].dest] < nodeVertices[x.dest]);
			do j--; while (nodeVertices[arr[j].dest] > nodeVertices[x.dest]);
		}
		if (i < j)
		{
			// swap arr[i] and arr[j];
			edge temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
		{
			break;
		}
	} while (true);
	// swap arr[p] and arr[j];
	edge temp = arr[p];
	arr[p] = arr[j];
	arr[j] = temp;
	return j;
}