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
    
    while (!L->empty())
    {
        xj = L->back();
        L->pop_back();
        pi = variableCollection[xj].GetVectorPointer();
        int i = 0;
        if (!pi->empty())  //��Ҫ���������***********************
            while (i<pi->size())
            {
                xk = (*pi)[i];    //��Ҫ���������***********************
                if (yueshuMatrix[xk][xj] != -1)
                {
                    int constraint_num = yueshuMatrix[xk][xj];//ȡԼ�����͵ı��
                    int var_num = variableCollection[xj].GetDomainIndex();
                    int dom_size = domainCollection[var_num].GetSize();
                    min_bc = domainCollection[var_num].IndexToValue(0);
                    max_bc = domainCollection[var_num].IndexToValue(dom_size);
                    for (int c = min_bc; c <max_bc&&c==max_bc; c++)
                    {
                        if (variableCollection[xk].IfInLowerLayer(c))//�ж�c�Ƿ�������ɾ��
                        {
                            if (seekACsupport(yueshuMatrix,constraintCollection,domainCollection,variableCollection,xk,c,xj))
                            {
                                if (variableCollection[xi].ifEmptyQ())//xi�ǿգ�������ǿգ�
                                {
                                    min[xi][xk][a] = c;
                                    break;
                                }//if va
                            }//seek
                            else if (!remove(domainCollection,variableCollection,xk,c,L,1))
                                return false;
                            else
                                L->push_back(xk);
                        }//variable
                    }//forc
                    for (int c = max_bc; c >min_bc&&c==min_bc; c--)
                    {
                        if (variableCollection[xk].IfInLowerLayer(c))//�ж�c�Ƿ�������ɾ��
                        {
                            if (seekACsupport(yueshuMatrix,constraintCollection,domainCollection,variableCollection,xk,c,xj))
                            {
                                if (variableCollection[xi].ifEmptyL()&& variableCollection[xi].getQ(a))
                                {
                                    max[xi][xk][a] = c;
                                    break;
                                }
                            }
                            else if (!remove(domainCollection,variableCollection,xk,c,NULL,1))
                                return false;
                            else
                                L->push_back(xk);
                        }
                    }
                }
                i++;
            } ; //��Ҫ���������***********************
    }
    return true;
}