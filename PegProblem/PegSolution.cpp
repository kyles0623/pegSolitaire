#include "PegTable.h"
#include "PGraph.h"
#include <time.h>
#include<iostream>

using namespace std;

int main()
{
	int n = 7;
	PegTable x(n);

	PegTable *found;
	PegTable *table = new PegTable(n);
	PGraph graph;

	found = graph.BFS(table);


	while(found != 0)
	{
		found->Print();
		cout<<endl<<found->last_move<<endl;
		found = found->parent;
	}
	
	return 0;
}