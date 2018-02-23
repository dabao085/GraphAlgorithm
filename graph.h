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
	int m_indegree;	//顶点的入度,如何操作呢？
	int m_topNum;	//顶点的拓扑排序编号
	int m_distance;	//到目的节点的距离，用于图的遍历
	int m_pathIndex;//下一节点的index，用于图的遍历
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
	int m_weight;				//权重
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
	//初始化并存储所有的边
	int InitEdgeVec(int firstIndex, int secondIndex, int weight);
	//初始化并计算存储所有顶点的indegree
	int InitIndegree(int firstIndex, int secondIndex);
	//读入文件中的数据,vertexEdgeWeightInfoVec存储格式为 [firstIndex, secondIndex, weight]
	int GenIndexFromFile(const std::string &fileName, std::vector<std::vector<int>> &vertexEdgeWeightInfoVec);
	void InitAdjacencyListMapAndEdgeVecIndegree();
	void InsertEdgeInAdj(int firstVertexIndex, int secondVertexIndex);
private:
	std::map<int, std::list<int>> m_adjacencyListMap;	//记录整个邻接表信息，但只记录index与index信息，不记录详细节点信息
	std::map<int, CVertex> m_allVertexesMap;			//记录所有的节点，index为索引
	std::vector<CEdge> m_edgeVec;						//记录所有的边
	int m_vertexNum;									//记录节点总数
};
#endif