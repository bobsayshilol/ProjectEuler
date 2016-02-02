/**
 * Maximum path sum I
 * 
 * By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
 * 3
 * 7 4
 * 2 4 6
 * 8 5 9 3
 * That is, 3 + 7 + 4 + 9 = 23.
 * Find the maximum total from top to bottom of the triangle below:
 * 75
 * 95 64
 * 17 47 82
 * 18 35 87 10
 * 20 04 82 47 65
 * 19 01 23 75 03 34
 * 88 02 77 73 07 63 67
 * 99 65 04 28 06 16 70 92
 * 41 41 26 56 83 40 80 70 33
 * 41 48 72 33 47 32 37 16 94 29
 * 53 71 44 65 25 43 91 52 97 51 14
 * 70 11 33 28 77 73 17 78 39 68 17 57
 * 91 71 52 38 17 14 91 43 58 50 27 29 48
 * 63 66 04 68 89 53 67 30 73 16 69 87 40 31
 * 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
 * NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
 */

/**
 * Make the graph node based, then keep track of each current total on the node.
 * As you traverse down, compare the current nodes total to all other nodes and change to the node that's the largest.
 */



// Common includes
#include "common.h"



// A node in the triangle
struct TriangleNode {
	// The parsing phase
	
	// The value in the triangle
	uint64_t mValue;
	
	// The child nodes
	TriangleNode * mLeftChild;
	TriangleNode * mRightChild;
	
	// The parent nodes
	TriangleNode * mLeftParent;
	TriangleNode * mRightParent;
	
	
	// The traversal phase
	
	// The current total
	uint64_t mTotal;
	
	// The parent which the total was calculated from
	TriangleNode * mTotalParent;
};



// A function to parse a triangle
static TriangleNode * ParseTriangle(const uint64_t * triangle, const size_t& elements, const size_t& rows, const uint64_t& max)
{
	// Create a vector to store these in so we can find parents easily
	TriangleNode ** nodes = (TriangleNode**)malloc(elements * sizeof(TriangleNode*));
	
	// Populate the vector
	for (size_t i = 0; i < elements; i++)
	{
		// Create a blank node
		TriangleNode * node = (TriangleNode*)malloc(sizeof(TriangleNode));
		memset(node, 0, sizeof(*node));
		
		// Add it to the nodes list
		nodes[i] = node;
	}
	
	// Helpful macro
#define NODE_INDEX(row, column) (((row) * ((row) + 1)) / 2 + (column))
	
	// Go through each row
	for (size_t row = 0; row < rows; row++)
	{
		// And then each column
		for (size_t column = 0; column <= row; column++)
		{
			// Get the index
			const size_t index = NODE_INDEX(row, column);
			
			// Get the node
			TriangleNode * node = nodes[index];
			
			// Set the value
			// We take away the value from max so that we are looking for the smallest sum
			node->mValue = max - triangle[index];
			
			// Set the parents
			if (row != 0)
			{
				if (column != 0)
					node->mLeftParent = nodes[NODE_INDEX(row-1, column-1)];
				if (column != row)
					node->mRightParent = nodes[NODE_INDEX(row-1, column)];
			}
			
			// Set the children
			if (row != rows - 1)
			{
				node->mLeftChild = nodes[NODE_INDEX(row+1, column)];
				node->mRightChild = nodes[NODE_INDEX(row+1, column+1)];
			}
		}
	}
	
	// Make sure we grab this before freeing it
	TriangleNode * root = nodes[NODE_INDEX(0, 0)];
	
	// Free the node vector
	free(nodes);
	
	// Return the root node
	return root;
	
#undef NODE_INDEX
}



// A function to recursively free nodes
static void FreeNodes(TriangleNode * root)
{
	// Set the parents first
	if (root->mRightParent != nullptr)
	{
		root->mRightParent->mLeftChild = nullptr;
	}
	if (root->mLeftParent != nullptr)
	{
		root->mLeftParent->mRightChild = nullptr;
	}
	
	// Then recursively free the nodes
	if (root->mLeftChild != nullptr)
	{
		FreeNodes(root->mLeftChild);
	}
	if (root->mRightChild != nullptr)
	{
		FreeNodes(root->mRightChild);
	}
	
	// Then clear ourself
	free(root);
}



// A function to get the shortest path between the nodes
static uint64_t GetShortestPath(TriangleNode * node)
{
	// Set our value
	uint64_t value = node->mValue;
	
	// No skill, just do it
	if (node->mLeftChild != nullptr)
	{
		value += std::min(GetShortestPath(node->mLeftChild), GetShortestPath(node->mRightChild));
	}
	
	return value;
}



// Begin the solution
SOLUTION_BEGIN(18, uint64_t)
{
	// The triangle
	constexpr uint64_t triangle[] =
#if 0
	{
		3,
		7, 4,
		2, 4, 6,
		8, 5, 9, 3,
	}
#else
	{
		75,
		95, 64,
		17, 47, 82,
		18, 35, 87, 10,
		20, 04, 82, 47, 65,
		19, 01, 23, 75, 03, 34,
		88, 02, 77, 73, 07, 63, 67,
		99, 65, 04, 28, 06, 16, 70, 92,
		41, 41, 26, 56, 83, 40, 80, 70, 33,
		41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
		53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
		70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
		91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
		63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
		04, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60, 04, 23,
	}
#endif
	;
	
	// Get the size of the triangle
	constexpr size_t elements = sizeof(triangle) / sizeof(triangle[0]);
	
	// Reverse T(n) = n(n+1)/2 to find out the number of rows
	// n^2 + n - 2T(n) => n = (-1 + sqrt(1 + 8T(n))) / 2
	constexpr size_t rows = (sqrt(1 + 8 * elements) - 1) / 2;
	
	// Just check that rounding hasn't broken it
	static_assert(rows * (rows + 1) == 2 * elements, "Rounding in sqrt() broke, or there are an incorrect number of elements in triangle");
	
	// Get the maximum value in the triangle
	const uint64_t max = *std::max_element(triangle, triangle + elements) + 1;
	
	// Parse the triangle. In doing so we also invert that values so that we're looking for the shortest path instead
	TriangleNode * root = ParseTriangle(triangle, elements, rows, max);
	
	// Get the shortest path. The subtraction undoes the inversion we did before
	result = max * rows - GetShortestPath(root);
	
	// Free the nodes afterwards
	FreeNodes(root);
}
SOLUTION_END()
