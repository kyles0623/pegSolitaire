#include "PegTable.h"
#include<iostream>
#include<vector>

PegTable::PegTable(void)
{
	this->parent = 0;
}

PegTable::PegTable(const int level)
{
	//Level 
	this->level = level;
	this->size = (level*(level+1))/2;
	this->Table = std::vector<bool>(size,true);
	this->numPegs = size-1;
	this->Table[0] = false;
	this->parent = 0;
}
PegTable::PegTable(const PegTable &copy)
{
	this->level = copy.level;
	this->size = copy.size;
	this->Table = copy.Table;
	this->numPegs = copy.numPegs;
	this->parent = 0;

}
bool PegTable::operator==(PegTable &compare)
{
	return this->Table == compare.Table;
}
bool PegTable::getValue(const int level, const int number)
{
	if(level == 0)
		return this->Table[0];
	else
		return this->Table[((level*(level+1)/2) + number)];
}
void PegTable::JumpTo(const int index)
{


}
//Jump to this empty peg from the direction given
//Level indicates what level we are jumping to
//Number indicates what index on that level we are jumping to
//jumpFromDirection indicates 1 of the 5 possible ways to jump to that space
void PegTable::JumpTo(const int level, const int number, const int jumpFromDirection)
{
	//Index of current peg
	int index;
	
	//Set Peg Index
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
	switch(jumpFromDirection){
	case 0:
		jumpFromIndex = index - ((2*(level+1)) - 1);
		jumpOverIndex = index - (level + 1);
		break;
	case 1:
		jumpFromIndex = index - ((2*(level)) - 1);
		jumpOverIndex = index - level ;
		break;
	case 2:
		jumpFromIndex = index - 2;
		jumpOverIndex = index - 1;
		break;
	case 3:
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

	this->Table[index] = true;
	this->Table[jumpFromIndex] = false;
	this->Table[jumpOverIndex] = false;
	this->numPegs--;
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
	int r1;

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
		jumpFromIndex = index - ((2*(level)) - 1);
		jumpOverIndex = index - (level);

		//Range makes sure the value of the jumpFromIndex
		//is on two levels above X's level
		if(index > ((level+2)*(level+1))/2 - 3)
			return false;
		break;
	case 2:
		jumpFromIndex = index - 2;
		jumpOverIndex = index - 1;
		
		//Pegs on this edge cant have a jump from 2
		//when they are the 2nd peg in the row
		if(number < 2)
			return false;
		break;
	case 3:
		

		jumpFromIndex = index + 2;
		jumpOverIndex = index + 1;

		if(index > ((level+2)*(level+1))/2 - 3)
			return false;
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

PegTable::~PegTable(void)
{

}
