#include "BoardUtility.h"
#include "PrintUtility.h"

using namespace std;

int PASSFLAG = 0;

const int boardWeights[8][8] = { 99, -8,   8,  6,  6,  8, -8,  99,
						  - 8, -24, -4, -3, -3, -4, -24, -8,
							8, -4,   7,  4,  4,  7, -4,   8,
							6, -3,   4,  0,  0,  4, -3,   6,
							6, -3,   4,  0,  0,  4, -3,   6,
							8, -4,   7,  4,  4,  7, -4,   8,
						   -8, -24, -4, -3, -3, -4, -24, -8,
						   99, -8,   8,  6,  6,  8, -8,  99};

const char Name[8] ={'a','b','c','d','e','f','g','h'};
vector< vector<char> > maxState;
ostringstream buffer;

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

int CheckPiece(char player,vector< vector<char> > &state){
	
	for(int i=0; i < 8 ; i++){
		for(int j=0; j < 8 ; j++){
			if(state[i][j] == player){
				return 1;
			}

		}
	}

	return 0;
}
