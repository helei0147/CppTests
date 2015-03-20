

#ifndef PROPBC_H
#define PROPBC_H

#include <iostream>
#include "constraint.h"
#include "Model.h"
#include "pair.h"
#include "tools.h"
#include "value.h"
#include "variable.h"
#include "domain.h"
#include <fstream>
#include "maxmin.h"
using namespace std;
bool propBC(int xi, int a, vector<int>* L, constraint* constraintCollection, variable* variableCollection,int** yueshuMatrix, domain* domainCollection,int*** min,int*** max);
#endif
