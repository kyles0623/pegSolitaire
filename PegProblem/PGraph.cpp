#include "PGraph.h"
#include<sstream>
#include<iostream>
using namespace std;

PGraph::PGraph(void)
{
}

void PGraph::AddEdge(PegTable *from, PegTable *to, double cost)
{
	hash_map<PegTable*,hash_map<PegTable*,double>>::iterator iter = gData.find(from);

	if(iter==gData.end())
	{
		hash_map<PegTable*,double> edges;
		edges[to] = cost;
		gData[from] = edges;
	}
	else
	{
		iter->second[to] = cost;
	}

	iter = gData.find(to);

	if(iter==gData.end())
	{
		hash_map<PegTable*,double> edges;
		gData[to] = edges;
	}
	

}

hash_map<PegTable*,double> & PGraph::getAdjacents(PegTable *src)
{
	hash_map<PegTable*,hash_map<PegTable*,double>>::iterator iter = gData.find(src);

	if(iter == gData.end())
	{
		emptyMap.clear();
		return emptyMap;

	}
	return iter->second;
}


PegTable * PGraph::BFS(PegTable *src)
{
	int maxQSize = 0;
	int testCount = 0;
	 
	stack<PegTable*> stac;
	PegTable *add;
	PegTable *view;
	stac.push(src);

	std::stringstream ss;

	while(!stac.empty())
	{
		view = stac.top();
		stac.pop();

		testCount++;

		if(view->numPegs == 1){
			cout<<"Test Count: "<<testCount;
			return view;

		}

		for(int i=0;i<view->level;i++)
		{
			for(int j=0;j<=i;j++)
			{
				for(int k=0;k<6;k++)
				{
					
					
					if(view->CanJumpTo(i,j,k))
					{
						add = new PegTable(*view);
						add->parent = view;
						add->JumpTo(i,j,k);
						ss.str("");
						ss<<i<<", "<<j<<", "<<k<<endl;
						add->last_move = ss.str();
						stac.push(add);

						if((signed)stac.size() > maxQSize)
							maxQSize = stac.size();	
					}
					
				}

			}
		}

	}

	

	return 0;

}
PGraph::~PGraph(void)
{
}
