#include "updatabound.h"

bool PanDing(variable* x,int j,int b)
{
    if(x[j].IfInLowerLayer(b))
        return true;
    else
        return false;
}

void ChangeBound(domain* dom,int min,int max,variable* x,int j)
{
    for(int i=0;i<min+1;i++)
        x[j].SetQ(i,0);
    int temp;
    temp=x[j].GetDomainIndex();
    for(int i=dom[temp].GetSize();i>max-1;i--)
        x[i].SetQ(i,0);
    return;
}

bool seekACsupport(int** yuesuMaxtir,constraint *C,domain* dom,variable* x,int i,int a,int j)//x为指向变量数组的指针，dom为指向轮域的指针，i 为xi的下标，j为xj的下标
{
    int b;
    int temp;//记录xj轮域的编号。
    temp=x[i].GetDomainIndex();
    for(int li=0;li<dom[temp].GetSize();li++)
    {
        b=dom[temp].IndexToValue(li);
        if(isConsistent_value(yuesuMaxtir,C,x,dom,li,a,j,b))
            return true;
    }
    return false;
}

bool updatabound(int*** min,int*** max,domain* dom,variable* x,int i,int a,int j,int**yueshuMatrix,constraint*C)//同上注释
{
    bool found=false;
    int Min;
    int Max;
    Min=min[i][j][a];//边界更改后的最小边界的下标。
    Max=max[i][j][a];//边界更改后的最大边界的下标.
    if(!haveACSs(yueshuMatrix,C,x,dom,i,j,a,Min))
        for(int b=Min+1;b!=Max+1&&PanDing(x,j,b);b++)//判断条件有疑问PanDing用来检测xj中的b变量是否已经被删去。
        {
            if(!haveACSs(yueshuMatrix,C,x,dom,i,j,a,b))
            {
                Min=b;
                found=true;
                break;
            }
        }
    else
        found=true;
    
    if(!haveACSs(yueshuMatrix,C,x,dom,i,j,a,Max))
        for(int b=Max-1;(b!=Min-1)&&PanDing(x, j, b);b--)
            if(haveACSs(yueshuMatrix,C,x,dom,i,j,a,b))
            {
                Max=b;
                break;
            }
    ChangeBound(dom,Min,Max,x,j);//更改xj的边界
    return found;
}
