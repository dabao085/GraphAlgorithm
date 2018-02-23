#include "graphAlgorithm.h"
#include <iostream>

int BreadthFirst(CGraph &graph, int startIndex)
{
	std::queue<int> l_queue;
	std::map<int, CVertex> &tmp_allVertex = graph.GetAllVertex();

	for (auto &a : tmp_allVertex)
		a.second.SetDistance(CVertex::GRAPHINFINITY);

	//³õÊ¼½Úµã
	tmp_allVertex[startIndex].SetDistance(0);
	l_queue.push(startIndex);
	std::map<int, std::list<int>> &tmp_adjacencyListMap = graph.GetAdjacencyListMap();
	std::cout << "---------Start to print result after breadth first----------" << std::endl;
	while (!l_queue.empty())
	{
		int tmp_index = l_queue.front();
		std::cout << tmp_index << " -> ";
		l_queue.pop();

		for (auto a : tmp_adjacencyListMap[tmp_index])
			if (tmp_allVertex[a].GetDistance() == CVertex::GRAPHINFINITY)
			{
				//distance + 1
				tmp_allVertex[a].SetDistance(tmp_allVertex[tmp_index].GetDistance() + 1);
				tmp_allVertex[a].SetPathIndex(tmp_index);
				l_queue.push(a);
			}
	}

	std::cout << "END" << std::endl;
	return 0;
}