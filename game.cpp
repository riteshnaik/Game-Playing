#include<iostream>
#include<sstream>
#include<queue>
#include<fstream>
#include<string>
#include<list>
#include<algorithm>
#include<stdlib.h>
#include<vector>

using namespace std;

void Output(int task,vector< vector<char> > &state);
void printLog(int row, int column, int depth,int value,string inf);
void printLog(string state, int depth,int value,string inf);
void printLog(int row, int column, int depth,int value,string inf,int alpha,int beta,string ainf, string binf);
void printLog(string state, int depth,int value,string inf,int alpha,int beta,string ainf, string binf);

void Successors(char player,vector< vector<char> > &state,vector< vector<int> >& moves,int row,int column);
void ValidMoves(vector< vector<int> >& moves,char player,vector< vector<char> > &state);
void GetBranchFactor(vector< vector<int> >& moves,vector< vector<int> >& branch);
int Utility(char player,vector< vector<char> > &state);

int Max(int a,int b);
int Min(int a,int b);
int MaxValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column);
int MinValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column);
int MaxValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column,int alpha, int beta);
int MinValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column,int alpha, int beta);

void Greedy(char player,vector< vector<char> > &state);
void MiniMax(char player,vector< vector<char> > &state,int cutting_off_depth);
void Alphabeta(char player,vector< vector<char> > &state,int cutting_off_depth);

int boardWeights[8][8] = { 99, -8,   8,  6,  6,  8, -8,  99,
						  - 8, -24, -4, -3, -3, -4, -24, -8,
							8, -4,   7,  4,  4,  7, -4,   8,
							6, -3,   4,  0,  0,  4, -3,   6,
							6, -3,   4,  0,  0,  4, -3,   6,
							8, -4,   7,  4,  4,  7, -4,   8,
						   -8, -24, -4, -3, -3, -4, -24, -8,
						   99, -8,   8,  6,  6,  8, -8,  99};

char Name[8] ={'a','b','c','d','e','f','g','h'};
vector< vector<char> > maxState;
ostringstream traverseLog;
ostringstream buffer;
ofstream out("output.txt");

/*Gets probable successors for the given state*/
void Successors(char player,vector< vector<char> > &state,vector< vector<int> >& moves,int row,int column){

	char opponent;
	
	if(player == 'X'){
		opponent = 'O';
	}
	
	if(player == 'O'){
		opponent = 'X';
	}

	for(int i=0;i<moves[0].size();i++){
		if(moves[0][i] == row && moves[1][i] == column){
			switch(moves[2][i]){
				case 1: for(int k=row-1,l=column-1;k>0,l>0,state[k][l] == opponent;k--,l--){
							state[k][l] = player;
						}
						break;
				case 2: for(int k=row-1,l=column;k>0,state[k][l] == opponent;k--){
							state[k][l] = player;
						}
						break;
				case 3: for(int k=row-1,l=column+1;k>0,l<7,state[k][l] == opponent;k--,l++){
							state[k][l] = player;
						}
						break;
				case 4: for(int k=row,l=column+1;l<7,state[k][l] == opponent;l++){
							state[k][l] = player;
						}
						break;
				case 5: for(int k=row+1,l=column+1;k<7,l<7,state[k][l] == opponent;k++,l++){
							state[k][l] = player;
						}
						break;
				case 6: for(int k=row+1,l=column;k<7,state[k][l] == opponent;k++){
							state[k][l] = player;
						}
						break;
				case 7: for(int k=row+1,l=column-1;k<7,l>0,state[k][l] == opponent;k++,l--){
							state[k][l] = player;
						}
						break;
				case 8: for(int k=row,l=column-1;l>0,state[k][l] == opponent;l--){
							state[k][l] = player;
						}
						break;
			}
		}
	}

	state[row][column] = player;
}

