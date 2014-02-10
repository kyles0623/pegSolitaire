#pragma once
#include<vector>
#include<string>

using namespace std;


class PegTable
{
public:
	struct lastMove{
		int jumpedFrom, jumpedOver,index;

	} lastMove;

	PegTable *parent;
	PegTable(void);
	PegTable(const int levels, const string &config);
	PegTable(const PegTable &copy);
	bool getValue(const int level, const int index);
	bool operator==(PegTable &);
	bool CanJumpTo (const int level, const int number, const int jumpFromDirection);
	void JumpTo(const int level, const int number , const int jumpFromDirection);
	vector<bool> getChangedValue(const int level, const int number, const int jumpFromDirection);
	void SetConfiguration(const string &config);
	int getJumpOverIndex(const int &index, const int &jumpDir, const int &level);
	int getJumpFromIndex(const int &index, const int &jumpDir, const int &level);
	bool isSolvable();
	bool isSolved(const int &level,const int &number);
	unsigned long long int GenerateBitsValue();
	int getLevel(const int index);
	void Print();
	int level;
	int numPegs;
	
	unsigned long long int TableValue;
	std::vector<int> solvableValues;
	std::vector<int> Blanks;
	std::string last_move;
	std::vector<bool> Table;
	~PegTable(void);

private:
	const static int DEFAULT_SIZE = 15;
	
	int size;

};

