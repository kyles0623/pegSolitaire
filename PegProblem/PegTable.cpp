#pragma once
#include "PegTable.h"
#include<iostream>
#include<vector>

PegTable::PegTable(void)
{
	this->parent = 0;
}

PegTable::PegTable(const int level, const string &config)
{
	//Level 
	this->level = level;
	this->size = (level*(level+1))/2;
	this->Table = std::vector<bool>(size,true);
	this->numPegs = size;
	this->SetConfiguration(config);
	this->TableValue = this->GenerateBitsValue();
	this->parent = 0; 
	this->lastMove.index = -1;
	this->lastMove.jumpedFrom = -1;
	this->lastMove.jumpedOver = -1;
}
void PegTable::SetConfiguration(const string &config)
{
	if(this->size > config.size())
	{
		cout<<"Error: Config invalid";
		return;
	}

	for(unsigned int i=0;i<this->size;i++)
	{
		if(config[i] == '0'){
			this->Table[i] = false;
			this->numPegs--;
		}

	}

}

PegTable::PegTable(const PegTable &copy)
{
	this->level = copy.level;
	this->size = copy.size;
	this->Table = copy.Table;
	this->numPegs = copy.numPegs;
	this->TableValue = copy.TableValue;
	this->parent = 0;

}
bool PegTable::isSolvable()
{
	int x1 = 0, x2 = 0, x3 = 0;
	
	for(int i=0;i<this->level;i++)
	{
		for(int j=0;j<=i;j++)
		{
			bool t = this->Table[(((i+1)*i)/2)+j];
			if(t){
				switch(((i+j)%3)+1){
				case 1:
					x1++;
					break;
				case 2:
					x2++;
					break;
				case 3:
					x3++;
					break;
				}
			}
		}
	}

	if(x1==x2 && x1==x3)
		return false;
	else
		return true;
}
bool PegTable::operator==(PegTable &compare)
{
	return this->Table == compare.Table;
}
bool PegTable::isSolved(const int &level,const int &number)
{
	if(this->numPegs != 1)
		return false;

	if(this->Table[((level*(level+1)/2) + number)])
		return true;

	return false;

}
bool PegTable::getValue(const int level, const int number)
{
	if(level == 0)
		return this->Table[0];
	else
		return this->Table[((level*(level+1)/2) + number)];
}