/*Gets all valid moves for all the successors of the given state */
void ValidMoves(vector< vector<int> >& moves,char player,vector< vector<char> > &state){
	
	char opponent;
	
	if(player == 'X'){
		opponent = 'O';
	}
	
	if(player == 'O'){
		opponent = 'X';
	}

	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(state[i][j] == '*'){
				if(i-1 >= 0 && j-1>= 0 && state[i-1][j-1] == opponent){
					for(int k=i-2,l=j-2;k>=0 && l>=0;k--,l--){
						if(state[k][l] == player){
							moves[0].push_back(i);
							moves[1].push_back(j);
							moves[2].push_back(1);
							break;
						}
						if(state[k][l] == '*'){
							break;
						}
					}
				}
			}

			if(state[i][j] == '*'){
				if(i-1 >= 0 && state[i-1][j] == opponent){
					
					for(int k=i-2;k>=0;k--){
						if(state[k][j] == player){
							moves[0].push_back(i);
							moves[1].push_back(j);
							moves[2].push_back(2);
							break;
						}
						if(state[k][j] == '*'){
							break;
						}
					}
					
				}
			}

			if(state[i][j] == '*'){
				if(i-1 >= 0 && j+1 < 8 && state[i-1][j+1] == opponent){
					for(int k=i-2,l=j+2;k>=0 && l<8;k--,l++){
						if(state[k][l] == player){
							moves[0].push_back(i);
							moves[1].push_back(j);
							moves[2].push_back(3);
							break;
						}
						if(state[k][l] == '*'){
							break;
						}
					}
				}
			}

			if(state[i][j] == '*'){
				if(j+1 < 8 && state[i][j+1] == opponent){
					for(int l=j+2;l<8;l++){
						if(state[i][l] == player){
							moves[0].push_back(i);
							moves[1].push_back(j);
							moves[2].push_back(4);
							break;
						}
						if(state[i][l] == '*'){
							break;
						}
					}
				}
			}

			if(state[i][j] == '*'){
				if(i+1 < 8 && j+1 < 8 && state[i+1][j+1] == opponent){
					for(int k=i+2,l=j+2;k<8 && l<8;k++,l++){
						if(state[k][l] == player){
							moves[0].push_back(i);
							moves[1].push_back(j);
							moves[2].push_back(5);
							break;
						}
						if(state[k][l] == '*'){
							break;
						}
					}
				}
			}

			if(state[i][j] == '*'){
				if(i+1 < 8 && state[i+1][j] == opponent){
					for(int k=i+2;k<8;k++){
						if(state[k][j] == player){
							moves[0].push_back(i);
							moves[1].push_back(j);
							moves[2].push_back(6);
							break;
						}
						if(state[k][j] == '*'){
							break;
						}
					}
				}
			}

			if(state[i][j] == '*'){
				if(i+1 < 8 && j-1 >= 0 && state[i+1][j-1] == opponent){
					for(int k=i+2,l=j-2;k<8 && l>=0;k++,l--){
						if(state[k][l] == player){
							moves[0].push_back(i);
							moves[1].push_back(j);
							moves[2].push_back(7);
							break;
						}
						if(state[k][l] == '*'){
							break;
						}
					}
				}
			}

			if(state[i][j] == '*'){
				if(j-1 >= 0 && state[i][j-1] == opponent){
					for(int l=j-2;l>=0;l--){
						if(state[i][l] == player){
							moves[0].push_back(i);
							moves[1].push_back(j);
							moves[2].push_back(8);
							break;
						}
						if(state[i][l] == '*'){
							break;
						}
					}
				}
			}
		}
	}
	
}

/*Terminal State*/
int Utility(char player,vector< vector<char> > &state){
	char opponent;
	int weight_player = 0;
	int weight_opponent = 0;

	if(player == 'X'){
		opponent = 'O';
	}
	
	if(player == 'O'){
		opponent = 'X';
	}

	for(int i=0;i < 8; i++){
		for(int j=0;j < 8; j++){
			if(state[i][j] == player){
				weight_player = weight_player + boardWeights[i][j];
			}

			if(state[i][j] == opponent){
				weight_opponent = weight_opponent + boardWeights[i][j];
			}
		}
	}

return weight_player-weight_opponent;
}

void Output(int task,vector< vector<char> > &state,string log){
	string output;
	
	if( task == 1 || task == 2){
		for (int j=0;j<8;j++){
				for(int k=0;k<8;k++){
					output = output + state[j][k];
				}
				output = output  + '\n';
		}

		out << output;
		out << log;
	}
}

int Max(int a,int b){
	if( a > b){
		return a;
	}
	else{
		return b;
	}
}

int Min(int a,int b){
	if( a < b){
		return a;
	}
	else{
		return b;
	}
}

