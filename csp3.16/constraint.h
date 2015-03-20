
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "pair.h"
#include <vector>
class constraint//只是在两个变量之间的约束
{
public:
    constraint();
    int GetType(void);
    int GetSize(void);
    mypair* GetPairCollection(void);
    void Initialization(char * dataLine);//initialize all the pairs
private:
    int serialNum;
    int type;
    int size;//包含几个元组对
    int elements;//几元约束
    int firstDomain, secondDomain;//相对应的第一个域，相对应的第二个域
    mypair* pairCollection;
};
#endif
