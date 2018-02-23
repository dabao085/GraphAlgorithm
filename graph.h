#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <list>
#include <vector>
#include <map>
#include <string>
#include <set>

class CVertex
{
public:
	CVertex(int index) :m_index(index), m_indegree(0), m_topNum(0){}
	CVertex(){}

public:
	int GetIndex() const{ return m_index; }
	int GetIndegree() const{ return m_indegree; }
	int GetTopNum() const{ return m_topNum; }
	int GetDistance() const{ return m_distance; }
	int GetPathIndex()const{ return m_pathIndex; }
public:
	void SetDistance(int distance){ m_distance = distance; }
	void SetPathIndex(int pathIndex){ m_pathIndex = pathIndex; }
	void SetTopNum(int topNum){ m_topNum = topNum; }
	void AddIndegree(){  ++m_indegree;  }
	void MinusIndegree(){ --m_indegree; }
	//void SetIndegree(int indegree){ m_indegree = indegree; }

	static const int GRAPHINFINITY = 100;
private:
	int m_index;
	int m_indegree;	//��������,��β����أ�
	int m_topNum;	//���������������
	int m_distance;	//��Ŀ�Ľڵ�ľ��룬����ͼ�ı���
	int m_pathIndex;//��һ�ڵ��index������ͼ�ı���
};

class CEdge
{
public:
	CEdge(int firstIndex, int secondIndex, int weight):
		m_firstVertex(CVertex(firstIndex)),
		m_secondVertex(CVertex(secondIndex)),
		m_weight(weight)
	{}

	const int GetWeight() const { return m_weight; }
	CVertex GetFirstVertex() const { return m_firstVertex; }
	CVertex GetSecondVertex() const { return m_secondVertex; }

private:
	int m_weight;				//Ȩ��
	CVertex m_firstVertex;
	CVertex m_secondVertex;
};

class CGraph
{
public:
	CGraph() :m_vertexNum(0){}

	//Create Graph according to the content of the file
	int CreateGraph(const std::string & fileName);
	void PrintGraph()const;
	void PrintIndegree() const;
	std::map<int, CVertex>& GetAllVertex() { return m_allVertexesMap; }
	std::map<int, std::list<int>>& GetAdjacencyListMap(){ return m_adjacencyListMap; }
	int GetVertexNum() const{ return m_vertexNum; }
private:
	//��ʼ�����洢���еı�
	int InitEdgeVec(int firstIndex, int secondIndex, int weight);
	//��ʼ��������洢���ж����indegree
	int InitIndegree(int firstIndex, int secondIndex);
	//�����ļ��е�����,vertexEdgeWeightInfoVec�洢��ʽΪ [firstIndex, secondIndex, weight]
	int GenIndexFromFile(const std::string &fileName, std::vector<std::vector<int>> &vertexEdgeWeightInfoVec);
	void InitAdjacencyListMapAndEdgeVecIndegree();
	void InsertEdgeInAdj(int firstVertexIndex, int secondVertexIndex);
private:
	std::map<int, std::list<int>> m_adjacencyListMap;	//��¼�����ڽӱ���Ϣ����ֻ��¼index��index��Ϣ������¼��ϸ�ڵ���Ϣ
	std::map<int, CVertex> m_allVertexesMap;			//��¼���еĽڵ㣬indexΪ����
	std::vector<CEdge> m_edgeVec;						//��¼���еı�
	int m_vertexNum;									//��¼�ڵ�����
};
#endif