void GetBranchFactor(vector< vector<int> >& moves,vector< vector<int> >& branch){

	int found = 0;
	branch[0].push_back(moves[0][0]);
	branch[1].push_back(moves[1][0]);
	
	for(int i=0;i<moves[0].size();i++){
		for(int j=0;j<branch[0].size();j++){
			if(moves[0][i] == branch[0][j] && moves[1][i] == branch[1][j]){
				found = 1;
			}
		}
		if(found == 0){
			branch[0].push_back(moves[0][i]);
			branch[1].push_back(moves[1][i]);
		}
		found = 0;
	}
}

void printLog(int row, int column, int depth,int value,string inf){
	
	if(depth == 0){
			traverseLog << "root,";
			traverseLog << depth;
			traverseLog << ",";
			if(value >= 999 || value <= -999){
				traverseLog << inf;
				traverseLog << "\n";
			}
			else{
				traverseLog << value;
				traverseLog << "\n";
			}
	}
	else{
		traverseLog <<  Name[column];
		traverseLog << row; 
		traverseLog <<  ",";
		traverseLog << depth;
		traverseLog << ",";
		if(value >= 999 || value <= -999){
			traverseLog << inf;
			traverseLog << "\n";
		}
		else{
			traverseLog << value;
			traverseLog << "\n";
		}
	}
}

void printLog(string state, int depth,int value,string inf){
	
	traverseLog << state;
	traverseLog << ",";
	traverseLog << depth;
	traverseLog << ",";
		
	if(value >= 999 || value <= -999){
		traverseLog << inf;
		traverseLog << "\n";
	}
	else{
		traverseLog << value;
		traverseLog << "\n";
	}
}

void printLog(int row, int column, int depth,int value,string inf,int alpha,int beta,string ainf, string binf){
	
	if(depth == 0){
			traverseLog << "root";
	}
	else{
		traverseLog <<  Name[column];
		traverseLog << row; 
	}

	traverseLog <<  ",";
	traverseLog << depth;
	traverseLog << ",";

	if(value >= 999 || value <= -999){
		traverseLog << inf;
		traverseLog << ",";
	}
	else{
		traverseLog << value;
		traverseLog << ",";
	}
			
	if(alpha >= 999 || alpha <= -999){
		traverseLog << ainf;
		traverseLog << ",";
	}
	else{
		traverseLog << alpha;
		traverseLog << ",";
	}

	if(beta >= 999 || beta <= -999){
		traverseLog << binf;
		traverseLog << "\n";
	}
	else{
		traverseLog << beta;
		traverseLog << "\n";
	}
}

void printLog(string state, int depth,int value,string inf,int alpha,int beta,string ainf, string binf){
	
	traverseLog << state;
	traverseLog <<  ",";
	traverseLog << depth;
	traverseLog << ",";

	if(value >= 999 || value <= -999){
		traverseLog << inf;
		traverseLog << ",";
	}
	else{
		traverseLog << value;
		traverseLog << ",";
	}
			
	if(alpha >= 999 || alpha <= -999){
		traverseLog << ainf;
		traverseLog << ",";
	}
	else{
		traverseLog << alpha;
		traverseLog << ",";
	}

	if(beta >= 999 || beta <= -999){
		traverseLog << binf;
		traverseLog << "\n";
	}
	else{
		traverseLog << beta;
		traverseLog << "\n";
	}
}

