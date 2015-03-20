

#ifndef PAIR_H
#define PAIR_H
//现在看来是暂时废弃的类……
class mypair//这个类用来存储约束中的值
{
private:
    int first, second;
public:
    int GetFirst(void);
    int GetSecond(void);
    void SetFirst(int tempfirst);
    void SetSecond(int tempsecond);
};

#endif
