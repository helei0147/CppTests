#include "tools.h"
#include <cstring>
#include <vector>
using namespace std;
void Keep_The_Same_Q_L(variable* x,int xi)
{
    for(int i=0; i<x[xi].GetDomainSize(); i++)
        x[xi].SetL(i,x[xi].GetQ(i));
    return;
}
void DeleteFollowingSpaces(char* tempstring)
{
    int stringLength = strlen(tempstring);
    int tempnumber = 0;
    for (int i = stringLength - 1; i >= 0; i--)
    {
        if (tempstring[i] == ' ')
        {
            tempstring[i] = 0;
            stringLength--;
        }
        else if (tempstring[i] <= '9'&&tempstring[i] >= '0')
        {
            break;
        }
    }
}
vector<int>* StringToIntArray(char* mystring)
{
    int stringLength=strlen(mystring);
    int tempnumber=0;
    for (int i = stringLength - 1; i >= 0; i--)
    {
        if (mystring[i] == ' ')
        {
            mystring[i] = 0;
            stringLength--;
        }
        else if (mystring[i]<='9'&&mystring[i]>='0')
        {
            break;
        }
    }
    vector<int>* returnvector=new vector<int>;
    for (int i = 0; i <= stringLength; i++)
    {
        if (mystring[i] != ' ' && mystring[i] != 0)
        {
            tempnumber = tempnumber * 10 + mystring[i] - '0';
        }
        else
        {
            returnvector->push_back(tempnumber);
            tempnumber = 0;
        }
    }
    return returnvector;
}

void Creatpair(queue<value>&temp,variable*x,domain* domainCollection,int account)
{
    for(int i=0; i<account; i++)
    {
        int BianH=domainCollection[x[i].GetDomainIndex()].GetSize();
        for(int j=0; j!=BianH; j++)
            if(x[i].IfInLowerLayer(j))
            {
                value p(i,j);
                temp.push(p);
            }
    }
    return;
}//这个函数将所有 没有被删除的 论域中的 元素做成（xi,a）的对，更改传进来的队列引用

bool isConsistent_value(int** yuanzujiColle, constraint* constraintColle, variable* variableColle, domain* domainColle,
                        int variableIndex_j, int value_b, int variableIndex_k, int value_c)
{
    //判断两个值是否是相容的，参数中给出的是变量的标号还有要确定的两个值的实际值（不实在变量中的标号）
    int yuanzujiIndex = yuanzujiColle[variableIndex_j][variableIndex_k];
    mypair* tempPairPointer = constraintColle[yuanzujiIndex].GetPairCollection();
    if (constraintColle[yuanzujiIndex].GetType() == 1)
    {
        for (int i = 0; i < constraintColle[yuanzujiIndex].GetSize(); i++)
        {
            if ((tempPairPointer[i].GetFirst() == value_b) && (tempPairPointer[i].GetSecond() == value_c))
            {
                return true;
            }
        }
        return false;
    }
    else//这里的逻辑很可疑（不过现在看也没有什么可疑之处）
    {
        for (int i = 0; i < constraintColle[yuanzujiIndex].GetSize(); i++)
        {
            if ((tempPairPointer[i].GetFirst() == value_b) && (tempPairPointer[i].GetSecond() == value_c))
            {
                return false;
            }
        }
        return true;
    }
}

