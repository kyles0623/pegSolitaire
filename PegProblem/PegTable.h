#pragma once
#include<vector>
#include<string>


class PegTable
{
public:

	PegTable *parent;
	PegTable(void);
	PegTable(const int levels);
	PegTable(const PegTable &copy);
	bool getValue(const int level, const int index);
	bool operator==(PegTable &);
	bool CanJumpTo (const int level, const int number, const int jumpFromDirection);
	void JumpTo(const int level, const int number , const int jumpFromDirection);
	void JumpTo(const int index);
	int getLevel(const int index);
	void Print();
	int level;
	int numPegs;

	std::vector<int> Blanks;
	std::string last_move;

	~PegTable(void);

private:
	const static int DEFAULT_SIZE = 15;
	std::vector<bool> Table;
	int size;

};

