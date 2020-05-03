#include "QuickSort.h"

void QuickSort::sortWeightAscending(edge arr[], int p, int r)
{
	if (p < r)
	{
		int q = partitionWeightAscending(arr, p, r);
		sortWeightAscending(arr, p, q - 1);
		sortWeightAscending(arr, q + 1, r);
	}
}

int QuickSort::partitionWeightAscending(edge arr[], int p, int r)
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