//Jump to this empty peg from the direction given
//Level indicates what level we are jumping to
//Number indicates what index on that level we are jumping to
//jumpFromDirection indicates 1 of the 5 possible ways to jump to that space
void PegTable::JumpTo(const int level, const int number, const int jumpFromDirection)
{
	//Index of current peg
	int index;
	
	//Set Peg
	if(level == 0)
		index = 0;
	else
		index = ((level+1)*(level))/2 + number;


	int jumpOverIndex;
	int jumpFromIndex;


	//JumpFrom Direction
	/*
	 0 1
	2 x 3
	 4 5
	 0 - Jump from Top Left diagonally to x
	 1 - jump from top right diagonally to x
	 2 - jump from left to x 
	 3 - jump from right to x
	 4 - jump from bottom left diagonally
	 5 - jump from bottom right diagonally
	*/
	jumpFromIndex = getJumpFromIndex(index,jumpFromDirection,level);
	jumpOverIndex = getJumpOverIndex(index,jumpFromDirection,level);


	this->TableValue |= 1 << index;
	this->TableValue &= ~(1<<jumpFromIndex);
	this->TableValue &= ~(1<<jumpOverIndex);

	this->Table[index] = true;
	this->Table[jumpFromIndex] = false;
	this->Table[jumpOverIndex] = false;

	this->lastMove.index = index;
	this->lastMove.jumpedFrom = jumpFromIndex;
	this->lastMove.jumpedOver = jumpOverIndex;
	this->numPegs--;
}
int PegTable::getJumpOverIndex(const int &index, const int &jumpDir, const int &level)
{
	int jumpOverIndex;
		switch(jumpDir){
	case 0:
		jumpOverIndex = index - (level + 1);
		break;
	case 1:
		jumpOverIndex = index - level ;
		break;
	case 2:
		jumpOverIndex = index - 1;
		break;
	case 3:
		jumpOverIndex = index + 1;
		break;
	case 4:
		jumpOverIndex = index + level + 1;
		break;
	case 5:
		jumpOverIndex = index + level + 2;
		break;
	}

		return jumpOverIndex;

}
int PegTable::getJumpFromIndex(const int &index, const int &jumpDir, const int &level)
{
	int jumpFromIndex;
	switch(jumpDir){
	case 0:
		jumpFromIndex = index - ((2*(level+1)) - 1);
		break;
	case 1:
		jumpFromIndex = index - ((2*(level)) - 1);
		break;
	case 2:
		jumpFromIndex = index - 2;
		break;
	case 3:
		jumpFromIndex = index + 2;
		break;
	case 4:
		jumpFromIndex = index + ((2*(level+1)) + 1);
		break;
	case 5:
		jumpFromIndex = index + ((2*(level+2)) + 1);
		break;
	}

	return jumpFromIndex;

}
//Level indicates what level we are jumping to
//Number indicates what index on that level we are jumping to
//jumpFromDirection indicates 1 of the 5 possible ways to jump to that space
//returns boolean indicating jumpable space
bool PegTable::CanJumpTo (const int level, const int number, const int jumpFromDirection)
{
	//It's impossible to do jump directions 0-3
	//from levels 0 and 1
	if(level <= 1 && jumpFromDirection <= 3)
		return false;
	
	//JumpFrom Direction
	/*
	 0 1
	2 x 3
	 4 5

	 0 - Jump from Top Left diagonally to x
	 1 - jump from top right diagonally to x
	 2 - jump from left to x 
	 3 - jump from right to x
	 4 - jump from bottom left diagonally
	 5 - jump from bottom right diagonally
	*/

	//Index of curret peg
	int index;

	if(level == 0)
		index = 0;
	else
		index = (((level+1)*(level))/2) + number;

	if(this->Table[index])
		return false;

	//Jump over index is the index of the peg we are jumping over 
	//and removing from the board, i.e. making false
	int jumpOverIndex;
	//Jump from index is the index of the peg we are jumping from, i.e. making false
	int jumpFromIndex;

	//Each JumpFromDirection value has a specific calculation
	//to calculate the value of the JumpToIndex
	//and the JumpOverIndex
	switch(jumpFromDirection){
	case 0:
		if(number < 2)
			return false;

		jumpFromIndex = index - ((2*(level+1)) - 1);
		jumpOverIndex = index - (level+1);
		break;
	case 1:
		//Range makes sure the value of the jumpFromIndex
		//is on two levels above X's level
		if(index > ((level+2)*(level+1))/2 - 3)
			return false;

		jumpFromIndex = index - ((2*(level)) - 1);
		jumpOverIndex = index - (level);
		break;
	case 2:

		
		//Pegs on this edge cant have a jump from 2
		//when they are the 2nd peg in the row
		if(number < 2)
			return false;

		jumpFromIndex = index - 2;
		jumpOverIndex = index - 1;
		
		break;
	case 3:
		if(index > ((level+2)*(level+1))/2 - 3)
			return false;

		jumpFromIndex = index + 2;
		jumpOverIndex = index + 1;

		
		break;
	case 4:
		jumpFromIndex = index + ((2*(level+1)) + 1);
		jumpOverIndex = index + level + 1;
		break;
	case 5:
		jumpFromIndex = index + ((2*(level+2)) + 1);
		jumpOverIndex = index + level + 2;
		break;
	}

	//Check to make sure we are still on the board
	if(jumpFromIndex < 0 || jumpFromIndex >= this->size || !this->Table[jumpFromIndex])
		return false;
	if(jumpOverIndex < 0 || jumpOverIndex >= this->size || !this->Table[jumpOverIndex])
		return false;

	return true;
}
vector<bool> PegTable::getChangedValue(const int lev, const int number, const int jumpFromDirection)
{
	vector<bool> ret = this->Table;
	unsigned long long int temp = this->TableValue;
	int in;

	if(lev == 0)
		in = 0;
	else
		in = ((lev+1)*(lev))/2 + number;

	int jumpOverIndex = getJumpOverIndex(in,jumpFromDirection,lev);
	int jumpFromIndex = getJumpFromIndex(in,jumpFromDirection,lev);
	ret[in] = 1;
	ret[jumpFromIndex] = 0;
	ret[jumpOverIndex] = 0;

	return ret;

}
unsigned long long int PegTable::GenerateBitsValue()
{
	
    unsigned long long int retval = 0;
    int i =0;
    for (std::vector<bool>::iterator it = this->Table.begin() ; it != Table.end(); it++,i++){
        if(*it){
            retval |= 1<<i;
        }
    
   
	}
	return retval;
}

void PegTable::Print()
{

	for(int i=0;i<this->level;i++)
	{
		for(int k=0;k<((level)-i);k++)
			std::cout<<" ";

		for(int j=0;j<=i;j++)
		{
			std::cout<<this->getValue(i,j)<<" ";
		}

		std::cout<<std::endl;

	}
}

/*
void PegTable::Draw(sf::RenderWindow &window, PegTable *last)
{
	static const int init_x = 100,init_y = 100;
	int index;

	float x,y;
	for(int i=0;i<this->level;i++)
	{
		for(int j=0;j<=i;j++)
		{
			

			

			x = init_x+ (((level)-i)*22.0f + (44.0f*(j+1)));
			y = init_y+(40.0f*i);

			index = ((i)*(i+1)/2)+j;

			

			sf::CircleShape circle(15);

			circle.setPosition(x,y);
		
			if(this->getValue(i,j) == 0)
			{
				circle.setFillColor(sf::Color::Color(245,18,232,255));
			}
			else
			{
				circle.setFillColor(sf::Color::Blue);
			}

			
			window.draw(circle);

			//Draw signifier
			if(index == last->lastMove.jumpedFrom)
			{
				sf::CircleShape sig(5);
				sig.setPosition(x+10,y+10);
				sig.setFillColor(sf::Color::Red);

				window.draw(sig);
			}
			if(index == last->lastMove.index)
			{
				sf::CircleShape sig(5);
				sig.setPosition(x+10,y+10);
				sig.setFillColor(sf::Color::Green);

				window.draw(sig);
			}
		}

	}

}
*/
PegTable::~PegTable(void)
{

}
