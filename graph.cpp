#include "graph.h"
#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>

bool operator<(const CVertex &lhs, const CVertex &rhs)
{
	return lhs.GetIndex() < rhs.GetIndex();
}

int CGraph::CreateGraph(const std::string & fileName)
{
	std::vector<std::vector<int>> l_infoVec;
	if (GenIndexFromFile(fileName, l_infoVec) < 0)
	{
		std::cout << "[ERROR]:CreateGraph failed" << std::endl;
		return -1;
	}

	for (auto a : l_infoVec)
	{
		int tmp_firstIndex = a.at(0);
		int tmp_secondIndex = a.at(1);
		int tmp_weight = a.at(2);

		//初始化邻接表
		InsertEdgeInAdj(tmp_firstIndex, tmp_secondIndex);
		//初始化所有边
		CEdge tmp_edge(tmp_firstIndex, tmp_secondIndex, tmp_weight);
		m_edgeVec.push_back(tmp_edge);

		if (!m_allVertexesMap.count(tmp_firstIndex))
			m_allVertexesMap[tmp_firstIndex] = CVertex(tmp_firstIndex);
		if (!m_allVertexesMap.count(tmp_secondIndex))
			m_allVertexesMap[tmp_secondIndex] = CVertex(tmp_secondIndex);

		//寻找m_adjacencyListMap中缺失的节点，并加入m_adjacencyListMap中
		for (auto a : m_allVertexesMap)
		{
			int tmp_index = a.first;
			if (m_adjacencyListMap.count(tmp_index))
				continue;
			m_adjacencyListMap[tmp_index] = std::list<int>();		//把缺失的顶点补上
		}
		m_vertexNum = m_adjacencyListMap.size();
		//初始化并计算indegree
		InitIndegree(tmp_firstIndex, tmp_secondIndex);
	}

	return 0;
}

void CGraph::InsertEdgeInAdj(int firstVertexIndex, int secondVertexIndex)
{
	assert(firstVertexIndex > 0 && secondVertexIndex > 0);

	std::list<int> &l_list = m_adjacencyListMap[firstVertexIndex];
	l_list.insert(l_list.end(), secondVertexIndex);
}

int CGraph::InitIndegree(int firstIndex, int secondIndex)
{
	assert(firstIndex > 0 && secondIndex > 0);
	m_allVertexesMap[secondIndex].AddIndegree();

	return 0;
}

void CGraph::PrintGraph()const
{
	for (auto a : m_adjacencyListMap)
	{
		std::cout << a.first << std::endl;
		for (auto b : a.second)
			std::cout << b << " ";
		std::cout << std::endl;		
	}
}

int CGraph::GenIndexFromFile(const std::string &fileName, std::vector<std::vector<int>> &vertexEdgeWeightInfoVec)
{
	assert(!fileName.empty());
	std::ifstream in(fileName);
	std::string line;
	int firstIndex, secondIndex, weight;

	if (in)
	{
		while (getline(in, line))
		{
			std::istringstream record(line);
			record >> firstIndex;
			record >> secondIndex;
			record >> weight;

			std::vector<int> tmp_vec;
			tmp_vec.push_back(firstIndex);
			tmp_vec.push_back(secondIndex);
			tmp_vec.push_back(weight);
			vertexEdgeWeightInfoVec.push_back(tmp_vec);
		}
	}
	else
	{
		std::cout << "[ERROR]:File " << fileName << " open failed" << std::endl;
		return -1;
	}

	return 0;
}

void CGraph::PrintIndegree() const
{
	for (auto a : m_allVertexesMap)
		std::cout << a.first << " : " << a.second.GetIndegree() << std::endl;
}
