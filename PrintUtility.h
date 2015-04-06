#include "Search.h"
using namespace std;

extern ostringstream traverseLog;

/*Print Utilities to print traversal of Min-Max algorithm*/
void printLog(string state, int depth,int value,string inf);
void printLog(int row, int column, int depth,int value,string inf);

/*Print Utilities to print traversal of Alpha-beta algorithm*/
void printLog(int row, int column, int depth,int value,string inf,int alpha,int beta,string ainf, string binf);
void printLog(string state, int depth,int value,string inf,int alpha,int beta,string ainf, string binf);