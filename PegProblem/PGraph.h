#pragma once

#include<hash_map>
#include<stack>
#include "PegTable.h"

using namespace std;

class PGraph
{
public:
	PGraph(void);
	void AddEdge(PegTable* from,PegTable* to, double cost); 
	hash_map<PegTable*,double> & getAdjacents(PegTable *src);
	PegTable* BFS(PegTable *src);
	~PGraph(void);

private: 
	hash_map<PegTable*,hash_map<PegTable*,double>> gData;
	hash_map<PegTable*,double> emptyMap;
};

