

#ifndef TOOLS_H
#define TOOLS_H
#include <vector>
#include "constraint.h"
#include "Model.h"
#include "pair.h"
#include "tools.h"
#include "value.h"
#include "variable.h"
#include "domain.h"
#include <queue>
using namespace std;
std::vector<int>* StringToIntArray(char* mystring);
bool haveACSs(int** yuanzujiColle,constraint* constraintColle,variable* variableColle,domain* domainColle, int variableIndex_i, int valueIndex_i,
              int variableIndex_j, int valueIndex_j);
bool isConsistent_value(int** yuanzujiColle, constraint* constraintColle, variable* variableColle, domain* domainColle, int variableIndex_j, int value_b, int variableIndex_k, int value_c);
bool remove(domain*dom,variable*var,int variableIndex_i,int a,vector<int>*list,bool ifQ);
bool FC(int** yuanzujiColle,domain*dom,constraint*con, variable*var,int variableIndex_i,int a,vector<int>*list);
void Creatpair(queue<value>&temp,variable*x,domain* domainCollection,int account);
void DeleteFollowingSpaces(char* tempstring);
bool ifRepeated(vector<int> list,int variableIndex_i);
#endif