/*Max node of Minimax search tree*/
int MaxValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column){
	int value = -999;
	int nvalue = 999;
	int maxValue = -9999;
	int maxRow = 0;
	int maxColumn = 0;
	string inf = "-Infinity";
	string ninf = "Infinity";
	vector< vector<char> > currentState;
	vector< vector<int> > moves(3);
	vector< vector<int> > o_moves(3);
	vector< vector<int> > pmoves(3);
	vector< vector<int> > o_pmoves(3);
	vector< vector<int> > branch(2);
	vector< vector<int> > o_branch(2);
	char opponent;
	
	if(player == 'X'){
		opponent = 'O';
	}
	
	if(player == 'O'){
		opponent = 'X';
	}

	ValidMoves(moves,player,state);
	currentState = state;

	ValidMoves(o_moves,opponent,state);
  
	if(moves[0].empty() && o_moves[0].empty()){
		value = Utility(player, state);
		printLog(row + 1, column, depth,value,inf);
		return value;
	}

	if(depth == cutting_off_depth){
		value = Utility(player, state);
		printLog(row + 1, column, depth,value,inf);
		return value;
	}

	
	if(depth == 0){
		if(moves[0].empty() && o_moves[0].empty()){
			value = Utility(player, state);
			printLog(row + 1, column, depth,value,inf);
			return value;
		}
		else{
			printLog(row + 1, column, depth,value,inf);
		}
	}
	else{

		printLog(row + 1, column, depth,value,inf);
	}

	
	if(moves[0].empty() && !o_moves[0].empty()){
		depth = depth + 1;
		printLog("pass", depth,value,ninf);
		
		GetBranchFactor(o_moves,o_branch);

		for(int i = 0;i<o_branch[0].size();i++){

			Successors(opponent,currentState,o_moves,o_branch[0][i],o_branch[1][i]);
			nvalue = Min(nvalue,MaxValue(player,currentState,cutting_off_depth,depth+1, o_branch[0][i],o_branch[1][i] ));

			printLog("pass", depth,nvalue,ninf);

			maxRow = column;
			maxColumn = row;
			maxState = state;
			currentState = state;

		}

		if(depth-1 == 0){
			printLog(row + 1, column, depth-1,nvalue,inf);
		}
		else{
			printLog(row + 1, column, depth-1,nvalue,inf);
		}
		return nvalue;
	}

	GetBranchFactor(moves,branch); 
	
	
	for(int i = 0;i<branch[0].size();i++){
		Successors(player,currentState,moves,branch[0][i],branch[1][i]);
		value = Max(value,MinValue(opponent,currentState,cutting_off_depth,depth+1, branch[0][i],branch[1][i]));

		printLog(row + 1, column, depth,value,inf);
		if(value > maxValue && depth == 0){
			maxValue = value;
			maxRow = branch[0][i];
			maxColumn = branch[1][i];
			maxState = currentState;
		}

		if(value == maxValue && branch[0][i] + branch[1][i] < maxRow + maxColumn && depth == 0){
			maxValue = value;
			maxRow = branch[0][i];
			maxColumn = branch[1][i];
			maxState = currentState;
		}
		currentState = state;
	}
		return value; 
}
/*Min node of Minimax search tree */
int MinValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column){
	int value = 999;
	int nvalue = -999;
	string inf = "Infinity";
	string ninf = "-Infinity";
	ostringstream buffer;
	vector< vector<char> > currentState;
	vector< vector<int> > moves(3);
	vector< vector<int> > o_moves(3);
	vector< vector<int> > pmoves(3);
	vector< vector<int> > o_pmoves(3);
    vector< vector<int> > branch(2);
	vector< vector<int> > o_branch(2);

	char opponent;
	
	if(player == 'X'){
		opponent = 'O';
	}
	
	if(player == 'O'){
		opponent = 'X';
	}

	ValidMoves(moves,player,state);
	currentState = state;

	ValidMoves(o_moves,opponent,state);

	if(moves[0].empty() && o_moves[0].empty()){
		value = Utility(opponent, state);
		printLog(row + 1, column, depth,value,inf);
		return value;
	}

	if(depth == cutting_off_depth){
		value = Utility(opponent, state);
		printLog(row + 1, column, depth,value,inf);
		return value;
	}

	printLog(row + 1, column, depth,value,inf);

	if(moves[0].empty() && !o_moves[0].empty()){

		depth = depth + 1;
		printLog("pass", depth,value,ninf);
		GetBranchFactor(o_moves,o_branch);
		for(int i = 0;i<o_branch[0].size();i++){

			Successors(opponent,currentState,o_moves,o_branch[0][i],o_branch[1][i]);
			nvalue = Max(nvalue,MinValue(player,currentState,cutting_off_depth,depth+1, o_branch[0][i] ,o_branch[1][i] ));
			printLog("pass", depth,nvalue,inf);
			currentState = state;

		}

		printLog(row + 1, column, depth-1,nvalue,inf);
		return nvalue;

	}

	GetBranchFactor(moves,branch);

	for(int i = 0;i<branch[0].size();i++){

		Successors(player,currentState,moves,branch[0][i],branch[1][i]);
		value = Min(value,MaxValue(opponent,currentState,cutting_off_depth,depth+1, branch[0][i],branch[1][i]));
		printLog(row + 1, column, depth,value,inf);
		currentState = state;

	}
	return value;
}

