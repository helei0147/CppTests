#include "lssbc1.h"
void ExchangeTheDom(bool * TakePlace,variable *x,int i)
{
    int b=x[i].GetDomainIndex();
    for(int j=0; j!=b; j++)
        TakePlace[j]=x[i].IfInLowerLayer(j);//进行论域复制。
    return;
}


void ReplaceTheDom(variable *x,int i,int a)
{
    for(int j=0; j!=x[i].GetdomainSize(); j++)
        x[i].SetL(j,0);
    x[i].SetL(a, 1);
    return;
}//只是更改假删除的状况

bool DelistEmpty(bool *d,int o)
{
    int size;
    size=0;
    for(int i=0; i!=o; i++)
        if(!d[i])
            size++;
    if(size==0)
        return true;
    else
        return false;
}

void GetBackTheDom(bool *GetBack,variable *x,int i,int a)//将变量中的L删除情况变成GetBack的copy
{
    int y=x[i].GetdomainSize();
    for(int u=0; u!=y; u++)
        if(u!=a)
            x[i].SetL(u, GetBack[u]);
    return;
}

void ChangeQ(variable *a,int b)
{
    for(int i=0; i<b; i++)
        for(int j=0; j!=a[i].GetdomainSize(); j++)
            a[i].SetQ(j,a[i].GetL(j));  //参数？？解释：把L的值全部赋值给Q，相当于最后收尾？
    return;
}

bool LSSBC1(domain* dom,variable* x,constraint* C,int account,int** matrix,int*** min1,int*** max1)//参数还待添加  account记录变量个数
{
    vector<int> delist;
    vector<int>*dd=&delist;//FC中如何用的什么形式？我采用bool来记录变量的有无。
    vector<int> Q;
    vector<int>*oo=&Q;
    if(!propBC(-1,-1,oo,C,x,matrix,dom,min1,max1))        //为什么xi的编号是-1？代表NULL
        return false;
    queue<value> PandingList;
    queue<value> &now=PandingList;
    Creatpair(now,x,dom,account);//创建pair并将pair存入Pandinglist,能存入Pandinglist中吗？？
    while(!PandingList.empty())
    {
        value a(-1,-1);
        a=PandingList.front();//需要进行＝的重载。
        PandingList.pop();//元素去除有问题。
        bool satSSBC=false;
        int exchange=a.GetVariableIndex();//记录变量编号
        int exchange1=a.GetValueIndex();//记录变量值。
        bool *TempArry;
        TempArry=new bool[x[exchange].GetDomainIndex()];//建立临时数组记录xi的原轮域用来和之后判定后的xi a进行合并 数组大小正确吗？？
        ExchangeTheDom(TempArry, x, exchange);
        ReplaceTheDom(x, exchange,exchange1);//更改变量的论域。

        //if(!ifRepeated(Q,exchange))
        //    Q.push_back(exchange);
        //原伪代码：Q ← {x i }，这里错了，应该是
        Q.clear();
        Q.push_back(exchange);
        if(FC(matrix,dom,C,x,exchange,exchange1,oo))//遍历论域还是该从x的l入手。
        {
            if(propBC(exchange,exchange1,Q,C,x,matrix,dom,min1,max1))
            {
                satSSBC=true;
            }
        }
            //satSSBC=true;
        if(!satSSBC)
        {
            if(!remove(dom,x,exchange,exchange1,dd,1))//dd=dellist...删除不成功，说明问题不用继续研究了，已经不满足约束了，退出程序
                return false;
            else
            {
                x[exchange].SetQ(exchange1, 0);//修改论域 是从Q中删吧？ 还有为什么是else下面的？
            }//应该是删除成功，在Q中改变该值是否被删
        }
        for(int iter=0;iter<account;iter++)
        {
            Keep_The_Same_Q_L(x,iter);
        }
    }//PendingList.empty();
    ChangeQ(x,account);//更改变量的实际论域值

    stack<int>  HelpRecordC;//辅助记录和xi有关系的变量
    HelpRecordC.push(0);
    while(!delist.empty())//!DelistEmpty(delist,account)) !empty？？？
    {

        int xj;//找到的第一个变量


        vector<int>::iterator it=delist.end()-1;//
        xj=*it;
        delist.pop_back();//获取一个变量
        for(int k=0; k!=account; k++)
            if(matrix[xj][k]!=-1)
                HelpRecordC.push(k);//记录所有和xi有关系的变量。 是xj吗？大概不是，是和xj有关系的变量xi
        while(!HelpRecordC.empty())
        {
            int xi;//记录从xst中提取出的变量。
            xi=HelpRecordC.top();
            HelpRecordC.pop();
            bool *TempArry1;

            for(int p=0; p!=x[xi].GetdomainSize(); p++) //GetDomainSize()
            {
                if (!x[xi].IfInLowerLayer(p))
                {
                    continue;
                }
                TempArry1=new bool[x[xi].GetDomainIndex()];//建立临时数组记录xi的原轮域用来和之后判定后的xi a进行合并 应该是size吧？？
                ExchangeTheDom(TempArry1, x, xi);//
                ReplaceTheDom(x, xi,p);//更改变量的轮域。 不是P吧？
                bool found=false;
                if(FC(matrix,dom,C,x,xj,p,NULL))
                    if(updatabound(min1,max1,dom,x,xi,p,xj,matrix,C))
                        found=true;
                if(!found)
                    if(!remove(dom,x,xi,p,dd,1))
                        return false;
                GetBackTheDom(TempArry1,x,xj,p);//最后一个参数是值，不是在论域中的标号，WARNNING
            }//不是P吧？
        }//while(!HelpRecord)

    }//while(delist)
    ChangeQ(x,account);
    return true;

}
