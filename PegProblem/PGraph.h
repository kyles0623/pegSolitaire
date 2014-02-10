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
	PegTable* DFS(PegTable *src,const string &final_state);
	~PGraph(void);

private: 
};

