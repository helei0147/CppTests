#ifndef MAXMIN_H
#define MAXMIN_H

class maxandmin
{
public:
    maxandmin();
    int GetMax(void);
    int GetMin(void);
    void SetMax(int);
    void SetMin(int);
private:
    int max, min;
};
#endif
