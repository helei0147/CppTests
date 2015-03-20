#include "propbc.h"
#include "constraint.h"
#include "Model.h"
#include "pair.h"
#include "tools.h"
#include "value.h"
#include "variable.h"
#include "domain.h"
#include "domain.h"
#include "updatabound.h"
#include <queue>
using namespace std;
bool propBC(int xi, int a, vector<int>* L, constraint* constraintCollection, variable* variableCollection,int** yueshuMatrix, domain* domainCollection,int*** min,int*** max)
{
    int xj;
    int xk;
    vector<int> * pi;
    int max_bc;
    int min_bc;
    min_bc = 0;
    max_bc = 0;
    int QFlag=0;
    if(xi!=-1&&a!=-1)
    {
        QFlag=0;
    }
    else
        QFlag=1;
    while (!L->empty())
    {
        xj = L->back();
        L->pop_back();//从L中去除一个元素
        pi = variableCollection[xj].GetVectorPointer();//pi是所有和xj有关系的变量的标号数组
        int i = 0;
        if (!pi->empty())
            while (i<pi->size())
            {
                xk = (*pi)[i];
                if (yueshuMatrix[xk][xj] != -1)
                {
                    int constraint_num = yueshuMatrix[xk][xj];//取约束类型的编号
                    int var_num = variableCollection[xj].GetDomainIndex();//xj的论域编号
                    int dom_size = domainCollection[var_num].GetSize();
                    min_bc = domainCollection[var_num].IndexToValue(0);
                    max_bc = domainCollection[var_num].IndexToValue(dom_size);//问题！这里的最大值真的是论域的大小吗？
                    for (int c = min_bc; c <max_bc&&c==max_bc; c++)
                    {
                        if (variableCollection[xk].IfInLowerLayer(c))//判断c是否在论域被删除
                        {
                            if (seekACsupport(yueshuMatrix,constraintCollection,domainCollection,variableCollection,xk,c,xj))
                            {
                                //if (variableCollection[xi].ifEmptyQ())//xi非空，在哪里非空？
                                if(xi!=-1&&a!=-1)
                                {
                                    min[xi][xk][a] = c;
                                    break;
                                }//if va
                            }//seek
                            else if (!remove(domainCollection,variableCollection,xk,c,L,QFlag))
                                return false;
                            else
                            {
                                bool tempflag=false;
                                for(int u=0;u<L->size();i++)
                                {
                                    if(L[u]==xk)
                                        tempflag=true;
                                        break;
                                }
                                if(tempflag==false)
                                    L->push_back(xk);
                            }
                            //L->push_back(xk);//不应该是简单的pushback，而应该是检查是否又重复的东西在决定是添加还是保持不变
                        }//variable
                    }//forc
                    for (int c = max_bc; c >min_bc&&c==min_bc; c--)
                    {
                        if (variableCollection[xk].IfInLowerLayer(c))//判断c是否在论域被删除
                        {
                            if (seekACsupport(yueshuMatrix,constraintCollection,domainCollection,variableCollection,xk,c,xj))
                            {
                                //if (variableCollection[xi].ifEmptyL()&& variableCollection[xi].getQ(a))
                                if(xi!=-1&&a!=-1)
                                {
                                    max[xi][xk][a] = c;
                                    break;
                                }
                            }
                            else if (!remove(domainCollection,variableCollection,xk,c,NULL,QFlag))
                                return false;
                            else
                            {
                                bool tempflag=false;
                                for(int u=0;u<L->size();i++)
                                {
                                    if(L[u]==xk)
                                        tempflag=true;
                                        break;
                                }
                                if(tempflag==false)
                                    L->push_back(xk);
                            }
                                //L->push_back(xk);//理由同上
                        }
                    }
                }
                i++;
            } ; //需要重载运算符***********************
    }
    return true;
}
