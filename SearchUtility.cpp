#include "PrintUtility.h"

int Search::MaxValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column){
	int value = MIN;
	int nvalue = MAX;
	string inf = NINFINITY;
	string ninf = INFINITY;
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

int Search::MinValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column){
	int value = MAX;
	int nvalue = MIN;
	string inf = INFINITY;
	string ninf = NINFINITY;
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

int Search::MaxValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column,int alpha, int beta){
	int value = MIN;
	int nvalue = MAX;
	int nalpha = MIN;
	int nbeta = MAX;
	int palpha = MIN;
	int pbeta = MAX;
	string inf = NINFINITY;
	string ninf = INFINITY;
	string ainf = NINFINITY;
	string binf = INFINITY;
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
  
	if(moves[0].empty() && o_moves[0].empty() && !CheckPiece(opponent,state)){
		value = Utility(player, state);
		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		return value;
	}

	if(moves[0].empty() && o_moves[0].empty() && CheckPiece(opponent,state) && PASSFLAG){
		PASSFLAG = 0;
		value = Utility(player, state);
		printLog("pass", depth,value,ninf,alpha,beta,ainf,binf);
		return value;
	}

	if(moves[0].empty() && o_moves[0].empty() &&  CheckPiece(opponent,state) && !PASSFLAG){
		PASSFLAG = 1;
		palpha = alpha;
		pbeta = beta;

		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		
		printLog("pass", depth + 1,value,ninf,alpha,beta,ainf,binf);

		value = Max(value,MinValue(player,currentState,cutting_off_depth,depth+1, row,column,alpha,beta));

		if( value <= alpha){
				printLog("pass", depth,nvalue,ninf,nalpha,nbeta,ainf,binf);
				return nvalue;
		}

		pbeta = Min(beta,value);

		printLog("pass", depth + 1,value,ninf,alpha,pbeta,ainf,binf);

		printLog(row + 1, column, depth,value,inf,pbeta,beta,ainf,binf);
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

int Search::MinValue(char player,vector< vector<char> > &state,int cutting_off_depth,int depth,int row,int column,int alpha, int beta){
	int value = MAX;
	int nvalue = MIN;
	string inf = INFINITY;
	string ninf = NINFINITY;
	string ainf = NINFINITY;
	string binf = INFINITY;
	int nalpha = MIN;
	int nbeta = MAX;
	int palpha = MIN;
	int pbeta = MAX;
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

	if(moves[0].empty() && o_moves[0].empty() &&  !CheckPiece(opponent,state)){
		value = Utility(player, state);
		printLog(row + 1, column, depth,value,inf,alpha,beta,ainf,binf);
		return value;
	}

	if(moves[0].empty() && o_moves[0].empty() &&  CheckPiece(opponent,state) && PASSFLAG){
		PASSFLAG = 0;
		value = Utility(player, state);
		printLog("pass", depth + 1,value,ninf,alpha,beta,ainf,binf);
		return value;
	}

	if(moves[0].empty() && o_moves[0].empty() &&  CheckPiece(opponent,state) && !PASSFLAG){
		PASSFLAG = 1;
		palpha = alpha;
		pbeta = beta;
		printLog("pass", depth,value,ninf,alpha,beta,ainf,binf);

		value = Max(value,MinValue(player,currentState,cutting_off_depth,depth+1, row,column,palpha,pbeta));

		if( value >= pbeta){
			printLog(row + 1, column, depth,value,inf,palpha,pbeta,ainf,binf);
			return value;
		}

		alpha = Max(alpha,value);

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