/*Max node of Minimax search tree with Alpha-beta pruning*/
int MaxValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column,int alpha, int beta){
	int value = -999;
	int nvalue = 999;
	int maxValue = -9999;
	int maxRow = 0;
	int maxColumn = 0;
	int nalpha = -999;
	int nbeta = 999;
	string inf = "-Infinity";
	string ninf = "Infinity";
	string ainf = "-Infinity";
	string binf = "Infinity";
	vector< vector<char> > currentState;
	vector< vector<int> > moves(3);
	vector< vector<int> > o_moves(3);
	vector< vector<int> > pmoves(3);
	vector< vector<int> > o_pmoves(3);
	vector< vector<int> > branch(2);
	vector< vector<int> > o_branch(2);
	char opponent;
	
	if(player == 'X'){
		opponent = 'O';
	}
	
	if(player == 'O'){
		opponent = 'X';
	}

	ValidMoves(moves,player,state);
	currentState = state;

	ValidMoves(o_moves,opponent,state);
  
	if(moves[0].empty() && o_moves[0].empty()){
		value = Utility(player, state);
		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		return value;
	}

	if(depth == cutting_off_depth){
		value = Utility(player, state);
		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		return value;
	}

	
	if(depth == 0){
		if(moves[0].empty() && o_moves[0].empty()){
			value = Utility(player, state);
			printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
			return value;
		}
		else{
			printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		}
	}
	else{

		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
	}

	
	if(moves[0].empty() && !o_moves[0].empty()){
		depth = depth + 1;
		printLog("pass", depth,value,ninf,alpha,beta,ainf,binf);
		
		GetBranchFactor(o_moves,o_branch);
		nalpha = alpha;
		nbeta = beta;
		for(int i = 0;i<o_branch[0].size();i++){

			Successors(opponent,currentState,o_moves,o_branch[0][i],o_branch[1][i]);
			nvalue = Min(nvalue,MaxValue(player,currentState,cutting_off_depth,depth+1, o_branch[0][i],o_branch[1][i],nalpha,nbeta));

			if( nvalue <= nalpha){
				printLog("pass", depth,nvalue,ninf,nalpha,nbeta,ainf,binf);
				return nvalue;
			}

			nbeta = Min(nbeta,nvalue);

			printLog("pass", depth,nvalue,ninf,nalpha,nbeta,ainf,binf);

			maxRow = column;
			maxColumn = row;
			maxState = state;
			currentState = state;

		}

		if( nvalue >= beta){
			printLog(row + 1, column, depth-1,nvalue,inf,alpha,beta,ainf,binf);
			return nvalue;
		}

		alpha = Max(alpha,nvalue);

		printLog(row + 1, column, depth-1,nvalue,inf,alpha,beta,ainf,binf);
		return nvalue;
	}

	GetBranchFactor(moves,branch); 
	
	
	for(int i = 0;i<branch[0].size();i++){
		Successors(player,currentState,moves,branch[0][i],branch[1][i]);
		value = Max(value,MinValue(opponent,currentState,cutting_off_depth,depth+1, branch[0][i],branch[1][i],alpha,beta));

		if( value >= beta){
			printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
			return value;
		}

		alpha = Max(alpha,value);

		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		if(value > maxValue && depth == 0){
			maxValue = value;
			maxRow = branch[0][i];
			maxColumn = branch[1][i];
			maxState = currentState;
		}

		if(value == maxValue && branch[0][i] + branch[1][i] < maxRow + maxColumn && depth == 0){
			maxValue = value;
			maxRow = branch[0][i];
			maxColumn = branch[1][i];
			maxState = currentState;
		}
		currentState = state;
	}
		return value; 
}

