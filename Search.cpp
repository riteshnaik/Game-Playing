#include "Search.h"

using namespace std;

Search::Search(void){
	maxValue = -9999;
	maxRow = 0;
	maxColumn = 0;
}

void Search::Greedy(char player,vector< vector<char> > &state){
	int utilityValue;
	vector< vector<int> > moves(3);
	vector< vector<char> > currentState;
	vector< vector<char> > maxState;
	currentState = state;
	maxState = state;
	ValidMoves(moves,player,state);
	
	for(int i=0;i<moves[0].size();i++){

		 Successors(player,currentState,moves,moves[0][i],moves[1][i]);
		 utilityValue = Utility(player, currentState);
		 
		 if(utilityValue > maxValue){
			maxValue = utilityValue;
			maxRow = moves[0][i];
			maxColumn = moves[1][i];
			maxState = currentState;
		 }

		 if(utilityValue == maxValue && moves[0][i] + moves[1][i] < maxRow + maxColumn){
			maxValue = utilityValue;
			maxRow = moves[0][i];
			maxColumn = moves[1][i];
			maxState = currentState;
		 }
		 currentState = state;
	}

	Output(1,maxState,"");
}

void Search::MiniMax(char player,vector< vector<char> > &state,int cutting_off_depth){
	int depth = 0;
	maxState = state;
	traverseLog << "Node,Depth,Value\n";		 
	int value = MaxValue(player,state,cutting_off_depth,depth,0,0);
	Output(2,maxState,traverseLog.str().substr(0, traverseLog.str().size()-1));
	
}

void Search::Alphabeta(char player,vector< vector<char> > &state,int cutting_off_depth){
	int depth = 0;
	maxState = state;
	traverseLog << "Node,Depth,Value,Alpha,Beta\n";		 
	int value = MaxValue(player,state,cutting_off_depth,depth,0,0,-999,999);
	Output(2,maxState,traverseLog.str().substr(0, traverseLog.str().size()-1));
}