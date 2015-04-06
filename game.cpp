#include<string>
#include<algorithm>
#include<stdlib.h>
#include "Search.h"

using namespace std;

int main(){
	string buffer;
	char player;
	int task;
	int cutting_off_depth;
	vector< vector<char> > state(8);
	char val;

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

	Search s;
	if(task == 1){
		s.Greedy(player,state);
	
	}
	
	if(task == 2){
		s.MiniMax(player,state,cutting_off_depth);
	}

	if(task == 3){
		s.Alphabeta(player,state,cutting_off_depth);
	}

	system("pause");
	return 0;
}
