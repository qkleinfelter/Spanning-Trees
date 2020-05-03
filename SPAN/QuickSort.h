#pragma once
#include "Edge.h"

using namespace std;

class QuickSort
{
public:
	static void sortWeightAscending(edge arr[], int p, int r);
	static void sortAlphaAscending(edge arr[], int p, int r);
private:
	static int partitionWeightAscending(edge arr[], int p, int r);
	static int partitionAlphaAscending(edge arr[], int p, int r);
};