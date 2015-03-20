

#ifndef PAIR_H
#define PAIR_H

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
