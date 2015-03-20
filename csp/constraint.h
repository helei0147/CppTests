
#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "pair.h"
#include <vector>
class constraint//ֻ������������֮���Լ��
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
    int size;//��������Ԫ���
    int elements;//��ԪԼ��
    int firstDomain, secondDomain;//���Ӧ�ĵ�һ�������Ӧ�ĵڶ�����
    mypair* pairCollection;
};
#endif
