

#ifndef VARIABLE_H
#define VARIABLE_H

#include <vector>
#include "domain.h"
class variable
//变量类，1）域的编号
//2）两个bool数组，一个Q, 一个L，
//用来确定该变量的域中那个值被删除了，
//哪个没有被删除，Q是记录第一层的
//删除情况，L记录第二层的删除情况
//3)在变量值中加入和哪个其他变量
//之间有哪种元组对关系
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
    bool getQ(int);//返回Q指针
    bool GetL(int);//bool
private:
    int domainSize;
    int domainIndex;//该变量的域的编号
    int index;//该变量在所有变量值中的编号（从零开始）
    bool* Q;//记录变量值中的值在Q中被删除的情况(后来又改成在PendingList之中的存在状况)
    bool* L;//记录变量值中的值在L中被删除的情况
    std::vector<int> have_constraint;//存储和该变量有约束关系的变量编号，用push_back
};
#endif
