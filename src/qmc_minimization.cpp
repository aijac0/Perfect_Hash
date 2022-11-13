// file: qmc_minimization.cpp
// author: aidan collins
// github: aijac0
// email: aidancollinscs@gmail.com
// Efficient implementation of the Quine-McCluskey
// boolean expression minimization algorithm
// // // // // // // // // // // // // // // // //

#include <vector>
#include <iostream>

using namespace std;


/**
 * Get the rank of a boolean expression
 * Rank is defined as the number of non-negated variables.
 * For example:
 * 		rank(!A * B * C) = rank(011) = 2
 *		rank(!A * !B * !C) = rank(000) = 0
 *		rank(A * B * C) = rank(111) = 3
 * @param exp: Boolean expression to get the rank of
 * @return: Rank of exp
 */
int get_rank(size_t exp)
{
	int rank = 0;
    while (exp > 0)
	{
       	rank++;
        exp = exp & (exp-1);
	}
    return rank;
}


/**
 * Sort the expressions vector by rank in ascending order
 * Sorting algorithm takes advantage of fact that there is a relatively
 * small number of ranks, and the range of possible ranks is known.
 * @param expressions: Expressions vector to be sorted
 * @return: Vector of indices in expressions vector which indicate the starting index
 *          of a rank in expressions specified by the index of the vector itself
 */
vector<size_t> & sort_expressions(vector<size_t> & expressions)
{
	size_t n_in_rank[sizeof(size_t) + 1] = {0};
	
	// Count how many expressions there are of each rank 
	// (to find where to place them in sorted vector)
	for (size_t i = 0; i < expressions.size(); i++)
	{
		n_in_rank[get_rank(expressions[i])]++;
	}

	// For an index i, separation_indices[i] represents the starting
	// index of a specified rank in the expressions vector
	vector<size_t>* separation_indices = new vector<size_t>(sizeof(size_t) + 1, 0);
	for (int i = 0; i < sizeof(size_t); i++)
	{
		(*separation_indices)[i+1] = (*separation_indices)[i] + n_in_rank[i];
	}
	
	// Set n_in_rank equal to separation_indices to mark the current index
	// in expressions for the next expression of rank i
	for (int i = 0; i <= sizeof(size_t); i++)
	{
		n_in_rank[i] = (*separation_indices)[i];
	}

	// Initialize a new vector as the sorted version of expressions
	vector<size_t> sorted_expressions(expressions.size(), 0);
	for (size_t i = 0; i < expressions.size(); i++)
	{
		int rank = get_rank(expressions[i]);
		sorted_expressions[n_in_rank[rank]++] = expressions[i];
	}

	// Set expressions equal to sorted_expressions
	for (size_t i = 0; i < expressions.size(); i++)
	{
		expressions[i] = sorted_expressions[i];
	}

	return *separation_indices;
}


int main()
{
	vector<size_t> expressions = {0, 255, 198, 204, 14, 109, 11, 12, 100, 37, 0, 4, 8, 16, 17, 33, 35};
	vector<size_t> separation_indices = sort_expressions(expressions);
		
	for (int i = 0; i < expressions.size(); i++)
	{
		cout << i << ' ' << expressions[i] << ' ' << get_rank(expressions[i]) << endl;
	}
	cout << endl << separation_indices.size() << endl;
	for (int i = 0; i < separation_indices.size(); i++)
	{
		cout << separation_indices[i] << endl;
	}
	return 0;
}
