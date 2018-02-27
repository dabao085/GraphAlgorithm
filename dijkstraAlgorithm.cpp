#include "graphAlgorithm.h"
#include <iostream>

int boolToInt(bool value){ return value ? 1 : 0; }
bool intToBool(int value){ return value == 1 ? true : false; }

int DijkstraAlgorhm(CGraph &graph, int index)
{
	//构建一张登记表，记录各节点信息的变化
	std::vector<std::vector<int>> tmp_infoTable;
	//初始化信息表
	for (int i = 0; i < graph.GetVertexNum(); ++i)
	{
		std::vector<int> tmp_vec{i+1,0,CVertex::GRAPHINFINITY,0};
		tmp_infoTable.push_back(tmp_vec);
	}

	std::map<int, std::list<int>> &tmp_adjacencyListMap = graph.GetAdjacencyListMap();
	std::map<int, CVertex > &tmp_allVertex = graph.GetAllVertex();
	std::vector<CEdge> &tmp_allEdgeVec = graph.GetEdgeVec();
	std::vector<std::vector<int>> tmp_weightTable;	//记录边(节点)和权值的信息

	int tmp_vertexNum = graph.GetVertexNum();
	//初始化为0
	for (int i = 0; i < tmp_vertexNum; ++i)
	{
		std::vector<int> tmp_weightVec;
		for (int j = 0; j < tmp_vertexNum; ++j)
			tmp_weightVec.push_back(0);
		tmp_weightTable.push_back(tmp_weightVec);
	}

	//初始化为实际权值
	for (auto a : tmp_allEdgeVec)
		tmp_weightTable[a.GetFirstVertex() - 1][a.GetSecondVertex() - 1] = a.GetWeight();

	for (auto a : tmp_allVertex)
	{
		a.second.SetDistance(CVertex::GRAPHINFINITY);
		a.second.SetKnown(false);
	}

	std::priority_queue<int> l_queue;
	l_queue.push(index);

	std::cout << "----------------" << std::endl;
	while (!l_queue.empty())
	{
		int tmp_index = l_queue.top();
		l_queue.pop();

		//设置该节点为known(1)
		tmp_infoTable[tmp_index - 1][1] = 1;
		//更新本节点距离(只对开始节点有效，后面的节点距离都由其他节点负责更新)
		if (tmp_index == index)
		{
			tmp_infoTable[tmp_index - 1][2] = 0;
			//更新本节点中"上一节点的index"信息，更新原则同上
			tmp_infoTable[tmp_index - 1][3] = 0;
		}
		//找到邻接节点并处理
		for (auto a : tmp_adjacencyListMap[tmp_index])
		{
			//unknown赋予初始权值
			if (tmp_infoTable[a - 1][2] == CVertex::GRAPHINFINITY)
			{
				tmp_infoTable[a - 1][2] = tmp_weightTable[tmp_index - 1][a - 1];
				std::cout << tmp_infoTable[a - 1][2] << std::endl;
				tmp_infoTable[a - 1][3] = tmp_index;
				l_queue.push(a);
			}
			else
			{
				int tmp_preIndex = tmp_infoTable[a - 1][3];
				if (tmp_infoTable[tmp_preIndex - 1][2] + tmp_weightTable[a - 1][2] > tmp_infoTable[a - 1][2])
				{
					//检查是否需要更新距离和上一节点index信息
					std::cout << tmp_infoTable[tmp_preIndex - 1][2] + tmp_weightTable[a - 1][2] << std::endl;
					tmp_infoTable[a - 1][2] = tmp_infoTable[tmp_preIndex - 1][2] + tmp_weightTable[a - 1][2];
					tmp_infoTable[a - 1][3] = tmp_index;
				}
			}		
		}
	}

	//tmp_infoTable已更新完毕，输出单节点到其他所有节点的距离和路径
	for (auto a : tmp_infoTable)
		std::cout << a[0] << " distance is: " << a[2] << std::endl;

	return 0;
}