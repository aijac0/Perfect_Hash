// File: optimal_sequence.cpp
// Author: Aidan Collins
// Github: aijac0
// Email: aidancollinscs@gmail.com
// The goal of this file is to find an algorithm for creating a sequence of
// integer which encompasses all possible values, and where each consecutive 
// integer has only one changed bit from the previous.
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


template <typename IntType>
IntType** initialize_graph()
{
	IntType* graph = new IntType[1 << sizeof(IntType) * 8];		// Initialize graph to contain 2^n where n is the number of bits in IntType
	for (int i = 0; i < 1 << sizeof(IntType) * 8; i++)
	{
		graph[i] = new IntType[sizeof(IntType) * 8];			// Initialize each adjacency array in graph
		get_adjacency(i, graph[i]);
	}
	return graph;
}


template <typename IntType>
void get_adjacency(IntType node, IntType* neighbors)
{
	for (int i = 0; i < sizeof(IntType) * 8; i++)
	{
		neighbors[i] = node ^ (1 << i);					// Set the element at each index as node with its ith bit from the right flipped	
	}
}


template <typename IntType>
void destroy_graph(IntType** graph)
{
	for (int i = 0; i < 1 << sizeof(IntType) * 8; i++)
	{
		free [] graph[i];									// Free memory for each adjacency array
	}
	free graph;												// Free memory for graph itself
}


int main()
{
	unsigned int node = 15;
	for (unsigned int variation : possible_neighbors(node))
	{
		cout << variation << endl;
	}
}
