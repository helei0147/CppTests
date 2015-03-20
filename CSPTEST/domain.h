
#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
class domain
{
public:
    domain();
    void Initialization(char* tstring);
    
    int GetSize(void);
    void SetSize(int);
    void SetIndex(int);
    int GetIndex(void);
    bool IfInTheDomain(int);//����ĳ��ֵ�ǲ����ڸ���֮��
    int ValueToIndex(int);//����һ��ֵ�����ظ�ֵ�����е��±�
    int IndexToValue(int);//�����ڲ����±�λ�õ�ֵ
private:
    std::vector<int> domain_numbers;
    int size;
    int domain_index;
};
#endif
