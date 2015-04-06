#include "Utility.h"

ofstream out("output.txt");

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

void displayState(vector< vector<char> > &state){
	string output;
	for (int j=0;j<8;j++){
			for(int k=0;k<8;k++){
				output = output + state[j][k] + ' ';
			}
			output = output  + '\n';
	}
	cout << output;
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