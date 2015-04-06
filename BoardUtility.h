#include "Utility.h"

using namespace std;

extern const int boardWeights[8][8];

extern const char Name[8];
extern vector< vector<char> > maxState;
extern ostringstream buffer;
extern int PASSFLAG;

void ValidMoves(vector< vector<int> >& moves,char player,vector< vector<char> > &state);
void Successors(char player,vector< vector<char> > &state,vector< vector<int> >& moves,int row,int column);
int Utility(char player,vector< vector<char> > &state);
void GetBranchFactor(vector< vector<int> >& moves,vector< vector<int> >& branch);
int CheckPiece(char player,vector< vector<char> > &state);