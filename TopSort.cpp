#include "graphAlgorithm.h"
#include <iostream>

int TopSort(CGraph &graph)
{
	std::queue<int> l_queue;
	int count = 0;
	int v;
	std::map<int, CVertex>& tmp_allVertex = graph.GetAllVertex();

	//把indegree==0的放入队列中
	for (auto a : tmp_allVertex)
		if (a.second.GetIndegree() == 0)
			l_queue.push(a.first);
	std::map<int, std::list<int>> &tmp_adjacencyListMap = graph.GetAdjacencyListMap();
	while (!l_queue.empty())
	{
		v = l_queue.front();
		l_queue.pop();

		tmp_allVertex[v].SetTopNum(++count);

		for (auto a : tmp_adjacencyListMap[v])
		{
			tmp_allVertex[a].MinusIndegree();
			if (tmp_allVertex[a].GetIndegree() == 0)
				l_queue.push(a);
		}
	}

	if (count != graph.GetVertexNum())
	{
		std::cout << "[ERROR]: Graph has a cycle" << std::endl;
		return -1;
	}

	std::cout << std::endl;
	std::cout << "-----------Start to print result after TopSort------------" << std::endl;

	//tmp_indexMap为m_TopNum, m_index
	std::map<int, int> tmp_indexMap;
	for (auto a : tmp_allVertex)
		tmp_indexMap[a.second.GetTopNum()] = a.second.GetIndex();
	
	for (auto a : tmp_indexMap)
		std::cout << a.second << " -> ";
	std::cout << "END" << std::endl;

	return 0;
}

