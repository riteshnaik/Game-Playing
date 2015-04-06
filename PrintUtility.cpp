#include "PrintUtility.h"

using namespace std;
ostringstream traverseLog;

void printLog(string state, int depth,int value,string inf){
	
	traverseLog << state;
	traverseLog << ",";
	traverseLog << depth;
	traverseLog << ",";
		
	if(value >= MAX || value <= MIN){
		traverseLog << inf;
		traverseLog << "\n";
	}
	else{
		traverseLog << value;
		traverseLog << "\n";
	}
}

void printLog(int row, int column, int depth,int value,string inf){
	
	if(depth == 0){
			traverseLog << "root,";
			traverseLog << depth;
			traverseLog << ",";
			if(value >= MAX || value <= MIN){
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
		if(value >= MAX || value <= MIN){
			traverseLog << inf;
			traverseLog << "\n";
		}
		else{
			traverseLog << value;
			traverseLog << "\n";
		}
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

	if(value >= MAX || value <= MIN){
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

	if(value >= MAX || value <= MIN){
		traverseLog << inf;
		traverseLog << ",";
	}
	else{
		traverseLog << value;
		traverseLog << ",";
	}
			
	if(alpha >= MAX || alpha <= MIN){
		traverseLog << ainf;
		traverseLog << ",";
	}
	else{
		traverseLog << alpha;
		traverseLog << ",";
	}

	if(beta >= MAX || beta <= MIN){
		traverseLog << binf;
		traverseLog << "\n";
	}
	else{
		traverseLog << beta;
		traverseLog << "\n";
	}
}
