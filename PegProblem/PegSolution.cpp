#include "PegTable.h"
#include "PGraph.h"
#include<SFML\Graphics.hpp>
#include <time.h>
#include<iostream>

using namespace std;

int main()
{
	//Number of levels 
	
	int emptyStart = 0;
	int final_level = 0;
	int final_number = 0;
	int depth = 1;
	//string config =		  "1110111111111111111111111111111111111111111111111111111";
	//string final_config = "0000000000100000000000000000000000000000000000000000000";
	int n;// = 8;
	string config;// =		  "01111111111111111111111111111111111111111111111111111111111111111";
	string final_config;// = "100000000000000000000000000000000000000000000000000000000000000000";

	cout<<"Please enter the number of level's you would like in this game: ";
	cin>>n;
	cout<<endl<<"Please enter the initial state which is a series of "<<(float)(n*(n+1)/2)<<" 0's and 1's where 1 reprents a peg and 0 represents an empty space."<<endl;
	cin>>config;
	cout<<endl<<"Please enter the final state which is a series of "<<(float)(n*(n+1)/2)<<" 0's and 1's where 1 reprents a peg and 0 represents an empty space."<<endl;
	cin>>final_config;
	cout<<endl<<endl;
	PegTable *found;

	PegTable *table = new PegTable(n,config);
	PGraph graph;
	stack<PegTable*> stac;
	const clock_t begin_time = clock();
	found = graph.DFS(table,final_config);
	cout<<endl<<float((clock() - begin_time))/1000<<" seconds"<<endl<<endl;
	if(found == 0)
	{
		cout<<"The solution state for this configuration does not exist"<<endl;
		return 0;
	}

	sf::Clock Clock;
	sf::Time time;

	while(found != 0)
	{
		stac.push(found);
		found = found->parent;
	}


	
	while(!stac.empty())
	{
		found = stac.top();
		stac.pop();
		found->Print();
	}
	
	/*
	sf::VideoMode videoMode(1280,720);
	sf::RenderWindow window(videoMode,"KeyEvent Window");

	stack<PegTable*> stac_iter = stac;
	float elapsed = 3000;
	float elapser = 0;
	while(window.isOpen())
	{
		time = Clock.getElapsedTime();

		if(time.asMilliseconds() > elapser ){

			if(stac_iter.empty())
				stac_iter = stac;

			found = stac_iter.top();
			stac_iter.pop();

			window.clear();
			found->Draw(window,stac_iter.top());
			window.display();
			Clock.restart();
			elapser = elapsed;
		} 
	}
	*/
	return 0;
}