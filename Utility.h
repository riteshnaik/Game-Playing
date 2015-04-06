#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>

using namespace std;

extern ofstream out;

int Max(int a,int b);
int Min(int a,int b);
void displayState(vector< vector<char> > &state);

void Output(int task,vector< vector<char> > &state,string log);