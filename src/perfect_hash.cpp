// file: perfect_hash.cpp
// author: aidan collins
// github: aijaco
// email: aidancollinscs@gmail.com
// Main file for the perfect_hash repo
// // // // // // // // // // // // // //

#include <iostream>
#include "hashtable.h"

using namespace std;


int main(int argc, char **argv)
{
	// Error checking
	if (argc != 2) return 1;

	// Initialize variables
	size_t max = atoi(argv[1]);
	HashTable<int> table;	

	// Insert "random" inputs to table
	for (size_t i = 0; i < max; i++) 
	{
		table.insert((i << 12) % 7001);
	}

	// Ensure inputs are in table
	for (size_t i = 0; i < max; i++)
	{	
		if (!(table.search((i << 12) % 7001)))
		{
			cout << "ERROR" << endl;
			return 1;
		}
	}
	cout << "Success" << endl;
	return 0;
}
