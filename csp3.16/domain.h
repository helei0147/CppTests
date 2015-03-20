
#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
class domain
{
public:
    domain();
    void Initialization(char* tstring);//��ʼ��

    int GetSize(void);
    void SetSize(int);
    void SetIndex(int);
    int GetIndex(void);
    bool IfInTheDomain(int);//����ĳ��ֵ�ǲ����ڸ���֮��
    int ValueToIndex(int);//����һ��ֵ�����ظ�ֵ�����е��±�
    int IndexToValue(int);//�����ڲ����±�λ�õ�ֵ
private:
    std::vector<int> domain_numbers;//�洢�������е���
    int size;//��С
    int domain_index;//������
};
#endif
