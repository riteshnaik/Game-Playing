#include "BoardUtility.h"

#define MIN -999
#define MAX 999
#define INFINITY "Infinity"
#define NINFINITY "-Infinity"

using namespace std;
extern ostringstream traverseLog;

class Search{
private:
	int maxValue;
	int maxRow;
	int maxColumn;
	/*Min and Max Utility functions of Min-Max algorithm*/
	int MaxValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column);
	int MinValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column);

	/*Min and Max Utility functions of Alpha-beta algorithm*/
	int MaxValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column,int alpha, int beta);
	int MinValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column,int alpha, int beta);
public:
	Search();
	void Greedy(char player,vector< vector<char> > &state);
    void MiniMax(char player,vector< vector<char> > &state,int cutting_off_depth);
    void Alphabeta(char player,vector< vector<char> > &state,int cutting_off_depth);
};