bool haveACSs(int** yuanzujiColle,constraint* constraintColle,variable* variableColle,domain* domainColle,int variableIndex_i,int valueIndex_i,int variableIndex_j,int valueIndex_j)
{
    if ( ! (variableColle[variableIndex_i].IfInUpperLayer(valueIndex_j) ) )
        return false;
    vector<int>* vpHaveConstraint = variableColle[variableIndex_i].GetVectorPointer();
    for (int i = 0; i < vpHaveConstraint->size(); i++)//有约束的个数，遍历所有有约束的变量
    {
        int variableIndex_k = (*vpHaveConstraint)[i];
        int yuanzujiIndex = yuanzujiColle[variableIndex_i][variableIndex_k];
        //找到是哪一种元组集，知道标号
        int k_min, k_max;
        if (constraintColle[yuanzujiIndex].GetType() == 1)
        {
            mypair* pairColle = constraintColle[yuanzujiIndex].GetPairCollection();
            //遍历该元组集中的所有对，寻找（xi，a）
            int value_i = domainColle[variableIndex_i].IndexToValue(valueIndex_i);//找出（xi，a）的值
            for (int m = 0; m < constraintColle[yuanzujiIndex].GetSize(); m++)
            {
                if (pairColle[m].GetFirst() == value_i)
                {
                    int value_k = pairColle[m].GetSecond();
                    int domainIndex_k = variableColle[variableIndex_k].GetDomainIndex();
                    int valueIndex_k = domainColle[domainIndex_k].ValueToIndex(value_k);
                    k_min = valueIndex_k;
                    break;
                }
            }
            for (int m = constraintColle[yuanzujiIndex].GetSize()-1; m >=0; m++)
            {
                if (pairColle[m].GetFirst() == value_i)
                {
                    int value_k = pairColle[m].GetSecond();
                    int domainIndex_k = variableColle[variableIndex_k].GetDomainIndex();
                    int valueIndex_k = domainColle[domainIndex_k].ValueToIndex(value_k);
                    k_max = valueIndex_k;
                    break;
                }
            }
        }
        else//不满足约束的情况
        {
            mypair* pairColle = constraintColle[yuanzujiIndex].GetPairCollection();
            //遍历该元组集中的所有对，寻找（xi，a）
            int value_i = domainColle[variableIndex_i].IndexToValue(valueIndex_i);//找出（xi，a）的值
            for (int m = 0; m < constraintColle[yuanzujiIndex].GetSize(); m++)
            {
                if (pairColle[m].GetFirst() != value_i)
                {
                    int value_k = pairColle[m].GetSecond();
                    int domainIndex_k = variableColle[variableIndex_k].GetDomainIndex();
                    int valueIndex_k = domainColle[domainIndex_k].ValueToIndex(value_k);
                    k_min = valueIndex_k;
                    break;
                }
            }
            for (int m = constraintColle[yuanzujiIndex].GetSize() - 1; m >= 0; m++)
            {
                if (pairColle[m].GetFirst() != value_i)
                {
                    int value_k = pairColle[m].GetSecond();
                    int domainIndex_k = variableColle[variableIndex_k].GetDomainIndex();
                    int valueIndex_k = domainColle[domainIndex_k].ValueToIndex(value_k);
                    k_max = valueIndex_k;
                    break;
                }
            }
        }
        bool found = false;
        int domainIndex_k = variableColle[variableIndex_k].GetDomainIndex();
        int yuanzujiIndex_jk = yuanzujiColle[variableIndex_j][variableIndex_k];
        for (int iter = k_min; iter <= k_max; iter++)
        {
            int value_k = domainColle[domainIndex_k].IndexToValue(iter);
            int domainIndex_j = variableColle[variableIndex_j].GetDomainIndex();
            int value_j = domainColle[domainIndex_j].IndexToValue(domainIndex_j);
            bool flag = isConsistent_value(yuanzujiColle, constraintColle, variableColle, domainColle,
                                           variableIndex_j, value_j, variableIndex_k, value_k);
            if (flag == true)
                found = true;
        }
        if (found == false)
            return false;
    }
    return true;
}

bool remove(domain*dom,variable*var,int variableIndex_i,int a,vector<int>*list,bool ifQ)
{
    //从变量的域中删除一个值，ifQ决定是真删除还是假删除，为true是真删除，为false是假删除
    if(dom[var[variableIndex_i].GetDomainIndex()].IfInTheDomain(a))
    {
        int m=dom[var[variableIndex_i].GetDomainIndex()].ValueToIndex(a);
        if(ifQ==true)
        {
            var[variableIndex_i].SetL(m, false);
            var[variableIndex_i].SetQ(m, false);
        }
        else
            var[variableIndex_i].SetL(m, false);
    }
/*    //之下的代码结构混乱，需要重新整理！
    if(ifQ==true)
    {
        if(!var[variableIndex_i].ifEmptyQ())//variable类里定义了ifEmptyL()和ifEmptyQ()
        {
            if(!list->empty())
            {
                if(!ifRepeated(*list,variableIndex_i))
                    list->push_back(variableIndex_i);
            }
            return true;
        }
        return false;
    }
    if(!var[variableIndex_i].ifEmptyL())//variable类里定义了ifEmptyL()和ifEmptyQ()
    {
        if(!list->empty())
        {
            if(!ifRepeated(*list,variableIndex_i))
                list->push_back(variableIndex_i);
        }
        return true;
    }
    return false;
    //之上的代码结构混乱，需要重新整理！
    */
    //贺磊的整理：
    if((!var[variableIndex_i].ifEmptyL())
    {
        if(!list->empty())
        {
            if(!ifRepeated(*list,variableIndex_i))
                list->push_back(variableIndex_i);
            //以上求并集list为空，那么就不会插入（舍弃意味），但是如果list本身就是空的，传进来的就是空的vector，会是什么结果？
        }
    return true;
    }
    else
        return false;
}

bool FC(int** yuanzujiColle,domain* dom,constraint* con,variable* var,int variableIndex_i,int a,vector<int>*list)
{
    vector<int>*nul=NULL;//
    vector<int>* vpHaveConstraint = var[variableIndex_i].GetVectorPointer();
    for (int i = 0; i < vpHaveConstraint->size(); i++)//有约束的个数，遍历所有有约束的变量
    {
        int variableIndex_j = (*vpHaveConstraint)[i];
        for(int k=0; k<dom[var[variableIndex_j].GetDomainIndex()].GetSize(); k++)
        {
            int b=dom[var[variableIndex_j].GetDomainIndex()].IndexToValue(k);     //xj域里每个值b
            if(!isConsistent_value(yuanzujiColle,con,var,dom,variableIndex_i,a,variableIndex_j,b))
            {
                if(!remove(dom,var,variableIndex_j,b,nul,0))
                    return false;
                if(!list->empty())
                {
                    if(!ifRepeated(*list,variableIndex_j))
                        list->push_back(variableIndex_j);
                }
            }
        }
    }
    return true;
}

bool ifRepeated(vector<int> list,int variableIndex_i)
{
    if(!list.empty())
    {
        int i=0;
        int count=list.size();
        while(i<count)
        {
            if(list[i]==variableIndex_i)
                return true;
            i++;
        }
        if(i>=count)
            return false;
    }
    return false;

}

