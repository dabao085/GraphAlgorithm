#include "graphAlgorithm.h"

int DijkstraAlgorhm(CGraph &graph, int index)
{
	std::map<int, std::list<int>> &tmp_adjacencyListMap = graph.GetAdjacencyListMap();
	std::map<int, CVertex > &tmp_allVertex = graph.GetAllVertex();

	for (auto a : tmp_allVertex)
	{
		a.second.SetDistance(CVertex::GRAPHINFINITY);
		a.second.SetKnown(false);
	}



	return 0;
}