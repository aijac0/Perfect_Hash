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
 * Determine whether or not a number is a power of 2.
 * Aka quickly determine whether or not the rank of n is 1.
 * @param n: Number to check 
 * @return: Whether or not n is a power of 2 / rank 1
 */
bool is_power_of_2(size_t n)
{
	return !(n & (n - 1));
}


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
 * @param masks: Masks for expressions to sort in the same exact order
 * @param separation_indices: Indices in expressions vector to initialize indicating
 *               the starting index of each rank in expressions.
 */
void sort_expressions(vector<size_t> & expressions, vector<size_t> & masks, vector<size_t> & separations,
					  vector<size_t> & expressions_temp, vector<size_t> & masks_temp)
{
	vector<size_t> n_in_rank(sizeof(size_t) * 8 + 1, 0);
	
	// Count how many expressions there are of each rank 
	// (to find where to place them in sorted vector)
	for (size_t i = 0; i < expressions.size(); i++)
	{
		n_in_rank[get_rank(expressions[i] & masks[i])]++;
	}

	// For an index i, separation_indices[i] represents the starting
	// index of a specified rank in the expressions vector
	separations[0] = 0;
	for (int i = 0; i < sizeof(size_t) * 8; i++)
	{
		separations[i + 1] = separations[i] + n_in_rank[i];
		n_in_rank[i] = separations[i];
	}
	n_in_rank[sizeof(size_t) * 8] = separations[sizeof(size_t) * 8];

	// Set temp vectors to the sorted contents of expressions and masks
	for (size_t i = 0; i < expressions.size(); i++)
	{
		int rank = get_rank(expressions[i] & masks[i]);
		size_t index = n_in_rank[rank]++;
		expressions_temp[index] = expressions[i];
		masks_temp[index] = masks[i];
	}

	// Swap temp contents with regular contents
	expressions.swap(expressions_temp);
	masks.swap(masks_temp);
}


void qmc_minimization_helper(vector<size_t> & expressions, vector<size_t> & masks, vector<size_t> & separations,
					  		 vector<size_t> & expressions_temp, vector<size_t> & masks_temp, vector<size_t> & separations_temp)
{	
	expressions_temp.clear();
	masks_temp.clear();
	for (int s = 0; s < separations.size() - 1; s++)
	{
		const int g1_start = separations[s];
		const int g2_start = separations[s+1];
		const int g3_start = (s == (separations.size() - 2))
					   		  ? expressions.size() : separations[s+2];
		
		separations_temp[s+1] = separations_temp[s];
		for (int g1 = g1_start; g1 < g2_start; g1++)
		{
			for (int g2 = g2_start; g2 < g3_start; g2++)
			{
				if (masks[g1] == masks[g2])
				{
					size_t diff = (expressions[g1] ^ expressions[g2]) & masks[g1];
					if (is_power_of_2(diff))
					{
						expressions_temp.push_back(expressions[g1]);
						masks_temp.push_back(masks[g1] ^ diff);
						separations_temp[s+1]++; 
					}
				}
			}
		}
	}
	
	if (!expressions_temp.empty())
	{
		expressions.swap(expressions_temp);
		masks.swap(masks_temp);
		separations.swap(separations_temp);
		qmc_minimization_helper(expressions, masks, separations, expressions_temp, masks_temp, separations_temp);
	}
}


void qmc_minimization(vector<size_t> & expressions, vector<size_t> & masks)
{
	// Initialize necessary vectors
	vector<size_t> expressions_temp(expressions.size(), 0);
	vector<size_t> masks_temp(masks.size(), 0);
	vector<size_t> separations(sizeof(size_t) * 8 + 1, 0);
	vector<size_t> separations_temp(sizeof(size_t) * 8 + 1, 0);

	// Sort the ordering of expressions
	sort_expressions(expressions, masks, separations, expressions_temp, masks_temp);
	
	// Minimize expressions
	//qmc_minimization_helper(expressions, masks, separations, expressions_temp, masks_temp, separations_temp);
}


int main()
{
	// Initialize variables
	vector<size_t> expressions = {0, 255, 198, 204, 14, 109, 11, 12, 100, 37, 0, 4, 8, 16, 17, 33, 35};
	vector<size_t> masks(expressions.size(), ~((size_t) 0));

	// Show initialized data info
	cout << "expressions (size = " << expressions.size() << ", capacity = " << expressions.capacity() << ")"  << endl;
	cout << "masks (size = " << masks.size() << ", capacity = " << masks.capacity() << ")"  << endl;

	// Sort expressions
	cout << endl << "Minimizing..." << endl << endl;
	qmc_minimization(expressions, masks);

	// Show sorted data info
	cout << "expressions (size = " << expressions.size() << ", capacity = " << expressions.capacity() << ")"  << endl;
	cout << "masks (size = " << masks.size() << ", capacity = " << masks.capacity() << ")"  << endl;
	for (int i = 0; i < expressions.size(); i++) 
	{
		cout << i << ' ';
		for (int j = 15; j >= 0; j--)
		{
			cout << (expressions[i] & (1 << j) ? '1' : '0');
		}
		cout << ' ';
		for (int j = 15; j >= 0; j--)
		{
			cout << (masks[i] & (1 << j) ? '1' : '0');
		}
		cout << endl;
	}
	return 0;		
}
