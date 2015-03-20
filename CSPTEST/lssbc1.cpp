#include "lssbc1.h"
void ExchangeTheDom(bool * TakePlace,variable *x,int i)
{
    int b=x[i].GetDomainIndex();
    for(int j=0;j!=b;j++)
        TakePlace[j]=x[i].IfInLowerLayer(j);//���������ơ�
    return;
}


void ReplaceTheDom(variable *x,int i,int a)
{
    for(int j=0;j!=x[i].GetdomainSize();j++)
        x[i].SetL(j,0);
    x[i].SetL(a, 1);
    return;
}

bool DelistEmpty(bool *d,int o)
{
    int size;
    size=0;
    for(int i=0;i!=o;i++)
        if(!d[i])
            size++;
    if(size==0)
        return true;
    else
        return false;
}

void GetBackTheDom(bool *GetBack,variable *x,int i,int a)
{
    int y=x[i].GetdomainSize();
    for(int u=0;u!=y;u++)
        if(u!=a)
            x[i].SetL(u, GetBack[u]);
    return;
}

void ChangeQ(variable *a,int b)
{
    for(int i=0;i<b;i++)
        for(int j=0;j!=a[i].GetdomainSize();j++)
            a[i].SetQ(j,a[i].GetL(j));  //��������
    return;
}

bool LSSBC1(domain* dom,variable* x,constraint* C,int account,int** matrix,int*** min1,int*** max1)//�����������  account��¼��������
{
    vector<int> delist;
    vector<int>*dd=&delist;//FC������õ�ʲô��ʽ���Ҳ���bool����¼���������ޡ�
    vector<int> Q;
    vector<int>*oo=&Q;
    if(!propBC(-1,-1,oo,C,x,matrix,dom,min1,max1))        //��������
        return false;
    queue<value> PandingList;
    queue<value> &now=PandingList;
    Creatpair(now,x,dom,account);//����pair����pair����Pandinglist,�ܴ���Pandinglist���𣿣�
    while(!PandingList.empty())
    {
        value a(-1,-1);
        a=PandingList.front();//��Ҫ���У������ء�
        PandingList.pop();//Ԫ��ȥ�������⡣
        bool satSSBC=false;
        int exchange=a.GetVariableIndex();//��¼�������
        int exchange1=a.GetValueIndex();//��¼����ֵ��
        bool *TempArry;
        TempArry=new bool[x[exchange].GetDomainIndex()];//������ʱ�����¼xi��ԭ����������֮���ж����xi a���кϲ� �����С��ȷ�𣿣�
        ExchangeTheDom(TempArry, x, exchange);
        ReplaceTheDom(x, exchange,exchange1);//���ı���������
        
        if(!ifRepeated(Q,exchange))
            Q.push_back(exchange);
        if(FC(matrix,dom,C,x,exchange,exchange1,oo))//���������Ǹô�x��l���֡�
            //propBC����������
            satSSBC=true;
        if(!satSSBC)
        {
            if(!remove(dom,x,exchange,exchange1,dd,1))//delist?
                return false;
            else
            {
                x[exchange].SetL(exchange1, 0);//�޸����� �Ǵ�Q��ɾ�ɣ� ����Ϊʲô��else����ģ�
            }//Ӧ����ɾ���ɹ�����Q�иı��ֵ�Ƿ�ɾ
            
        }
        
        GetBackTheDom(TempArry,x,exchange,exchange1);//��������
        
    }//PendingList.empty();
    ChangeQ(x,account);//���ı�����ʵ������ֵ
    
    stack<int>  HelpRecordC;//������¼��xi�й�ϵ�ı���
    HelpRecordC.push(0);
    while(delist.empty())//!DelistEmpty(delist,account)) !empty������
    {
        
        int xj;//�ҵ��ĵ�һ������
        
        
        vector<int>::iterator it=delist.end()-1;//
        xj=*it;
        delist.pop_back();//��ȡһ������
        for(int k=0;k!=account;k++)
            if(matrix[xj][k]!=-1)
                HelpRecordC.push(k);//��¼���к�xi�й�ϵ�ı����� ��xj��
        while(!HelpRecordC.empty())
        {
            int xi;//��¼��xst����ȡ���ı�����
            xi=HelpRecordC.top();
            HelpRecordC.pop();
            bool *TempArry1;
            
            for(int p=0;p!=x[xi].GetdomainSize();p++)  //GetDomainSize()
            {
				if (!x[xi].IfInLowerLayer(p))
				{
					continue;
				}
                TempArry1=new bool[x[xi].GetDomainIndex()];//������ʱ�����¼xi��ԭ����������֮���ж����xi a���кϲ� Ӧ����size�ɣ���
                ExchangeTheDom(TempArry1, x, xi);//
                ReplaceTheDom(x, xi,p);//���ı��������� ����P�ɣ�
                bool found=false;
                if(FC(matrix,dom,C,x,xj,p,NULL))
                    if(updatabound(min1,max1,dom,x,xi,p,xj,matrix,C))
                        found=true;
                if(!found)
                    if(!remove(dom,x,xi,p,dd,1))
                        return false;
                GetBackTheDom(TempArry1,x,xj,p);
            }//����P�ɣ�
        }//while(!HelpRecord)
        
    }//while(delist)
    ChangeQ(x,account);
    return true;
    
}