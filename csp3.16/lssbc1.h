

#ifndef LSSBC1_H
#define LSSBC1_H

//
//  lssbc1.h
//  ����
//
//  Created by sam on 14-9-14.
//  Copyright (c) 2014�� sam. All rights reserved.
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
void GetBackTheDom(bool * GetBack,variable *x,int i,int a);//��ԭ��������
bool LSSBC1(domain* dom,variable* x,constraint* C,int account,int** matrix,int*** min1,int*** max1);//�����������  account��¼��������

#endif
