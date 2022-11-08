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
vector<IntType> possible_neighbors(IntType node)
{
	vector<IntType> neighbors(sizeof(IntType) * 8); 	// Initialize neighbors vector to include all variations
	for (int i = 0; i < sizeof(IntType) * 8; i++)
	{
		neighbors[i] = node ^ (1 << i);					// Set the element at each index as node with its ith bit from the right flipped	
	}
	return neighbors;
}



int main()
{
	unsigned int node = 15;
	for (unsigned int variation : possible_neighbors(node))
	{
		cout << variation << endl;
	}
}
