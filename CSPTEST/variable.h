

#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include "domain.h"
class variable
//�����࣬1����ı��
//2������bool���飬һ��Q, һ��L��
//����ȷ���ñ����������Ǹ�ֵ��ɾ���ˣ�
//�ĸ�û�б�ɾ����Q�Ǽ�¼��һ���
//ɾ�������L��¼�ڶ����ɾ�����
//3)�ڱ���ֵ�м�����ĸ���������
//֮��������Ԫ��Թ�ϵ
{
public:
    variable();
    int GetDomainIndex(void);
    int GetdomainSize(void);
    bool IfInUpperLayer(int index);
    bool IfInLowerLayer(int index);
    void Initialization(char* tstring,domain* domainColle);
    std::vector<int>* GetVectorPointer(void);
    bool SetQ(int index, bool WantToSet);
    bool SetL(int index, bool WantToSet);
    bool ifEmptyL();
    bool ifEmptyQ();
    bool getQ(int);//����Qָ��
    bool GetL(int);//bool
private:
    int domainSize;
    int domainIndex;//�ñ�������ı��
    int index;//�ñ��������б���ֵ�еı�ţ����㿪ʼ��
    bool* Q;//��¼����ֵ�е�ֵ��Q�б�ɾ�������(�����ָĳ���PendingList֮�еĴ���״��)
    bool* L;//��¼����ֵ�е�ֵ��L�б�ɾ�������
    std::vector<int> have_constraint;//�洢�͸ñ�����Լ����ϵ�ı�����ţ���push_back
};
#endif
