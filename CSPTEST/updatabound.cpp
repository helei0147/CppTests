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

bool seekACsupport(int** yuesuMaxtir,constraint *C,domain* dom,variable* x,int i,int a,int j)//xΪָ����������ָ�룬domΪָ�������ָ�룬i Ϊxi���±꣬jΪxj���±�
{
    int b;
    int temp;//��¼xj����ı�š�
    temp=x[i].GetDomainIndex();
    for(int li=0;li<dom[temp].GetSize();li++)
    {
        b=dom[temp].IndexToValue(li);
        if(isConsistent_value(yuesuMaxtir,C,x,dom,li,a,j,b))
            return true;
    }
    return false;
}

bool updatabound(int*** min,int*** max,domain* dom,variable* x,int i,int a,int j,int**yueshuMatrix,constraint*C)//ͬ��ע��
{
    bool found=false;
    int Min;
    int Max;
    Min=min[i][j][a];//�߽���ĺ����С�߽���±ꡣ
    Max=max[i][j][a];//�߽���ĺ�����߽���±�.
    if(!haveACSs(yueshuMatrix,C,x,dom,i,j,a,Min))
        for(int b=Min+1;b!=Max+1&&PanDing(x,j,b);b++)//�ж�����������PanDing�������xj�е�b�����Ƿ��Ѿ���ɾȥ��
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
    ChangeBound(dom,Min,Max,x,j);//����xj�ı߽�
    return found;
}
