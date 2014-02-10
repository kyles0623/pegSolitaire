#pragma once

#include<hash_map>
#include<stack>
#include "PegTable.h"

#include<set>
using namespace std;

class PGraph
{
public:
	PGraph(void);
	void AddEdge(PegTable* from,PegTable* to, double cost); 
	hash_map<PegTable*,double> & getAdjacents(PegTable *src);
	PegTable* DLS(PegTable *src, int limit);
	
	PegTable* DFS(PegTable *src,const string &final_state);
	~PGraph(void);

private: 
	hash_map<PegTable*,hash_map<PegTable*,double>> gData;
	hash_map<PegTable*,double> emptyMap;
};

