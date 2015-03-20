

#ifndef UPDATABOUND_H
#define UPDATABOUND_H


#include <iostream>
#include "variable.h"
#include "domain.h"
#include "tools.h"
/* defined(______updatabound__) */

bool PanDing(variable* x,int j,int b);
void ChangeBound (domain* dom,int min,int max,variable* x,int j);
bool seekACsupport(int** yuesuMaxtir,constraint *C,domain* dom,variable* x,int i,int a,int j);//x为指向变量数组的指针，dom为指向轮域的指针，i 为xi的下标，j为xj的下标

bool updatabound(int*** min,int*** max,domain* dom,variable* x,int i,int a,int j,int**yueshuMatrix,constraint*C);//同上注释


#endif
