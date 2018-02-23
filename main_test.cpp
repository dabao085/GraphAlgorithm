#include "graph.h"
#include <iostream>
using namespace std;

class CTest
{
public:
	CTest(int weight) :weight(weight){}

	//bool operator<(const CTest &rhs){ return this->weight < rhs.weight; }
	int GetWeight()const{ return weight; }
private:
	int weight;
};

bool operator<(const CTest &lhs, const CTest &rhs)
{
	return lhs.GetWeight() < rhs.GetWeight();
}

//int main()
//{
//	set<CTest> testSet;
//	CTest test1(1);
//	CTest test2(2);
//
//	testSet.insert(test1);
//	testSet.insert(test2);
//
//	return 0;
//}