/*Min node of Minimax search tree with Alpha-beta pruning*/
int MinValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column,int alpha, int beta){
	int value = 999;
	int nvalue = -999;
	string inf = "Infinity";
	string ninf = "-Infinity";
	string ainf = "-Infinity";
	string binf = "Infinity";
	int nalpha = -999;
	int nbeta = 999;
	ostringstream buffer;
	vector< vector<char> > currentState;
	vector< vector<int> > moves(3);
	vector< vector<int> > o_moves(3);
	vector< vector<int> > pmoves(3);
	vector< vector<int> > o_pmoves(3);
    vector< vector<int> > branch(2);
	vector< vector<int> > o_branch(2);

	char opponent;
	
	if(player == 'X'){
		opponent = 'O';
	}
	
	if(player == 'O'){
		opponent = 'X';
	}

	ValidMoves(moves,player,state);
	currentState = state;

	ValidMoves(o_moves,opponent,state);

	if(moves[0].empty() && o_moves[0].empty()){
		value = Utility(opponent, state);
		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		return value;
	}

	if(depth == cutting_off_depth){
		value = Utility(opponent, state);
		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		return value;
	}

	printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);

	if(moves[0].empty() && !o_moves[0].empty()){

		depth = depth + 1;
		printLog("pass", depth,value,ninf,alpha,beta,ainf,binf);
		GetBranchFactor(o_moves,o_branch);
		nalpha = alpha;
		nbeta = beta;
		for(int i = 0;i<o_branch[0].size();i++){

			Successors(opponent,currentState,o_moves,o_branch[0][i],o_branch[1][i]);
			nvalue = Max(nvalue,MinValue(player,currentState,cutting_off_depth,depth+1, o_branch[0][i] ,o_branch[1][i],nalpha,nbeta));

			if( nvalue >= nbeta){
				printLog("pass", depth,nvalue,ninf,nalpha,nbeta,ainf,binf);
				return nvalue;
			}

			nalpha = Max(nalpha,nvalue);

			printLog("pass", depth,nvalue,inf,nalpha,nbeta,ainf,binf);
			currentState = state;

		}
		
		if( nvalue <= alpha){
			printLog(row + 1, column, depth-1,nvalue,inf,alpha,beta,ainf,binf);
			return nvalue;
		}

		beta = Min(beta,nvalue);

		printLog(row + 1, column, depth-1,nvalue,inf,alpha,beta,ainf,binf);
		return nvalue;

	}

	GetBranchFactor(moves,branch);

	for(int i = 0;i<branch[0].size();i++){

		Successors(player,currentState,moves,branch[0][i],branch[1][i]);
		value = Min(value,MaxValue(opponent,currentState,cutting_off_depth,depth+1, branch[0][i],branch[1][i],alpha,beta));

		if( value <= alpha){
			printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
			return value;
		}

		beta = Min(beta,value);

		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		currentState = state;

	}
	return value;
}

void Greedy(char player,vector< vector<char> > &state){
	int utilityValue;
	int maxValue = -999999;
	int maxRow = 0;
	int maxColumn = 0;
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

void MiniMax(char player,vector< vector<char> > &state,int cutting_off_depth){
	int depth = 0;
	maxState = state;
	traverseLog << "Node,Depth,Value\n";		 
	int value = MaxValue(player,state,cutting_off_depth,depth,0,0);
	Output(2,maxState,traverseLog.str().substr(0, traverseLog.str().size()-1));
	
}

void Alphabeta(char player,vector< vector<char> > &state,int cutting_off_depth){
	int depth = 0;
	maxState = state;
	traverseLog << "Node,Depth,Value,Alpha,Beta\n";		 
	int value = MaxValue(player,state,cutting_off_depth,depth,0,0,-999,999);
	Output(2,maxState,traverseLog.str().substr(0, traverseLog.str().size()-1));
}

int main(){
	string buffer;
	char player;
	int task;
	int cutting_off_depth;
	vector< vector<char> > state(8);
	char val;

	/*Reads board from input file input.txt*/
	ifstream myFile("input.txt");
	
	getline(myFile,buffer);
	istringstream line1(buffer);
	line1 >> task;
	getline(myFile,buffer);
	istringstream line2(buffer);
	line2 >> player;
	getline(myFile,buffer);
	istringstream line3(buffer);
	line3 >> cutting_off_depth;

	for(int i=0;i<8; i++){
		getline(myFile,buffer);
		istringstream temp(buffer);
		for(int j=0;j<8; j++){
			temp >> val;
			state[i].push_back(val);
		}
	}

	if(task == 1){
		/*Calculates the next move using Greedy algorithm*/
		Greedy(player,state);
	}
	
	if(task == 2){
		/*Calculates the next move using MiniMax algorithm*/
		MiniMax(player,state,cutting_off_depth);
	}

	if(task == 3){
		/*Calculates the next move using Alpha-beta algorithm*/
		Alphabeta(player,state,cutting_off_depth);
	}

	return 0;
}
