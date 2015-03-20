#include "variable.h"
#include "tools.h"
#include "domain.h"
using namespace std;
variable::variable()
{
}
bool variable::getQ(int c)
{
    return Q[c];
}
void variable::Initialization(char* tstring,domain* domainColle)
{
    vector<int>* buffervector = StringToIntArray(tstring);
    index = (*buffervector)[0];
    domainIndex = (*buffervector)[1];
    domainSize = domainColle[domainIndex].GetSize();
    Q = new bool[domainSize];
    L = new bool[domainSize];
    for (int i = 0; i < domainSize; i++)
    {
        Q[i] = L[i] = true;
    }
}

vector<int>* variable::GetVectorPointer(void)
{
    return &have_constraint;
}

int variable::GetDomainIndex(void)
{
    return domainIndex;
}
int variable::GetdomainSize(void)
{
    return domainSize;
}

bool variable::IfInUpperLayer(int index)
{
    if (index >= domainSize||index < 0)
        return false;
    else
        return Q[index];
}
bool variable::IfInLowerLayer(int index)
{
    if (index >= domainSize||index < 0 )
        return false;
    else
        return L[index];
}

bool variable::SetQ(int index, bool WantToSet)
{
    Q[index] = WantToSet;
    return true;
}

bool variable::SetL(int index, bool WantToSet)
{
    L[index] = WantToSet;
    return true;
}
bool variable::ifEmptyL()
{
    for (int i = 0; i < domainSize; i++)
    {
        if(L[i]==true)
            return false;
    }
    return true;
}

bool  variable::ifEmptyQ()
{
    for (int i = 0; i < domainSize; i++)
    {
        if(Q[i]==true)
            return false;
    }
    return true;
}

bool variable::GetL(int temp)
{
    return L[temp];
}