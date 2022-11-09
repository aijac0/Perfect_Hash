// File: optimal_tour.cpp
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
#include <cstring>
#include <cassert>

using namespace std;


template <typename IntType>
void get_adjacency(IntType node, IntType *neighbors, size_t n_bits)
{
	for (size_t i = 0; i < n_bits; i++)
	{
		neighbors[i] = node ^ (1ul << i);				// Set the element at each index as node with its ith bit from the right flipped	
	}
}


template <typename IntType>
IntType** initialize_graph(size_t n_bits)
{
	IntType** graph = new IntType*[1 << n_bits];		// Initialize graph to contain 2^n where n is the number of bits in IntType
	for (size_t i = 0; i < (1ul << n_bits); i++)
	{
		graph[i] = new IntType[n_bits];					// Initialize each adjacency array in graph
		get_adjacency<IntType>(i, graph[i], n_bits);
	}
	return graph;
}


template <typename IntType>
void destroy_graph(IntType **graph, size_t n_bits)
{
	for (size_t i = 0; i < (1ul << n_bits); i++)
	{
		delete [] graph[i];									// Free memory for each adjacency array
	}
	delete graph;											// Free memory for graph itself
}


template <typename IntType>
void traverse_helper(IntType node, IntType **graph, bool *visited, IntType *path, size_t depth, size_t n_bits)
{	
	if (depth == (1ul << n_bits))												// If all nodes have been visited
	{
		for (size_t i = 0; i < (1ul << n_bits); i++)							// Output path in binary
		{
			for (int j = n_bits - 1; j >= 0; j--)
			{
				cout << (path[i] & (1 << j) ? 1 : 0);
			}
			cout << endl;
		}
		cout << endl;
	}
	else 																		// If not all nodes have been visited
	{	
		for (size_t i = 0; i < n_bits; i++)											// Iterate over every neighbor of node
		{
			IntType neighbor = graph[node][i];
			if (visited[neighbor] == false)										// Create new branch if neighbor was not visited
			{		
				bool *new_visited = new bool[1 << n_bits];						// Create a new array to represent visited of new branch
				IntType *new_path = new IntType[1 << n_bits];					// Create a new array to represent path of new branch
				memcpy(new_visited, visited, sizeof(bool) * (1 << n_bits));		// Copy visited array to new_visited array
				memcpy(new_path, path, sizeof(IntType) * (1 << n_bits));		// Copy path array to new_path array
				new_visited[neighbor] = true;									// Update new_visited array to set neighbor as visited
				new_path[depth] = neighbor;										// Update new_path array to add neighbor to path
				traverse_helper<IntType>(neighbor, graph, new_visited,
										 new_path, depth + 1, n_bits);			// Call traversal_helper on new branch
			}
		}
	}
	delete [] visited;															// Delete previous visited array
	delete [] path;																// Delete previous path array
}


template <typename IntType>
void traverse(IntType **graph, size_t n_bits)
{	
	bool *visited = new bool[1 << n_bits] {};						// Initialize array indicating whether or node was initialized with all 0's
	IntType *path = new IntType[1 << n_bits];						// Initialize path array
	visited[0] = true;												// Set 0 as the first visited node
	path[0] = (IntType) 0;											// Set 0 as the first node in path
	size_t depth = 1;												// Initialize depth with 1
	traverse_helper<IntType>(0, graph, visited, path, 
							 depth, n_bits);						// Call traversal_helper on master branch
}


int main(int argc, char **argv)
{
	assert(argc > 1);

	// INITIALIZE
	size_t n_bits = argv[1][0] - '0';
	unsigned char **graph = initialize_graph<unsigned char>(n_bits);

	// FUNCTION CALLS
	traverse<unsigned char>(graph, n_bits);

	// DESTROY
	destroy_graph<unsigned char>(graph, n_bits);

	return 0;
}
