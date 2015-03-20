#include "maxmin.h"
maxandmin::maxandmin()
{}
int maxandmin::GetMax(void)
{
    return max;
}
int maxandmin::GetMin(void)
{
    return min;
}
void maxandmin::SetMax(int tempmax)
{
    max = tempmax;
}
void maxandmin::SetMin(int tempmin)
{
    min = tempmin;
}