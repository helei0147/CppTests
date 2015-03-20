
#ifndef DOMAIN_H
#define DOMAIN_H

#include <vector>
class domain
{
public:
    domain();
    void Initialization(char* tstring);//初始化

    int GetSize(void);
    void SetSize(int);
    void SetIndex(int);
    int GetIndex(void);
    bool IfInTheDomain(int);//查找某个值是不是在该域之中
    int ValueToIndex(int);//传入一个值，返回该值在域中的下标
    int IndexToValue(int);//返回在参数下标位置的值
private:
    std::vector<int> domain_numbers;//存储论域所有的数
    int size;//大小
    int domain_index;//论域编号
};
#endif
