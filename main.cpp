#include "graphAlgorithm.h"
#include <iostream>
using namespace std;

int main()
{
	CGraph graph;
	graph.CreateGraph("inputBreadthFirst.txt");

	cout << "----------Print Graph Reuslt ----------------" << endl;
	graph.PrintGraph();
	cout << "----------Print Indegree Result--------------" << endl;
	graph.PrintIndegree();

	//if (TopSort(graph) < 0)
	//{
	//	std::cout << "[ERROR]: TopSort failed!" << std::endl;
	//	return -1;
	//}

	if (BreadthFirst(graph, 3) < 0)
	{
		std::cout << "[ERROR]: BreadthFirst failed!" << std::endl;
		return -1;
	}

	return 0;
}