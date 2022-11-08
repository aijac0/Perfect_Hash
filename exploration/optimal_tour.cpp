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
#include <cstring>

using namespace std;

template <typename IntType>
void get_adjacency(IntType node, IntType *neighbors)
{
	for (size_t i = 0; i < (sizeof(IntType) * 8); i++)
	{
		neighbors[i] = node ^ (1 << i);					// Set the element at each index as node with its ith bit from the right flipped	
	}
}


template <typename IntType>
IntType** initialize_graph()
{
	IntType** graph = new IntType*[1 << sizeof(IntType) * 8];		// Initialize graph to contain 2^n where n is the number of bits in IntType
	for (size_t i = 0; i < (1 << (sizeof(IntType) * 8)); i++)
	{
		graph[i] = new IntType[sizeof(IntType) * 8];			// Initialize each adjacency array in graph
		get_adjacency<IntType>(i, graph[i]);
	}
	return graph;
}


template <typename IntType>
void destroy_graph(IntType **graph)
{
	for (size_t i = 0; i < (1 << sizeof(IntType) * 8); i++)
	{
		delete [] graph[i];									// Free memory for each adjacency array
	}
	delete graph;											// Free memory for graph itself
}


template <typename IntType>
void traverse_helper(IntType node, IntType **graph, bool *visited, IntType *path, size_t depth, vector<IntType*> & successful_paths)
{	
	bool finished = true;																	// Indicates whether all the neighbors of node have been visited 
	for (size_t i = 0; i < sizeof(IntType) * 8; i++)										// Iterate over every neighbor of node
	{
		IntType neighbor = graph[node][i];
		if (visited[neighbor] == false)														// Create new branch if neighbor was not visited
		{		
			finished = false;																// Set finished boolean to false
			bool *new_visited = new bool[1 << (sizeof(IntType) * 8)];						// Create a new array to represent visited of new branch
			IntType *new_path = new IntType[1 << (sizeof(IntType) * 8)];					// Create a new array to represent path of new branch
			memcpy(new_visited, visited, sizeof(bool) * (1 << (sizeof(IntType) * 8)));		// Copy visited array to new_visited array
			memcpy(new_path, path, sizeof(IntType) * (1 << (sizeof(IntType) * 8)));			// Copy path array to new_path array
			new_visited[neighbor] = true;													// Update new_visited array to set neighbor as visited
			new_path[depth] = neighbor;														// Update new_path array to add neighbor to path
			traverse_helper<IntType>(neighbor, graph, new_visited,
 									 new_path, depth + 1, successful_paths);				// Call traversal_helper on new branch
		}
	}
	delete [] visited;																		// Delete previous visited array
	if (finished && depth >= (1 << (sizeof(IntType) * 8)) - 1 )								// If all nodes have been visited
	{
		successful_paths.push_back(path);													// Add path to successful paths
	}
	else																					// If not all nodes have been visited
	{
		delete [] path;																		// Delete previous path array
	}
}


template <typename IntType>
vector<IntType*> traverse(IntType **graph)
{	
	vector<IntType*> successful_paths;												// Create vector to hold successful path arrays
	bool *visited = new bool[1 << (sizeof(IntType) * 8)] {};						// Initialize array indicating whether or node was initialized with all 0's
	IntType *path = new IntType[1 << (sizeof(IntType) * 8)];						// Initialize path array
	visited[0] = true;																// Set 0 as the first visited node
	path[0] = (IntType) 0;															// Set 0 as the first node in path
	size_t depth = 1;																// Initialize depth with 1
	traverse_helper<IntType>(0, graph, visited, path, depth, successful_paths);		// Call traversal_helper on master branch
	return successful_paths;
}


int main()
{

	// INITIALIZE
	unsigned char **graph = initialize_graph<unsigned char>();

	// FUNCTION CALLS
	vector<unsigned char*> successful_paths = traverse<unsigned char>(graph);

	// OUTPUT
	for (unsigned char* path : successful_paths)
	{
		for (size_t i = 0; i < (1 << (sizeof(unsigned char) * 8)); i++)
		{
			cout << path[i] << endl;
		}
		cout << endl;
	}

	// DESTROY
	destroy_graph<unsigned char>(graph);

	return 0;
}
