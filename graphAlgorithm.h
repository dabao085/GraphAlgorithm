#ifndef _GRAPH_ALGORITHM_H_
#define _GRAPH_ALGORITHM_H_

#include "graph.h"
#include <queue>
#include <algorithm>

//拓扑排序TopSort
int TopSort(CGraph &graph);

//广度优先遍历
int BreadthFirst(CGraph &graph, int index);

//深度优先遍历
int WidthFirst(CGraph &graph, int index);

//DijkstraAlgorithm最短路径
int DijkstraAlgorhm(CGraph &graph, int index);

#endif