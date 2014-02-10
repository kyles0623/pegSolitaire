#include "PGraph.h"
#include<sstream>
#include<iostream>
#include<queue>
#include<time.h>
#include<unordered_set>
using namespace std;

PGraph::PGraph(void)
{
}







//Breadth First Search for Triangle Solitaire
PegTable * PGraph::DFS(PegTable *src,const string &final_state)
{

	//
	int maxQSize = 0;
	int testCount = 0;

	PegTable finish(src->level,final_state);
	 std::stack<PegTable*> stac;

	//Serves as Red Stack
	 //all Tables converted to integer
	 //each index of table serves as bit in index of integer
	unordered_set<vector<bool>> used;
	//Next table to be added to the stack
	PegTable *add;

	//Last popped from the stack
	PegTable *view;

	//Add initial state to stac
	stac.push(src);
	
	//used for viewing answer better
	//std::stringstream ss;

	while(!stac.empty())
	{

		view = stac.top();

		//system("cls");
		//cout<<testCount<<endl<<stac.size()<<endl;

		used.insert(view->Table);

		stac.pop();

		if(view->Table == finish.Table ){
			cout<<"Test Count: "<<testCount;
			return view;
		}
		testCount++;

		if((view->numPegs - 1) < finish.numPegs)
			continue;

		//Level 
		//0        x
		//1       x x
		//2      x x x
		//3     x x x x
		bool madeMove = 0;
		for(int i=0;i<view->level;i++)
		{

			//Index within that level
			// e.g. i = 1, j = 0 is the first value in level 1
			for(int j=0;j<=i;j++)
			{

				//Move possibility
				//5 different ways to jump to index i,j
				/*
				     0 1
				    2 x 3
					 4 5
				*/
				
				for(int k=0;k<6;k++)
				{
					
					//If the jump to this index is possible
					//and the the table due to this jump hasn't already been seen
					//Create the table and add it to the stack
					if(view->CanJumpTo(i,j,k) && (used.find(view->getChangedValue(i,j,k)) == used.end()))
					{
						add = new PegTable(*view);
						add->parent = view;
						add->JumpTo(i,j,k);
						
						madeMove = true;
						
						/*ss.str("");
						ss<<i<<", "<<j<<", "<<k<<endl;
						add->last_move = ss.str();*/
						
						stac.push(add);

						if((signed)stac.size() > maxQSize)
							maxQSize = stac.size();
					}
				}//end jumpdirection loop

				
			}//end index in level loop
		}//end level loop

		if(!madeMove)
		{
			delete view;
		}
	}//end while loop
	
	return 0;

}
PGraph::~PGraph(void)
{
}
