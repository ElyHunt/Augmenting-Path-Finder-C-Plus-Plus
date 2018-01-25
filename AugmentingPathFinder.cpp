/*
Elliot Hunt
November 9th, 2017
AugmentingPathFinder.cpp
Assignment Two, Question 3
Lars Kotthoff
Uses C++

Note: This was an assignment to write a program to find augmenting
paths from residual graphs given from the Ford-Fulkerson algorithm.
*/

#include <iostream>
#include <vector>
#include <list>
using namespace std;


void printMatrix(vector<vector<int>> theMatrix)
{
	cout << endl;

	for (int i = 0; i < theMatrix.size(); i++)
	{
		for (int j = 0; j < theMatrix.size(); j++)
		{
			cout << theMatrix[i][j] << "\t";

		}
		cout << endl;
	}
}

void printList(list<int> theList)
{
	if (theList.size() > 0)
	{
		cout << endl << "Augmenting Path: ";

		for (int element : theList)
		{
			cout << element << " ";
		}
	}
	else
	{
		cout << endl << "No path found! ";
	}

	cout << endl;
}

list<int> augmentingPath(vector<vector<int>> residualGraph, int startingNode, int endingNode, list<int>& aPath)
{ //The assignment said to use a list as the container of the path.
  //In addition to the graph, the function takes in the starting node and ending nodes and stores the path as a list.
	if (startingNode == endingNode)
	{
		aPath.push_back(startingNode);
		return aPath;
	}
	else if (residualGraph[endingNode][startingNode] != 0)
	{
		aPath.push_back(startingNode);
		augmentingPath(residualGraph, endingNode, endingNode, aPath);
		return aPath;
	}
	else
	{
		bool visited = false;
		aPath.push_back(startingNode);
		for (int i = 0; i < residualGraph[startingNode].size(); i++)
		{
			if (residualGraph[i][startingNode] != 0)
			{
				for (int element : aPath)
				{
					if (i == element)
					{
						visited = true;
						break;
					}
				}
				if (!visited)
				{
					augmentingPath(residualGraph, i, endingNode, aPath);
				}
				visited = false;
			}
		}
	}

	if (aPath.back() != endingNode)
	{
		aPath.pop_back();
	}//Allows the path to be erased as it goes backwards if the proper
	//path was not found on this route.
	return aPath;
}

list<int> findAugmentingPath(vector<vector<int>> residualGraph, int startingNode, int endingNode)
{//Wrapper function so that a list doesn't have to be passed in.
	list<int> aPath;
	return augmentingPath(residualGraph, startingNode, endingNode, aPath);
}




int main()//Testing Code
{
	//I chose to use matrices, as they're a little more intuitive to use
	//and they can be graphically represented as such when initializing.
	//This makes the code more readable in my opinion.

	vector<vector<int>> firstGraph{
		//	  0s 1a 2b 3c 4d 5t
			{ 0, 8, 3, 0, 0, 0 },	//0s
			{ 1, 0, 0, 8, 0, 0 },	//1a
			{ 6,10, 0, 0, 3, 0 },	//2b
			{ 0, 0, 1, 0, 8, 8 },	//3c
			{ 0, 0, 0, 0, 0, 3 },	//4d
			{ 0, 0, 0, 2, 4, 0 } };	//5t
//This residual graph adapted from one in here at 4:38: https://m.youtube.com/watch?v=hmIrJCGPPG4
	
	vector<vector<int>> secondGraph{
		//	  0s 1a 2b
			{ 0, 0, 1, },	//0s
			{ 1, 0, 1, },	//1a
			{ 0, 0, 0, } };	//2b
							
	vector<vector<int>> thirdGraph{
		//	  0s 1a 2b
			{ 0, 0, 1, },	//0s
			{ 1, 0, 1, },	//1a
			{ 0, -9, 0, } };	//2b

	vector<vector<int>> fourthGraph{
	//	  0s 1a 2b 3c 4d 5t
		{ 0, 0, 3, 0, 0, 0 },	//0s
		{ 1, 0, 0, 8, 0, 0 },	//1a
		{ 6, 0, 0, 0, 3, 0 },	//2b
		{ 0, 0, 1, 0, 8, 8 },	//3c
		{ 0, 0, 0, 0, 0, 3 },	//4d
		{ 0, 0, 0, 2, 4, 0 } };	//5t
								//This residual graph adapted from one in here at 4:38: https://m.youtube.com/watch?v=hmIrJCGPPG4


	cout << "Initial Matrix!\n";
	printMatrix(firstGraph);
	cout << "\nNow the augmenting path from 0 to 5!\n";
	printList(findAugmentingPath(firstGraph, 0, 5));
	//This tests whether or not the algorithm works in a general case.

	cout << "Initial Matrix!\n";
	printMatrix(firstGraph);
	cout << "\nNow the augmenting path from 1 to 4!\n";
	printList(findAugmentingPath(firstGraph, 1, 4));
	//This tests whether you can change the starting node positions.

	cout << "Initial Matrix!\n";
	printMatrix(secondGraph);
	cout << "\nNow the augmenting path from 0 to 2!\n";
	printList(findAugmentingPath(secondGraph, 0, 2));
	//This tests whether the algorithm can handle a case where there is no path.

	cout << "Initial Matrix!\n";
	printMatrix(thirdGraph);
	cout << "\nNow the augmenting path from 0 to 2!\n";
	printList(findAugmentingPath(thirdGraph, 0, 2));
	//This tests whether the algoirthm can handle a case with a negative weight/negative weight cycle.

	cout << "Initial Matrix!\n";
	printMatrix(fourthGraph);
	cout << "\nNow the augmenting path from 0 to 5!\n";
	printList(findAugmentingPath(fourthGraph, 0, 5));
	//This tests whether the algorithm can handle a case where the first choice is a dead end and it has to back-track.

	return 0;
}

/*
The way I implemented accounts for cycles, negative weights, and negative weight cycles.
Each node can only be visited once in a particular path, thus eliminating cycles. Negative
Weights are not given any preference, as it simply chooses any path it comes upon.
*/