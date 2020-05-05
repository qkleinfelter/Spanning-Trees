/*
	Quinn Kleinfelter
	EECS 2520-001 Non Linear Data Structures Spring 2020
	Dr. Thomas
	Last Edited: 5/5/20

	Header file for our shared Edge Struct
	allowing for the 2 different algorithms to run
	and find the minimum spanning tree of a graph.
	This shared header file allows us to avoid 
	excessive code repeating.
*/

#pragma once
struct edge
{
	int src; // The index of the vertex representing the source of the edge, i.e. the beginning.
	int dest;// The index of the vertex representing the destination of the edge, i.e. the end.
	double weight; // The weight of the edge, how much it costs to go between src and dest.
};