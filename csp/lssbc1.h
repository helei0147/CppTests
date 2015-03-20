

#ifndef LSSBC1_H
#define LSSBC1_H

//
//  lssbc1.h
//  测试
//
//  Created by sam on 14-9-14.
//  Copyright (c) 2014年 sam. All rights reserved.
//

#include <iostream>
#include "variable.h"
#include "domain.h"
#include "tools.h"
#include "propbc.h"
#include "constraint.h"
#include "updatabound.h"
#include <stack>
#include "value.h"
using namespace std;
void ChangeQ(variable*,int);
bool ifRepeated(vector<int>,int);
void ExchangeTheDom(bool * TakePlace,variable *x,int i);
void ReplaceTheDom(variable *,int i,int a);
bool DelistEmpty(bool *d,int o);
void GetBackTheDom(bool * GetBack,variable *x,int i,int a);//还原变量论域。
bool LSSBC1(domain* dom,variable* x,constraint* C,int account,int** matrix,int*** min1,int*** max1);//参数还待添加  account记录变量个数

#endif
