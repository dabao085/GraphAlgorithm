#include "graphAlgorithm.h"
#include <iostream>

int boolToInt(bool value){ return value ? 1 : 0; }
bool intToBool(int value){ return value == 1 ? true : false; }

int DijkstraAlgorhm(CGraph &graph, int index)
{
	//����һ�ŵǼǱ���¼���ڵ���Ϣ�ı仯
	std::vector<std::vector<int>> tmp_infoTable;
	//��ʼ����Ϣ��
	for (int i = 0; i < graph.GetVertexNum(); ++i)
	{
		std::vector<int> tmp_vec{i+1,0,CVertex::GRAPHINFINITY,0};
		tmp_infoTable.push_back(tmp_vec);
	}

	std::map<int, std::list<int>> &tmp_adjacencyListMap = graph.GetAdjacencyListMap();
	std::map<int, CVertex > &tmp_allVertex = graph.GetAllVertex();
	std::vector<CEdge> &tmp_allEdgeVec = graph.GetEdgeVec();
	std::vector<std::vector<int>> tmp_weightTable;	//��¼��(�ڵ�)��Ȩֵ����Ϣ

	int tmp_vertexNum = graph.GetVertexNum();
	//��ʼ��Ϊ0
	for (int i = 0; i < tmp_vertexNum; ++i)
	{
		std::vector<int> tmp_weightVec;
		for (int j = 0; j < tmp_vertexNum; ++j)
			tmp_weightVec.push_back(0);
		tmp_weightTable.push_back(tmp_weightVec);
	}

	//��ʼ��Ϊʵ��Ȩֵ
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

		//���øýڵ�Ϊknown(1)
		tmp_infoTable[tmp_index - 1][1] = 1;
		//���±��ڵ����(ֻ�Կ�ʼ�ڵ���Ч������Ľڵ���붼�������ڵ㸺�����)
		if (tmp_index == index)
		{
			tmp_infoTable[tmp_index - 1][2] = 0;
			//���±��ڵ���"��һ�ڵ��index"��Ϣ������ԭ��ͬ��
			tmp_infoTable[tmp_index - 1][3] = 0;
		}
		//�ҵ��ڽӽڵ㲢����
		for (auto a : tmp_adjacencyListMap[tmp_index])
		{
			//unknown�����ʼȨֵ
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
					//����Ƿ���Ҫ���¾������һ�ڵ�index��Ϣ
					std::cout << tmp_infoTable[tmp_preIndex - 1][2] + tmp_weightTable[a - 1][2] << std::endl;
					tmp_infoTable[a - 1][2] = tmp_infoTable[tmp_preIndex - 1][2] + tmp_weightTable[a - 1][2];
					tmp_infoTable[a - 1][3] = tmp_index;
				}
			}		
		}
	}

	//tmp_infoTable�Ѹ�����ϣ�������ڵ㵽�������нڵ�ľ����·��
	for (auto a : tmp_infoTable)
		std::cout << a[0] << " distance is: " << a[2] << std::endl;

	return 0;
}