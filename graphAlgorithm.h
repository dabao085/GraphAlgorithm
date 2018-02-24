#ifndef _GRAPH_ALGORITHM_H_
#define _GRAPH_ALGORITHM_H_

#include "graph.h"
#include <queue>
#include <algorithm>

//��������TopSort
int TopSort(CGraph &graph);

//������ȱ���
int BreadthFirst(CGraph &graph, int index);

//������ȱ���
int WidthFirst(CGraph &graph, int index);

//DijkstraAlgorithm���·��
int DijkstraAlgorhm(CGraph &graph, int index);

#endif